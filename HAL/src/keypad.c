/* Include ------------------------------------------------------------------*/
#include "keypad.h"
/* Private Defines------------------------------------------------------------*/
#define NUM_OF_COLUNM_PIN	3
#define COLUNM_INDEX		0
#define NUM_OF_ROW_PIN		4
#define ROW_INDEX			(COLUNM_INDEX + NUM_OF_COLUNM_PIN)
#define KEYPAD_NUM_PIN		(NUM_OF_COLUNM_PIN + NUM_OF_ROW_PIN)
#define KEYPAD_NUM_BT		(NUM_OF_COLUNM_PIN * NUM_OF_ROW_PIN)

/* Private Enum---------------------------------------------------------------*/
typedef enum
{
	eKeyLowToHigh,
	eKeyHighToLow,
	eKeyIdle,
}eKeyTransisition_t;

/* Private structure----------------------------------------------------------*/
typedef struct
{
	eKeyState_t			eOldKey;
	eKeyState_t 		eKeyCurrentState;
	eKeyState_t 		eKeyOldState;
	uint8_t				ucDebounceCount;
	eKeyTransisition_t	eTransition;

}keyData_t;

/* Private variable-----------------------------------------------------------*/
static uint8_t	ucDebouncedTick = 100; /* Default Value = 100 */
static keyData_t xKeyData[KEYPAD_NUM_BT];
static eHalGpioId_t eKeypadMap[KEYPAD_NUM_PIN] =  {KEYPAD3,		KEYPAD1,		KEYPAD5,	  KEYPAD2,		KEYPAD7,	KEYPAD6,	KEYPAD4};
static uint8_t ucKeypadMap[3][4] = {
		{1,4,7,10} ,
		{2,5,8,11} ,
		{3,6,9,12}
};
/* Private function prototype-------------------------------------------------*/
void prvDebounceKey(uint8_t ucKey, eKeyState_t eNewState)
{

	/* If the new key state is the same as the old one ----------------------*/
	if(eNewState == xKeyData[ucKey].eOldKey)
	{
		/* Decrement Debounced count ----------------------------------------*/
		xKeyData[ucKey].ucDebounceCount --;
		/* If debounced time is over set key current state-------------------*/
		if(xKeyData[ucKey].ucDebounceCount == 0)
		{
			/* Set the Old state --------------------------------------------*/
			xKeyData[ucKey].eKeyOldState = xKeyData[ucKey].eKeyCurrentState ;
			/* Set the new State ---------------------------------------------*/
			xKeyData[ucKey].eKeyCurrentState = eNewState;

			if(eNewState > xKeyData[ucKey].eKeyOldState )
				xKeyData[ucKey].eTransition = eKeyLowToHigh;
			else if(eNewState < xKeyData[ucKey].eKeyOldState)
				xKeyData[ucKey].eTransition = eKeyHighToLow;
		}
		/* Set the old key-----------------------------------------------*/
		xKeyData[ucKey].eOldKey = eNewState;
		return;
	}
	/* Otherwise reset the debounceCount------------------------------*/
	xKeyData[ucKey].ucDebounceCount = ucDebouncedTick;
	/* Otherwise set the old key------------------------------------------*/
	xKeyData[ucKey].eOldKey = eNewState;
}

/* Exported function----------------------------------------------------------*/
void vKeypadRefresh(void)
{
	uint8_t ucc, ucr, ucKey;
	eKeyState_t	eKeyState;
	/* Iterate across the colunm */
	for( ucc = COLUNM_INDEX; ucc < NUM_OF_COLUNM_PIN; ucc++)
	{
		/* Set the colunm digital low */
		vGpioSetPinState(eKeypadMap[ucc],ePinLow);
		/* Iterate across the row */
		for(ucr = ROW_INDEX; ucr < KEYPAD_NUM_PIN; ucr++)
		{
			ucKey = ucKeypadMap[ucc][ucr - ROW_INDEX]- 1;
			/* If we read digital low on the pin the buton is pressed */
			if(eGpioReadPinState(eKeypadMap[ucr]) == ePinLow)
				eKeyState = eKeyPressed;
			else
				eKeyState = eKeyReleased;

			prvDebounceKey(ucKey, eKeyState);
		}
		/* Reset the colunm pin to digital high */
		vGpioSetPinState(eKeypadMap[ucc],ePinHigh);
	}
}

eKeyState_t eGetCurrentKeyState(uint8_t ucKey)
{
	return xKeyData[ucKey].eKeyCurrentState;
}

uint8_t eKeyIsPressed(uint8_t ucKey)
{
	if(xKeyData[ucKey].eTransition == eKeyLowToHigh)
	{
		xKeyData[ucKey].eTransition = eKeyIdle;
		return 1;
	}
	return 0;
}

uint8_t	eKeyIsReleased(uint8_t ucKey)
{
	if(xKeyData[ucKey].eTransition == eKeyHighToLow)
	{
		xKeyData[ucKey].eTransition = eKeyIdle;
		return 1;
	}
	return 0;
}

void vResetKeypad(void)
{
	for(uint8_t uci; uci < KEYPAD_NUM_BT; uci++)
	{
		xKeyData[uci].eKeyCurrentState = eKeyReleased;
		xKeyData[uci].eKeyOldState = eKeyReleased;
		xKeyData[uci].eOldKey = eKeyReleased;
		xKeyData[uci].eTransition = eKeyIdle;
	}
}
