/*******************************************************************************
  * @file			lcd.c
  * @brief			Lcd driver based around the Hitachi HD44780U
  * @description	This module provide basic functionalities for LCD display that use
  *					the dot matrix liquid crystal display controller Hitachi HD44780U.
  * @author			Alexandre Mercier
  * @date			Apr 18, 2016
  * @note			By default all the pin are set to output. In function like read status
  *					they will me switch to input and then revert back to output mode.
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
	#define X_LCD(MODE, RS_PIN, E_PIN, RW_PIN, PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7)\
				  MODE,					\
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

static uint8_t ucLcdNumDataPin;
/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void prvLcdWaitUntilNotBusy(void)
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
void prvLcdWaitUntilNotBusy(void)
{
	ePinState_t eBusyFlag = ePinHigh;
	
	/*Set data pin 7 as input */
	vGpioSetPinMode(xLcdInfo.xDataPin[7].ucID,eInputModeNoPu);
	
	/*Reset register pin */
	vGpioSetPinState(xLcdInfo.xRegisterPin.ucID, ePinLow);
	
	/*Set Read/write pin */
	vGpioSetPinState(xLcdInfo.xReadWritePin.ucID, ePinHigh);
	
	do
	{
		/*Set Enable pin */
		vGpioSetPinState(xLcdInfo.xEnablePin.ucID, ePinHigh);
	
		/*Read the data pin 7*/
		eBusyFlag = eGpioReadPinState(xLcdInfo.xDataPin[7].ucID);
	
		/*Reset Enable pin */
		vGpioSetPinState(xLcdInfo.xEnablePin.ucID, ePinLow);
		
	}
	while(eBusyFlag == ePinHigh)
		
	/*Set data pin 7 as output */
	vGpioSetPinMode(xLcdInfo.xDataPin[7].ucID,eOutputMode);

	

}

void prvLcdClearDisplay(void)
{
	/*Wait until the LCD is not busy*/
	prvLcdWaitUntilNotBusy();
	
	/*Reset register pin */
	vGpioSetPinState(xLcdInfo.xRegisterPin.ucID, ePinLow);
		
	/*Reset the read/write pin*/
	vGpioSetPinState(xLcdInfo.xReadWritePin.ucID, ePinLow);
	
	/*Set Data pin 0*/
	vGpioSetPinState(xLcdInfo.xDataPin[0].ucID, ePinHigh);
	
	/*Set Enable pin*/
	vGpioSetPinState(xLcdInfo.xEnablePin.ucID, ePinHigh);
	
	/*Reset enable pin */
	vGpioSetPinState(xLcdInfo.xEnablePin.ucID, ePinLow);
	
	/*Reset Data pin 0*/
	vGpioSetPinState(xLcdInfo.xDataPin[0].ucID, ePinLow);
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
	uint8_t uci;
	
	/*Set the number of data pin*/
	if(xLcdInfo.eLcdMode == eMode4bData)
		ucLcdNumDataPin = 4;
	else
		ucLcdNumDataPin = 8;
	
	/*Set pins mode*/
	vGpioSetPinMode(xLcdInfo.xEnablePin.ucID, eOutputMode);
	vGpioSetPinMode(xLcdInfo.xRegisterPin.ucID, eOutputMode);
	vGpioSetPinMode(xLcdInfo.xReadWritePin.ucID, eOutputMode);
	
	for(uci = 0; uci < ucLcdNumDataPin; uci++)
		vGpioSetPinMode(xLcdInfo.xDataPin[uci].ucID, eOutputMode);

}

