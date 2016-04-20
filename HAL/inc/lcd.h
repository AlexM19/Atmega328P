/*******************************************************************************
  * @file			lcd.h
  * @brief
  * @description
  * @author			Alexandre Mercier
  * @date			Apr 18, 2016
  * @note
  *****************************************************************************/
/* Header guard ------------------------------------------------------------- */
#ifndef HAL_INC_LCD_H_
#define HAL_INC_LCD_H_

/* Includes ----------------------------------------------------------------- */
#include "hal_lib.h"

/* Define ------------------------------------------------------------------- */
#define NUM_DATA_PIN	8
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
typedef struct
{
	PinDescriptor_t xEnablePin;
	PinDescriptor_t	xReadWritePin;
	PinDescriptor_t	xRegisterPin;
	PinDescriptor_t	xDataPin[NUM_DATA_PIN];
}lcdInfo_t;

/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
void LcdInit(void);

#endif /* HAL_INC_LCD_H_ */
