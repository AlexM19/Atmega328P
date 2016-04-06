/* Header guard --------------------------------------------------------------*/
#ifndef HAL_INC_ADC_H_
#define HAL_INC_ADC_H_

/* Include -------------------------------------------------------------------*/
#include "hal_lib.h"

/* Exported Enum -------------------------------------------------------------*/
typedef enum
{
	eFreqDiv2 = 1,
	eFreqDiv4,
	eFreqDiv8,
	eFreqDiv16,
	eFreqDiv32,
	eFreqDiv64,
	eFreqDiv128,
}eFreqDiv_t;

typedef enum
{
	eAdcChan0 = 0,
	eAdcChan1	 ,
	eAdcChan2	 ,
	eAdcChan3	 ,
	eAdcChan4	 ,
	eAdcChan5	 ,
	eAdcChan6	 ,
	eAdcChan7	 ,
}eAdcChan_t;

/* Exported Struct------------------------------------------------------------*/
typedef struct
{
	uint8_t 			ucChanId;
	eAdcChan_t 			eChan;
	volatile uint16_t 	usChanValue;

}chanInfo_t;

typedef struct
{
	eFreqDiv_t eFreqDiv;

}adcInfo_t;

/* Exported Function ---------------------------------------------------------*/
void 		vAdcInit			(void);
void 		vAdcStart			(void);
void 		vAdcStop			(void);
void 		vAdcChangeClockDiv	(eFreqDiv_t eClockDiv);
uint16_t 	usAdcGetChanValue	(eHalAdcChanId_t eChanId);


#endif /* HAL_INC_ADC_H_ */
