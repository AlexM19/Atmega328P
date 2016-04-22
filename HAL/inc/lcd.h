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
#define LCD_MAX_DATA_PIN	8
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
typedef enum
{
	eMode4bData,
	eMode8bData,
}eLcdMode_t;

/* Exported struct ---------------------------------------------------------- */
typedef struct
{
	eLcdMode_t		eLcdMode;
	PinDescriptor_t xEnablePin;
	PinDescriptor_t	xReadWritePin;
	PinDescriptor_t	xRegisterPin;
	PinDescriptor_t	xDataPin[LCD_MAX_DATA_PIN];
}lcdInfo_t;

/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
void LcdInit(void);

#endif /* HAL_INC_LCD_H_ */
