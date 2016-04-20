/*******************************************************************************
  * @file			lcd.c
  * @brief			
  * @description
  * @author			Alexandre Mercier
  * @date			Apr 18, 2016
  * @note
  *****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static lcdInfo_t xLcdInfo =
{
	#define X_LCD(RS_PIN, E_PIN, RW_PIN, PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7)\
				  RS_PIN,				\
				  E_PIN, 				\
				  RW_PIN,				\
				  xDataPin[0] = PB0,	\
				  xDataPin[1] = PB1,	\
				  xDataPin[2] = PB2,	\
				  xDataPin[3] = PB3,	\
				  xDataPin[4] = PB4,	\
				  xDataPin[5] = PB5,	\
				  xDataPin[6] = PB6,	\
				  xDataPin[7] = PB7,	\
		LCD_DEF
	#undef X_LCD
};
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
uint8_t prvLcdIsBusy(void);
void prvLcdClearDisplay(void);
void prvLcdResetCursor(void);
void prvLcdSetEntryMode(uint8_t ucIncrement, uint8_t ucShift);
void prvLcdSetDisplay(uint8_t ucDisplay, uint8_t ucCursor, uint8_t ucBlinking);
void prvLcdSetCursor(uint8_t ucType, uint8_t ucDir);
void prvLcdSetFunction(uint8_t ucDataLength, uint8_t ucNbLine, uint8_t ucFont);
void prvLcdReadStatus(uint8_t *ucBusyFlag, uint8_t *ucAddrs);
void prvLcdSetDDRAM(uint8_t ucAddrs);
void prvLcdSetCGRAM(uint8_t ucAddrs);
void prvLcdWriteData(uint8_t ucData);

/* Private functions ---------------------------------------------------------*/
uint8_t prvLcdIsBusy(void)
{

	return 0;
}

void prvLcdClearDisplay(void)
{
	/*Reset register pin */
	/*Set the read/write pin*/
	/*Set PB1*/
	/*Set Enable pin*/
	/*Reset enable pin */
	/*Reset PB1*/
}

void prvLcdResetCursor(void)
{

}

void prvLcdSetEntryMode(uint8_t ucIncrement, uint8_t ucShift)
{

}

void prvLcdSetDisplay(uint8_t ucDisplay, uint8_t ucCursor, uint8_t ucBlinking)
{

}

void prvLcdSetCursor(uint8_t ucType, uint8_t ucDir)
{

}

void prvLcdSetFunction(uint8_t ucDataLength, uint8_t ucNbLine, uint8_t ucFont)
{

}

void prvLcdReadStatus(uint8_t *ucBusyFlag, uint8_t *ucAddrs)
{

}

void prvLcdSetDDRAM(uint8_t ucAddrs)
{

}

void prvLcdSetCGRAM(uint8_t ucAddrs)
{

}

void prvLcdWriteData(uint8_t ucData)
{

}

/* Exported functions --------------------------------------------------------*/

void LcdInit(void)
{
	/*Set pins mode*/
	vGpioSetPinMode(xLcdInfo.xEnablePin.ucID, eOutputMode);
	vGpioSetPinMode(xLcdInfo.xRegisterPin.ucID, eOutputMode);
	vGpioSetPinMode(xLcdInfo.xReadWritePin.ucID, eOutputMode);

}

