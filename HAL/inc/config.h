/*Header Guard ---------------------------------------------------------------*/
#ifndef HAL_INC_CONFIG_H_
#define HAL_INC_CONFIG_H_

#include "arduinoUno.h"


/******************************************************************************/
/*				        BINARY INPUT/OUPUT								      */
/******************************************************************************/

/*						 (enumID,  	PORTx,  DDRx,  PINx,	PORTPIN 	MODE,       		DefaultState)	*/
#define GPIO_DEF  X_GPIO( LED1, 	&PORTB, &DDRB, &PINB,	PB5,		eOutputMode, 		ePinLow		)\
				  X_GPIO( KEYPAD1, 	&PORTD, &DDRD, &PIND,	D2,			eOutputMode,		ePinLow		)\
				  X_GPIO( KEYPAD2, 	&PORTD, &DDRD, &PIND,	D3,			eInputModePu,		ePinLow		)\
				  X_GPIO( KEYPAD3, 	&PORTD, &DDRD, &PIND,	D4,			eOutputMode,		ePinLow		)\
				  X_GPIO( KEYPAD4, 	&PORTD, &DDRD, &PIND,	D5,			eInputModePu,		ePinLow		)\
				  X_GPIO( KEYPAD5, 	&PORTD, &DDRD, &PIND,	D6,			eOutputMode,		ePinLow		)\
				  X_GPIO( KEYPAD6, 	&PORTD, &DDRD, &PIND,	D7,			eInputModePu,		ePinLow		)\
				  X_GPIO( KEYPAD7, 	&PORTB, &DDRB, &PINB,	D8,			eInputModePu,		ePinLow		)\
				  X_GPIO( PIEZO, 	&PORTC, &DDRC, &PINC,	A0,			eOutputMode,		ePinLow		)



typedef enum
{
    #define X_GPIO(  ENUM_ID, PORTX, DDRX, PINX, PORTPIN, MODE, DEFAULTVALUE)\
                     ENUM_ID,
    GPIO_DEF
    #undef X_GPIO
    HAL_GPIO_NUM_OF_RSRC
} eHalGpioId_t;

/******************************************************************************/
/*				        			ADC								          */
/******************************************************************************/

/*								  (ENUM,	CHAN	    ) */
#define ADC_CHAN_DEF	X_ADC_CHAN(PADX,	eAdcChan6 	)\
						X_ADC_CHAN(PADY,	eAdcChan7 	)

typedef enum
{
    #define X_ADC_CHAN(  ENUM_ID, PIN)\
                     	 ENUM_ID,
	ADC_CHAN_DEF
    #undef X_ADC_CHAN
    HAL_ADC_NUM_OF_CHAN
} eHalAdcChanId_t;

/*						 (CLOCK_DIV) */
#define ADC_DEF		X_ADC(eFreqDiv128)

/******************************************************************************/
/*				        	      UART								          */
/******************************************************************************/

/*						   (MODE,				 BAUD,		PARITY,		STOP_BIT,	DATA_SIZE,		CLK_POLARITY,					FIFO_SIZE,  FRAME_TIMEOUT ) */
#define USART_DEF	X_USART(normal_asynchronous, baud_9600,	parity_none,stop_bit_1,	char_size_8, 	clock_polarity_rising,			128,		40            )

/******************************************************************************/
/*				        		  TIMER							              */
/******************************************************************************/
#define TIM_DEF				/* Comment if no timer is used  */
#define USE_SYS_TICK		/* Comment if for no system tick */
#define SYS_TICK_TIMER		eTim0
#define SYS_TICK_INT		eOCFxAInterrupt
#define TIM_NUM_CALLBACK	3

/******************************************************************************/
/*				       			  KEYPAD						 	 	      */
/******************************************************************************/

/*							(COLUNM1_PIN, 	COLUNM2_PIN, 	COLUNM3_PIN,  ROW1_PIN, 	ROW2_PIN, 	ROW3_PIN, 	ROW4_PIN) */
#define KEYPAD_DEF	X_KEYPAD(KEYPAD3,		KEYPAD1,		KEYPAD5,	  KEYPAD2,		KEYPAD7,	KEYPAD6,	KEYPAD7 )

/******************************************************************************/
/*				       			  LCD						 	 	      	  */
/******************************************************************************/
#define LCD_DEF		x_LCD(eMode8bData, RS_PIN, E_PIN, RW_PIN, PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7)

#endif /* HAL_INC_CONFIG_H_ */
