/* Include -------------------------------------------------------------------*/
#include "hal_lib.h"

/* Private function prototype-------------------------------------------------*/
void prvHalStartSysTick(void);
void prvHalTickHook(void);

/* Private function ----------------------------------------------------------*/
void prvHalStartSysTick(void)
{
	timerInitStruct_t xTimerInfo;

	/* Setup Timer for 1Khz interrupt intervals*/
	xTimerInfo.eTim 		= SYS_TICK_TIMER;
	xTimerInfo.eMode 		= eTimerCTC;
	xTimerInfo.eOCxAPinMode	= eOcxxNoOperation;
	xTimerInfo.eOCxBPinMode	= eOcxxNoOperation;
	xTimerInfo.ePrescaler	= eDiv64Prescaler;
	vInitTimerStruct(&xTimerInfo);
	vSetOutputCompareA(SYS_TICK_TIMER, 250);

	/* Register callBack */
	vSetInterruptCallback(SYS_TICK_TIMER, SYS_TICK_INT, prvHalTickHook);

	/* Start Timer Interrupt*/
	vStartTimerInterrupt(SYS_TICK_TIMER, SYS_TICK_INT);
}

void prvHalTickHook(void)
{
	/* Update frame timeout */
	UsartTickHook();
}

/* Exported Function----------------------------------------------------------*/

void vHalInit(void)
{
	/* Enable Interrupt */
	sei();

	/* Initialize all GPIO */
	#ifdef GPIO_DEF
	vGpioInitAllPin();
	#endif

	/* Initialize the UART interface */
	#ifdef USART_DEF
	UsartInit();
	#endif

	/* Initialize ADC */
	#ifdef ADC_DEF
	vAdcInit();
	#endif

	/* Initialize Keypad */
	#ifdef KEYPAD_DEF
	vResetKeypad();
	#endif

	/* Initialize Timer */
	#ifdef TIM_DEF
	vInitTimers();
		#ifdef USE_SYS_TICK
		/* Initialize system tick (1ms) */
		prvHalStartSysTick();
		#endif
	#endif
}

void vHalRegisterToSysTick(void (*callbackFunc)(void))
{
	vSetInterruptCallback(SYS_TICK_TIMER, SYS_TICK_INT, callbackFunc);
}

void vHalProcess(void)
{
	#ifdef KEYPAD_DEF
	/* Update keyboard key pressed */
	vKeypadRefresh();
	#endif
}
