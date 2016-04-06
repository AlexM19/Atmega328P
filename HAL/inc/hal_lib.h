/* Header guard ------------------------------------------------------------- */
#ifndef HAL_INC_HAL_LIB_H_
#define HAL_INC_HAL_LIB_H_
/* Includes ----------------------------------------------------------------- */

/* AVR Library */
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
/* C Library */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
/* HAL Configuration */
#include "config.h"
#include "gpio.h"
#include "adc.h"
#include "usart.h"
#include "keypad.h"
#include "timer.h"
#include "piezo.h"

/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
typedef enum
{
	eTrue,
	eFalse,
}eBool_t;

typedef enum
{
	eHalOk,
	eHalError,
	eHalRsrcError,
	eHalTimeout,
}eHalError_t;

/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
void vHalInit(void);
void vHalProcess(void);
void vHalRegisterToSysTick(void (*callbackFunc)(void));

#endif /* HAL_INC_HAL_LIB_H_ */
