/* Header guard ------------------------------------------------------------- */
#ifndef _TIMER_H_
#define _TIMER_H_

/* Includes ----------------------------------------------------------------- */
#include "hal_lib.h"

/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */


typedef enum
{
	eTimerNormal,
	eTimerCTC,
	eTimerFastPWM,
	eTimerPWMPhaseCorrect,
	eTimerPWMPhaseFreqCorrect,
}eTimerMode_t;

typedef enum
{
	eNoClock,
	eNoPrescaler,
	eDiv8Prescaler,
	eDiv32Prescaler,
	eDiv64Prescaler,
	eDiv128Prescaler,
	eDiv256Prescaler,
	eDiv1024Prescaler,
}eTimerPrescaling_t;

typedef enum
{
	eOcxxNoOperation,
	eOCxxToggle,
	eOCxxClear,
	eOCxxSet,
} eTimerOCxxPinMode_t;

typedef enum
{
	eTimerNoInterrupt 	= 0x01,
	eOCFxBInterrupt		= 0x02,
	eOCFxAInterrupt		= 0x04,
	eTOVxInterrupt		= 0x08,
} eTimerIterrupt_t;

typedef enum
{
	eTim0 = 0,
	eTim1,
	eTim2,
	eNumberOfTim
} eTimer_t;

/* Exported struct ---------------------------------------------------------- */
typedef struct
{
	eTimer_t 			eTim;
	eTimerMode_t 		eMode;
	eTimerOCxxPinMode_t	eOCxAPinMode;
	eTimerOCxxPinMode_t	eOCxBPinMode;
	eTimerPrescaling_t	ePrescaler;
} timerInitStruct_t;

/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
void vInitTimers(void);
void vInitTimerStruct(timerInitStruct_t *xTimerInfo);
void vStartTimerInterrupt(eTimer_t eTimId,uint8_t ucInterrupt);
void vStopTimerInterrupt(eTimer_t eTimId,uint8_t ucInterrupt);
void vSetOutputCompareA(eTimer_t eTimId, uint16_t usRegisterData);
void vSetOutputCompareB(eTimer_t eTimId, uint16_t usRegisterData);
void vReadTimerCount(eTimer_t eTimId, uint16_t *usTimerCount);
void vSetInterruptCallback(eTimer_t eTimId, uint8_t ucInterrupt, void (*callbackFunc)(void));

#endif /* _TIMER_H_ */
