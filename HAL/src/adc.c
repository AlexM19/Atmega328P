//For now this module only support single conversion mode...
//Voltage reference is automatically set AVCC with external capacitor at AREF pin
//It also have no filter what so ever...

/* Include -------------------------------------------------------------------*/
#include "adc.h"

/* Private variable-----------------------------------------------------------*/
volatile static uint8_t ucChan = 0;
/* Private struct-------------------------------------------------------------*/
static chanInfo_t xChanInfo[HAL_ADC_NUM_OF_CHAN] =
{
    #define X_ADC_CHAN(ENUM_ID, CHAN) \
                  	  {ENUM_ID, CHAN},
		ADC_CHAN_DEF
    #undef X_ADC_CHAN
};

static adcInfo_t xAdcInfo =
{
	#define X_ADC(CLOCKDIV)\
				  CLOCKDIV,
		ADC_DEF
	#undef X_ADC
};

/* Public Function------------------------------------------------------------*/
void vAdcInit(void)
{
	/* Set ADC Input clock division */
	ADCSRA &= ~(eFreqDiv128);
	ADCSRA |= xAdcInfo.eFreqDiv;

	/* Enable Interrupt */
	ADCSRA |= (1<<ADIE);

	/* Set voltage reference to AVCC with external capacitor at AREF pin */
	ADMUX  |=  (1<<REFS0);

	/* Disable ADC channel digital input */
	for(uint8_t uci = 0; uci < HAL_ADC_NUM_OF_CHAN; uci++)
	{
		if(xChanInfo[uci].eChan < eAdcChan6)
		{
			DIDR0 |= (1<< xChanInfo[uci].eChan);
		}
	}

}

void vAdcStart(void)
{
	/* Enable ADC */
	ADCSRA |= (1<<ADEN);

	/* Set channel */
	ADMUX &= ~(eAdcChan7);
	ADMUX |= xChanInfo[0].eChan;

	/* Start conversion */
	ADCSRA |= (1<<ADSC);

}

void vAdcStop(void)
{
	/* Disable ADC */
	ADCSRA &= ~(1<<ADEN);
}

void vAdcChangeClockDiv(eFreqDiv_t eClockDiv)
{
	vAdcStop();

	/* Reset clock division */
	ADCSRA &= ~(eFreqDiv128);
	/* Set clock division */
	ADCSRA |= eClockDiv;

	vAdcStart();
}

uint16_t usAdcGetChanValue(eHalAdcChanId_t eChanId)
{
	return xChanInfo[eChanId].usChanValue;
}

/* Interrupt Handler-----------------------------------------------------------*/
ISR(ADC_vect)
{
	/* Get the converted value by accessing the lower register first */
	xChanInfo[ucChan].usChanValue =  (ADCL) | (ADCH << 8) ;

	/* Increment the channel index */
	ucChan++;
	if(ucChan == HAL_ADC_NUM_OF_CHAN) ucChan = 0;

	/* Reset the channel multiplexer */
	ADMUX  &=  ~(eAdcChan7);

	/* Reset the channel multiplexer */
	ADMUX  |=  xChanInfo[ucChan].eChan;

	/* Start a new conversion */
	ADCSRA |= (1<<ADSC) ;
}
