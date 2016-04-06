/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define set_register_bit(reg,mask) ((reg) |= (mask))
#define reset_register_bit(reg,mask) ((reg) &= ~(mask))
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/

/* GPIO Info struct */
static PinDescriptor_t xPinInfo[HAL_GPIO_NUM_OF_RSRC] =
{
    #define X_GPIO(ENUM_ID, PORTX, DDRX, PINX, PORTPIN, MODE, DEFAULTVALUE) \
                  {ENUM_ID, PORTX, DDRX, PINX, PORTPIN, MODE, DEFAULTVALUE},
        GPIO_DEF
    #undef X_GPIO
};
/* Private variables ---------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void vGpioInitAllPin(void)
{
	uint8_t uci;

	for(uci = 0; uci < HAL_GPIO_NUM_OF_RSRC; uci++)
		vGpioConfigPin((eHalGpioId_t)uci);
}

void vGpioConfigPin(eHalGpioId_t eId)
{
	uint8_t	ucPinMask = (1<< xPinInfo[eId].ucPinNumber);

	switch(xPinInfo[eId].xMode)
	{
		case eInputModePu:
			reset_register_bit(*xPinInfo[eId].ucDDRx,ucPinMask);
			set_register_bit(*xPinInfo[eId].ucPORTx,ucPinMask);
			/*Make sure the pull up are not disable in the MCU control register */
			MCUCR &= ~(1<<PUD);
			break;
		case eInputModeNoPu:
			reset_register_bit(*xPinInfo[eId].ucDDRx,ucPinMask);
			reset_register_bit(*xPinInfo[eId].ucPORTx,ucPinMask);
			break;
		case eOutputMode:
			set_register_bit(*xPinInfo[eId].ucDDRx,ucPinMask);
			//#warning For some reason the PIN must be set High at first...
			vGpioSetPinState(xPinInfo[eId].ucID, xPinInfo[eId].xDefaultState);
			break;
	}
}

void vGpioSetPinMode(eHalGpioId_t eId, ePinMode_t eMode)
{
	xPinInfo[eId].xMode = eMode;
	vGpioConfigPin(xPinInfo[eId].ucID);
}

void vGpioSetPinState(eHalGpioId_t eId , ePinState_t xState)
{
	uint8_t	ucPinMask = (1<< xPinInfo[eId].ucPinNumber);
	switch(xState)
	{
		case ePinLow:
			reset_register_bit(*xPinInfo[eId].ucPORTx,ucPinMask);
			break;
		case ePinHigh:
			set_register_bit(*xPinInfo[eId].ucPORTx,ucPinMask);
			break;
	}
}

void vGpioTogglePinState(eHalGpioId_t eId)
{
	ePinState_t eCurrentState = eGpioReadPinState(eId);
	if(eCurrentState == ePinLow)
		vGpioSetPinState(eId,ePinHigh);
	else
		vGpioSetPinState(eId,ePinLow);
}

ePinState_t eGpioReadPinState(eHalGpioId_t eId)
{
	uint8_t	ucPinMask = (1<< xPinInfo[eId].ucPinNumber);
	if( (*xPinInfo[eId].ucPINx & ucPinMask) > 0)
		return ePinHigh;
	else
		return ePinLow;
}


