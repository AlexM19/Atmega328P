//For now this driver does not support TIM1

/* Includes ------------------------------------------------------------------*/
#include "timer.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
typedef struct
{
	volatile uint8_t   *ucTCCRxA;
	volatile uint8_t   *ucTCCRxB;
	volatile uint8_t   *ucTCNTx;
	volatile uint8_t   *ucOCRxA;
	volatile uint8_t   *ucOCRxB;
	volatile uint8_t   *ucTIMSKx;
	volatile uint8_t   *ucTIFRx;
} timerReg_t;

/* Private variables ---------------------------------------------------------*/

/* Callback typedef and arrays */
typedef  void (*callback_t)(void);
callback_t functionCompA[eNumberOfTim][TIM_NUM_CALLBACK];
callback_t functionCompB[eNumberOfTim][TIM_NUM_CALLBACK];
callback_t functionOVF[eNumberOfTim][TIM_NUM_CALLBACK];

/* Pointer to timers register */
static timerReg_t xTimReg[eNumberOfTim];

/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void prvInitTimersReg(void);
int8_t prvTestCallbackAvailability(callback_t *callback);
/* Private functions ---------------------------------------------------------*/
int8_t prvTestCallbackAvailability(callback_t *callback)
{

	for(uint8_t uci = 0; uci < TIM_NUM_CALLBACK; uci++)
	{
			if(callback[uci] == NULL)
				return uci;
	}
	return -1;
}

void prvInitTimersReg(void)
{
	/* Init Timer 0 registers -----------------------------------------------*/
	xTimReg[eTim0].ucOCRxA = &OCR0A;
	xTimReg[eTim0].ucOCRxB = &OCR0B;
	xTimReg[eTim0].ucTCCRxA = &TCCR0A;
	xTimReg[eTim0].ucTCCRxB = &TCCR0B;
	xTimReg[eTim0].ucTCNTx = &TCNT0;
	xTimReg[eTim0].ucTIFRx = &TIFR0;
	xTimReg[eTim0].ucTIMSKx = &TIMSK0;

	/* Init Timer 1 registers -----------------------------------------------*/
	xTimReg[eTim1].ucOCRxA = &OCR1AL;
	xTimReg[eTim1].ucOCRxB = &OCR1BL;
	xTimReg[eTim1].ucTCCRxA = &TCCR1A;
	xTimReg[eTim1].ucTCCRxB = &TCCR1B;
	xTimReg[eTim1].ucTCNTx = &TCNT1L;
	xTimReg[eTim1].ucTIFRx = &TIFR1;
	xTimReg[eTim1].ucTIMSKx = &TIMSK1;

	/* Init Timer 2 registers -----------------------------------------------*/
	xTimReg[eTim2].ucOCRxA = &OCR2A;
	xTimReg[eTim2].ucOCRxB = &OCR2B;
	xTimReg[eTim2].ucTCCRxA = &TCCR2A;
	xTimReg[eTim2].ucTCCRxB = &TCCR2B;
	xTimReg[eTim2].ucTCNTx = &TCNT2;
	xTimReg[eTim2].ucTIFRx = &TIFR2;
	xTimReg[eTim2].ucTIMSKx = &TIMSK2;
}
/* Exported functions --------------------------------------------------------*/
void vInitTimers(void)
{
	prvInitTimersReg();
}

void vInitTimerStruct(timerInitStruct_t *xTimerInfo)
{
	timerReg_t *xTimxReg = &xTimReg[xTimerInfo->eTim];

	/* Set mode -------------------------------------------------------------*/
	*xTimxReg->ucTCCRxA &= ~( (1<< WGM00) | (1<< WGM01));
	*xTimxReg->ucTCCRxB &= ~(1<< WGM02);


	switch(xTimerInfo->eMode)
	{
	case eTimerNormal:
		*xTimxReg->ucTCCRxA |= ( (0<< WGM00) | (0<< WGM01) );
		*xTimxReg->ucTCCRxB |= 	 (0<< WGM02);
		break;

	case eTimerPWMPhaseCorrect:
		if( (xTimerInfo->eTim == eTim0) || (xTimerInfo->eTim == eTim2) )
		{
			*xTimxReg->ucTCCRxA |= ( (1<< WGM00) | (0<< WGM01) );
			*xTimxReg->ucTCCRxB |= 	 (1<< WGM02);
		}
		else
		{
			*xTimxReg->ucTCCRxA |= ( (1<< WGM00) | (1<< WGM01) );
			*xTimxReg->ucTCCRxB |= 	 (0<< WGM02);
		}
		break;

	case eTimerCTC:
		if( (xTimerInfo->eTim == eTim0) || (xTimerInfo->eTim == eTim2) )
		{
			*xTimxReg->ucTCCRxA |= ( (0<< WGM00) | (1<< WGM01) );
			*xTimxReg->ucTCCRxB |= 	 (0<< WGM02);
		}
		else
		{
			*xTimxReg->ucTCCRxA |= ( (0<< WGM00) | (0<< WGM01) );
			*xTimxReg->ucTCCRxB |= 	 (0<< WGM02);
		}
		break;

	case eTimerFastPWM:
		if( (xTimerInfo->eTim == eTim0) || (xTimerInfo->eTim == eTim2) )
		{
			*xTimxReg->ucTCCRxA |= ( (1<< WGM00) | (1<< WGM01) );
			*xTimxReg->ucTCCRxB |= 	 (1<< WGM02);
		}
		else
		{
			*xTimxReg->ucTCCRxA |= ( (0<< WGM00) | (0<< WGM01) );
			*xTimxReg->ucTCCRxB |= 	 (0<< WGM02);
		}
		break;

	case eTimerPWMPhaseFreqCorrect:
		if( (xTimerInfo->eTim == eTim1))
		{
			*xTimxReg->ucTCCRxA |= ( (0<< WGM00) | (0<< WGM01) );
			*xTimxReg->ucTCCRxB |= 	 (0<< WGM02);
		}
		else
		{
			//return eHalRsrcError;
		}
		break;
	}
	/* Set OCxA and OCxB pin behavior-----------------------------------------*/
	*xTimxReg->ucTCCRxA &= ~( (1<<COM0A0) | (1<<COM0A1) | (1<<COM0B0) | (1<<COM0B1) );
	switch(xTimerInfo->eOCxAPinMode)
	{
	case eOcxxNoOperation:
		*xTimxReg->ucTCCRxA |= ( (0<<COM0A0) | (0<<COM0A1) );
		break;
	case eOCxxToggle:
		*xTimxReg->ucTCCRxA |= ( (1<<COM0A0) | (0<<COM0A1) );
		break;
	case eOCxxClear:
		*xTimxReg->ucTCCRxA |= ( (0<<COM0A0) | (1<<COM0A1) );
		break;
	case eOCxxSet:
		*xTimxReg->ucTCCRxA |= ( (1<<COM0A0) | (1<<COM0A1) );
		break;
	}
	switch(xTimerInfo->eOCxBPinMode)
	{
	case eOcxxNoOperation:
		*xTimxReg->ucTCCRxA |= ( (0<<COM0B0) | (0<<COM0B1) );
		break;
	case eOCxxToggle:
		*xTimxReg->ucTCCRxA |= ( (1<<COM0B0) | (0<<COM0B1) );
		break;
	case eOCxxClear:
		*xTimxReg->ucTCCRxA |= ( (0<<COM0B0) | (1<<COM0B1) );
		break;
	case eOCxxSet:
		*xTimxReg->ucTCCRxA |= ( (1<<COM0B0) | (1<<COM0B1) );
		break;
	}
	/* Set prescaler----------------------------------------------------------*/
	*xTimxReg->ucTCCRxB &= ~( (1<<CS20) | (1<<CS21) | (1<<CS22));
	switch(xTimerInfo->ePrescaler)
	{
	case eNoClock:
		*xTimxReg->ucTCCRxB |= ( (0<<CS20) | (0<<CS21) | (0<<CS22));
		break;
	case eNoPrescaler:
		*xTimxReg->ucTCCRxB |= ( (1<<CS20) | (0<<CS21) | (0<<CS22));
		break;
	case eDiv8Prescaler:
		*xTimxReg->ucTCCRxB |= ( (0<<CS20) | (1<<CS21) | (0<<CS22));
		break;
	case eDiv32Prescaler:
		if(xTimerInfo->eTim == eTim2)
		{
			*xTimxReg->ucTCCRxB |= ( (1<<CS20) | (1<<CS21) | (0<<CS22));
		}
		else
		{
			//return eHalRsrcError;
		}
		break;
	case eDiv64Prescaler:
		if(xTimerInfo->eTim == eTim2)
			*xTimxReg->ucTCCRxB |= ( (0<<CS20) | (0<<CS21) | (1<<CS22));
		else
			*xTimxReg->ucTCCRxB |= ( (1<<CS00) | (1<<CS01) | (0<<CS02));
		break;
	case eDiv128Prescaler:
		if(xTimerInfo->eTim == eTim2)
			*xTimxReg->ucTCCRxB |= ( (1<<CS20) | (0<<CS21) | (1<<CS22));
		else{}
			//return eHalRsrcError;
		break;
	case eDiv256Prescaler:
		if(xTimerInfo->eTim == eTim2)
			*xTimxReg->ucTCCRxB |= ( (0<<CS20) | (1<<CS21) | (1<<CS22));
		else
			*xTimxReg->ucTCCRxB |= ( (0<<CS20) | (0<<CS21) | (1<<CS22));
		break;
	case eDiv1024Prescaler:
		if(xTimerInfo->eTim == eTim2)
			*xTimxReg->ucTCCRxB |= ( (1<<CS20) | (1<<CS21) | (1<<CS22));
		else
			*xTimxReg->ucTCCRxB |= ( (1<<CS20) | (0<<CS21) | (1<<CS22));
		break;
	}

	//return eHalOk;
}

void vStartTimerInterrupt(eTimer_t eTimId, uint8_t ucInterrupt)
{
	timerReg_t *xTimxReg = &xTimReg[eTimId];

	if( (ucInterrupt & eOCFxBInterrupt) >= 1)
		*xTimxReg->ucTIMSKx |= (1<< OCIE0B);
	if ( (ucInterrupt & eOCFxAInterrupt) >= 1)
		*xTimxReg->ucTIMSKx |= (1<< OCIE0A);
	if ( (ucInterrupt & eTOVxInterrupt) >= 1)
		*xTimxReg->ucTIMSKx |= (1<< TOIE0);

	//return eHalOk;
}

void vStopTimerInterrupt(eTimer_t eTimId, uint8_t ucInterrupt)
{
	timerReg_t *xTimxReg = &xTimReg[eTimId];

	if( (ucInterrupt & eOCFxBInterrupt) >= 1)
		*xTimxReg->ucTIMSKx &= ~(1<< OCIE0B);
	if ( (ucInterrupt & eOCFxAInterrupt) >= 1)
		*xTimxReg->ucTIMSKx &= ~(1<< OCIE0A);
	if ( (ucInterrupt & eTOVxInterrupt) >= 1)
		*xTimxReg->ucTIMSKx &= ~(1<< TOIE0);

	//return eHalOk;
}

void vSetOutputCompareA(eTimer_t eTimId, uint16_t usRegisterData)
{
	timerReg_t *xTimxReg = &xTimReg[eTimId];
	*xTimxReg->ucOCRxA = (uint8_t) usRegisterData;
	//return eHalOk;
}

void vSetOutputCompareB(eTimer_t eTimId, uint16_t usRegisterData)
{
	timerReg_t *xTimxReg = &xTimReg[eTimId];
	*xTimxReg->ucOCRxB = usRegisterData;
	//return eHalOk;
}

void vReadTimerCount(eTimer_t eTimId, uint16_t *usTimerCount)
{
	timerReg_t *xTimxReg = &xTimReg[eTimId];
	*usTimerCount = *xTimxReg->ucTCNTx;
	//return eHalOk;
}

void vSetInterruptCallback(eTimer_t eTimId, uint8_t ucInterrupt, void (*callbackFunc)(void))
{

	int8_t ucIndex;

	if(callbackFunc == NULL)
		return;

	if( (ucInterrupt & eOCFxBInterrupt) >= 1)
	{
		ucIndex = prvTestCallbackAvailability(&functionCompB[eTimId][0]);
		if(ucIndex != -1)
			functionCompB[eTimId][ucIndex] = callbackFunc;
	}
	if( (ucInterrupt & eOCFxAInterrupt) >= 1)
	{
		ucIndex = prvTestCallbackAvailability(&functionCompA[eTimId][0]);
		if(ucIndex != -1)
			functionCompA[eTimId][ucIndex] = callbackFunc;
	}
	if( (ucInterrupt & eTOVxInterrupt) >= 1)
	{
		ucIndex = prvTestCallbackAvailability(&functionOVF[eTimId][0]);
		if(ucIndex != -1)
			functionOVF[eTimId][ucIndex] = callbackFunc;
	}
	//return eHalOk;
}

/* Ouput Campare with OCRA Event----------------------------------------------*/
ISR(TIMER0_COMPA_vect)
{
	for(uint8_t uci = 0; uci < TIM_NUM_CALLBACK; uci++)
	{
		if(functionCompA[eTim0][uci] != NULL)
			functionCompA[eTim0][uci]();
	}
}
ISR(TIMER1_COMPA_vect)
{
	for(uint8_t uci = 0; uci < TIM_NUM_CALLBACK; uci++)
	{
		if(functionCompA[eTim1][uci] != NULL)
			functionCompA[eTim1][uci]();
	}
}
ISR(TIMER2_COMPA_vect)
{
	for(uint8_t uci = 0; uci < TIM_NUM_CALLBACK; uci++)
	{
		if(functionCompA[eTim2][uci] != NULL)
			functionCompA[eTim2][uci]();
	}
}
/* Ouput Campare with OCRB Event----------------------------------------------*/
ISR(TIMER0_COMPB_vect)
{
	for(uint8_t uci = 0; uci < TIM_NUM_CALLBACK; uci++)
	{
		if(functionCompB[eTim0][uci] != NULL)
			functionCompB[eTim0][uci]();
	}
}
ISR(TIMER1_COMPB_vect)
{
	for(uint8_t uci = 0; uci < TIM_NUM_CALLBACK; uci++)
	{
		if(functionCompB[eTim1][uci] != NULL)
			functionCompB[eTim1][uci]();
	}
}
ISR(TIMER2_COMPB_vect)
{
	for(uint8_t uci = 0; uci < TIM_NUM_CALLBACK; uci++)
	{
		if(functionCompB[eTim2][uci] != NULL)
			functionCompB[eTim2][uci]();
	}
}
/* Ouput Campare with OCRA Event----------------------------------------------*/
ISR(TIMER0_OVF_vect)
{
	for(uint8_t uci = 0; uci < TIM_NUM_CALLBACK; uci++)
	{
		if(functionOVF[eTim0][uci] != NULL)
			functionOVF[eTim0][uci]();
	}
}
ISR(TIMER1_OVF_vect)
{
	for(uint8_t uci = 0; uci < TIM_NUM_CALLBACK; uci++)
	{
		if(functionOVF[eTim1][uci] != NULL)
			functionOVF[eTim1][uci]();
	}
}
ISR(TIMER2_OVF_vect)
{
	for(uint8_t uci = 0; uci < TIM_NUM_CALLBACK; uci++)
	{
		if(functionOVF[eTim2][uci] != NULL)
			functionOVF[eTim2][uci]();
	}
}
