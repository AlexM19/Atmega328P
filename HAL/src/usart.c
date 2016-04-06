/* Includes ------------------------------------------------------------------*/
#include "usart.h"
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private enum --------------------------------------------------------------*/
/* Private struct ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static usartInfo_t uxUSART_Info =
{
    #define X_USART(MODE,BAUD,PARITY,STOP_BIT,DATA_SIZE,CLK_POLARITY,FIFO_SIZE,FRAME_TIMEOUT )\
                   {MODE,BAUD,PARITY,STOP_BIT,DATA_SIZE,CLK_POLARITY,FIFO_SIZE,FRAME_TIMEOUT },
		USART_DEF
    #undef X_USART
};


/* Pointer for the TX buffer */
static uint8_t				*g_pucTxBuffer;
/* Pointer for the RX buffer */
static uint8_t				*g_pucRxBuffer;
/* Number of frame to transmit*/
static uint16_t 			g_usTxBufSize;
/* Number of frame to transmit*/
static uint16_t				g_usRxBufSize;
/* Number of frame transmitted */
static volatile uint16_t	g_usTxFrameCnt = 0;
/* Number of frame received*/
static volatile uint16_t	g_usRxFrameCnt = 0;
/* The state of the UART, Idle when not transmitted anything */
volatile eUsartState_t	 	g_xUsartState;
/* The frame timeout count */
volatile uint16_t			g_usFrameTimeoutCnt;

/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void UsartInit(void)
{
	uint16_t baud_setting;
	switch(uxUSART_Info.mode)
	{
		case normal_asynchronous:
			/* Set mode and disable clock polarity*/
			UCSR0C &= ~((1 <<UMSEL01) | (1 << UMSEL00) | (1<< UCPOL0));
			/* Disable double transmission speed */
			UCSR0A &= ~(1<< U2X0);
			/*Set Baud rate */
			baud_setting = (F_CPU / (uxUSART_Info.baud * 16)) - 1;
			UBRR0H = (unsigned char)(baud_setting>>8);
			UBRR0L = (unsigned char)baud_setting;
		break;

		case double_asynchronous:
			/* Set mode and disable clock polarity*/
			UCSR0C &= ~((1 <<UMSEL01) | (1 << UMSEL00) | (1<< UCPOL0));
			/* Enable double transmission speed */
			UCSR0A |=  (1<< U2X0);
			/*Set Baud rate */
			baud_setting = (F_CPU / (uxUSART_Info.baud * 8)) - 1;
			UBRR0H = (unsigned char)(baud_setting>>8);
			UBRR0L = (unsigned char)baud_setting;
		break;

		case master_synchronous:
			/* Reset mode and clock polarity bit**/
			UCSR0C &= ~((1 <<UMSEL01) | (1 << UMSEL00) | (1<< UCPOL0));
			/* Set mode to synchronous */
			UCSR0C |=  (1 << UMSEL00);
			/* Set external clock port pin as output */
			DDRD |= (1<<PD4);
			/* Disable double transmission speed */
			UCSR0A &= ~(1<< U2X0);
			/* Set clock polarity */
			if(uxUSART_Info.clk_polarity == clock_polarity_falling)
				UCSR0C |= (1 << UCPOL0);
			/*Set baud rate */
			baud_setting = (F_CPU / (uxUSART_Info.baud * 2)) - 1;
			UBRR0H = (unsigned char)(baud_setting>>8);
			UBRR0L = (unsigned char)baud_setting;
		break;

		case slave_synchronous:
			/* Reset mode and clock polarity bit*/
			UCSR0C &= ~((1 <<UMSEL01) | (1 << UMSEL00) | (1<< UCPOL0));
			/* Set mode to synchronous */
			UCSR0C |=  (1 << UMSEL00);
			/* Set external clock port pin as input */
			DDRD &= ~(1<<PD4);
			/* Disable double transmission speed */
			UCSR0A &= ~(1<< U2X0);
			/* Set clock polarity */
			if(uxUSART_Info.clk_polarity == clock_polarity_falling)
				UCSR0C |= (1 << UCPOL0);
			/*Set baud rate */
			baud_setting = (F_CPU / (uxUSART_Info.baud * 2)) - 1;
			UBRR0H = (unsigned char)(baud_setting>>8);
			UBRR0L = (unsigned char)baud_setting;
		break;

		default: break;
	}

	/*Set parity*/
	switch(uxUSART_Info.parity)
	{
		case parity_none:
			/*Reset parity bit */
			UCSR0C &= ~((1<<UPM01) | (1<<UPM00));
		break;

		case parity_even:
			/*Reset parity bit */
			UCSR0C &= ~((1<<UPM01) | (1<<UPM00));
			/* Set Even parity */
			UCSR0C |= (1<<UPM01);
		break;

		case parity_odd:
			/*Reset parity bit */
			UCSR0C &= ~((1<<UPM01) | (1<<UPM00));
			/* Set Even parity */
			UCSR0C |= (1<<UPM00);
		break;

		default: break;
	}

	/*reset stop bit*/
	UCSR0C &= ~(1<<USBS0);
	if(uxUSART_Info.stop_bit == stop_bit_2)
		UCSR0C |= (1<<USBS0);

	/*Reset char size bit*/
	UCSR0B &= ~(1<<UCSZ02);
	UCSR0C &= ~((1<<UCSZ01) | (1<<UCSZ00));
	switch(uxUSART_Info.char_size)
	{
		case char_size_5:
			/*Already set */
		break;
		case char_size_6:
			UCSR0C |= (1<<UCSZ00);
		break;
		case char_size_7:
			UCSR0C |= (1<<UCSZ01);
		break;
		case char_size_8:
			UCSR0C |= ((1<<UCSZ01) | (1<<UCSZ00));
		break;
		case char_size_9:
			UCSR0B |= (1<<UCSZ02);
			UCSR0C |= ((1<<UCSZ01) | (1<<UCSZ00));
		break;
		default: break;
	}

	/*Reset frame timeout count */
	g_usFrameTimeoutCnt = uxUSART_Info.usFrameTimeout;

	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	/*Allocate space for buffer */
	if(uxUSART_Info.usBufferSize != 0)
	{
		g_pucTxBuffer = malloc(uxUSART_Info.usBufferSize);
		g_pucRxBuffer = malloc(uxUSART_Info.usBufferSize);
	}

	/* Set the RX buffer size */
	g_usRxBufSize = uxUSART_Info.usBufferSize;

	/* Reset UART state */
	g_xUsartState = eUsartIdle;

	/* Enable RX complete Interrupt */
	UCSR0B |= (1<<RXCIE0);
}

void UsartSend(const uint32_t ulDataLength,const uint8_t *ucData )
{
	/*Wait until the USART become idle again */
	while(g_xUsartState != eUsartIdle);

	/*Set the number of frame to send */
	if(ulDataLength > uxUSART_Info.usBufferSize)
		g_usTxBufSize = uxUSART_Info.usBufferSize;
	else
		g_usTxBufSize = ulDataLength;

	/* Set the data to send into the TX buffer */
	memcpy(g_pucTxBuffer,ucData,g_usTxBufSize);

	/* Set the frame count to 0 */
	g_usTxFrameCnt = 0;

	/* Disable the RX complete  interrupt */
	UCSR0B &= ~(1<<RXCIE0);
	/* Enable the TX Buffer empty interrupt */
	UCSR0B |= (1<<UDRIE0);

	/*Wait until the USART become idle again */
	while(g_xUsartState != eUsartIdle);
}

uint16_t UsartRead(uint32_t ulDataLength, uint8_t *ucData )
{
	uint16_t usFramecnt;

	/* Wait for data to be received */
	while ( g_xUsartState == eUsartBusy);

	if(g_usRxFrameCnt > 0)
	{
		/* Disable the RX complete interrupt */
		UCSR0B &= ~(1<<RXCIE0);

		/* Get frame count and reset it */
		usFramecnt = (ulDataLength > g_usRxFrameCnt) ? g_usRxFrameCnt : ulDataLength;
		g_usRxFrameCnt = 0;

		/* Copy the RX buffer into the reception buffer */
		memcpy(ucData, g_pucRxBuffer, usFramecnt);

		/* Empty RX buffer */
		memset(g_pucRxBuffer, 0, uxUSART_Info.usBufferSize);

		/* Enable the RX complete interrupt */
		UCSR0B |= (1<<RXCIE0);
	}
	else
		usFramecnt = 0;

	return usFramecnt;
}

uint16_t UsartReadPeak(void)
{
	return g_usRxFrameCnt;
}

void UsartTickHook()
{

	if(g_usFrameTimeoutCnt > 0)
	{
		g_usFrameTimeoutCnt--;
	}
	else
	{
		/* Set the USART as Busy */
		g_xUsartState = eUsartIdle;
	}
}

/* RX complete Interrupt */
ISR(USART_RX_vect)
{
	/* If the RX buffer is not empty */
	if(g_usRxFrameCnt < g_usRxBufSize)
	{
		/* Store received frame */
		g_pucRxBuffer[g_usRxFrameCnt] = UDR0;
		/* Increment frame count */
		g_usRxFrameCnt++;
		/*Set the Usart state to busy */
		g_xUsartState = eUsartBusy;
		/*Reset frame timeout count */
		g_usFrameTimeoutCnt = uxUSART_Info.usFrameTimeout;
	}
	else
	{
		/* If the buffer is full then flush the received byte */
		uint8_t dummy = UDR0;
	}
}

/* TX Buffer is empty interrupt */
ISR(USART_UDRE_vect)
{

	if(g_usTxFrameCnt < g_usTxBufSize)
	{
		UDR0 = g_pucTxBuffer[g_usTxFrameCnt];
		g_usTxFrameCnt++;
		/*Reset frame timeout count */
		g_usFrameTimeoutCnt = uxUSART_Info.usFrameTimeout;
		/* Set the USART as Busy */
		g_xUsartState = eUsartBusy;
	}
	else
	{
		/* Disable the TX empty buffer interrupt */
		UCSR0B &= ~(1<<UDRIE0);
		/* Enable the TX complete interrupt */
		UCSR0B |= (1<<TXCIE0);
	}
}

/* TX complete interrupt */
ISR(USART_TX_vect)
{
	/* Set the USART as Busy */
	g_xUsartState = eUsartIdle;

	/* Disable the TX complete interrupt */
	UCSR0B &= ~(1<<TXCIE0);

	/* Enable the RX complete interrupt */
	UCSR0B |= (1<<RXCIE0);
}
