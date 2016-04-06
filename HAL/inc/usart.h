/* Header guard ------------------------------------------------------------- */
#ifndef HAL_INC_USART_H_
#define HAL_INC_USART_H_

/* Includes ----------------------------------------------------------------- */
#include "hal_lib.h"
/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
typedef enum
{
	normal_asynchronous,
	double_asynchronous,
	master_synchronous,
	slave_synchronous,
}uart_mode_t;

typedef enum
{
	baud_2400 = 2400,
	baud_4800 = 4800,
	baud_9600 = 9600,
	baud_14400 = 14400,
	baud_19200 = 19200,
	baud_28800 = 28800,
	baud_38400 = 38400,
	baud_57600 = 57600,
	baud_115200 = 115200,
	baud_230400 = 230400,

}uart_bauderate_t;

typedef enum
{
	parity_none,
	parity_even,
	parity_odd,
}uart_parity_t;

typedef enum
{
	stop_bit_1,
	stop_bit_2,
}uart_stop_bit_t;

typedef enum
{
	char_size_5,
	char_size_6,
	char_size_7,
	char_size_8,
	char_size_9,
}uart_char_size_t;

typedef enum
{
	clock_polarity_rising,
	clock_polarity_falling,
}uart_clock_polarity_t;

typedef enum
{
	eUsartBusy,
	eUsartIdle
}eUsartState_t;

/* Exported struct ---------------------------------------------------------- */
typedef struct
{
	uart_mode_t					mode;
	uart_bauderate_t			baud;
	uart_parity_t				parity;
	uart_stop_bit_t				stop_bit;
	uart_char_size_t			char_size;
	uart_clock_polarity_t		clk_polarity;
	volatile uint16_t			usBufferSize;
	volatile uint16_t			usFrameTimeout;
} usartInfo_t;

/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
void 		UsartInit		(void);
void 		UsartSend		(const uint32_t ulDataLength,const uint8_t *ucData );
uint16_t 	UsartRead		(uint32_t ulDataLength, uint8_t *ucData );
uint16_t 	UsartReadPeak	(void);
void 		UsartTickHook	(void);

#endif /* HAL_INC_USART_H_ */
