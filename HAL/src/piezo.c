/* Includes ------------------------------------------------------------------*/
#include "piezo.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static eHalGpioId_t ePiezoPinId;
static uint32_t		ulTimerFreq;
static uint32_t		ulTickToWait;
static uint8_t		ucWaitForDelay;
static uint8_t		ucCompareRegData = 100;
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void prvPiezoTimerCallbackFunc(void);
/* Private functions ---------------------------------------------------------*/
void prvPiezoTimerCallbackFunc(void)
{
	if(ucWaitForDelay == 1)
	{
		if(ulTickToWait > 0)
		{
			ulTickToWait--;
		}
		else
		{
			ucWaitForDelay = 0;
			vGpioSetPinState(ePiezoPinId, ePinLow);
			vStopTimerInterrupt(eTim2, eOCFxAInterrupt);
		}
	}
	vGpioTogglePinState(ePiezoPinId);
}

/* Exported functions --------------------------------------------------------*/
void vInitPiezo(eHalGpioId_t ePiezoPin)
{
	timerInitStruct_t xTimerInfo;


	xTimerInfo.eTim 		= eTim2;
	xTimerInfo.eMode 		= eTimerCTC;
	xTimerInfo.eOCxAPinMode	= eOcxxNoOperation;
	xTimerInfo.eOCxBPinMode	= eOcxxNoOperation;
	xTimerInfo.ePrescaler	= eDiv32Prescaler;
	vInitTimerStruct(&xTimerInfo);
	vSetOutputCompareA(eTim2, ucCompareRegData);
	vSetInterruptCallback(eTim2, eOCFxAInterrupt, prvPiezoTimerCallbackFunc);

	ulTimerFreq = F_CPU / (32 * ucCompareRegData);
	ePiezoPinId = ePiezoPin;
}

void vTurnPiezoOnForSec(uint8_t ulDelayInSec)
{
	ucWaitForDelay = 1;
	ulTickToWait = ulDelayInSec * ulTimerFreq;
	vStartTimerInterrupt(eTim2, eOCFxAInterrupt);
}

void vTurnPiezoOnForMs(uint32_t ulDelayInMs)
{
	ucWaitForDelay = 1;
	ulTickToWait = (uint32_t)((float)(ulDelayInMs / 1000) * (float) ulTimerFreq);
	vStartTimerInterrupt(eTim2, eOCFxAInterrupt);
}

void vTurnPiezoOn(void)
{
	vStartTimerInterrupt(eTim2, eOCFxAInterrupt);
}

void vTurnPiezoOff(void)
{
	vStopTimerInterrupt(eTim2, eOCFxAInterrupt);
	vGpioSetPinState(ePiezoPinId, ePinLow);
}
