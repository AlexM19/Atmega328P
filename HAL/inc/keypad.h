/* Header Guard---------------------------------------------------------------*/
#ifndef HAL_INC_KEYPAD_H_
#define HAL_INC_KEYPAD_H_

/* Include ------------------------------------------------------------------*/
#include "gpio.h"

/* Exported Enum--------------------------------------------------------------*/
typedef enum
{
	eKeyReleased=0,
	eKeyPressed,
}eKeyState_t;

/* Exported Defines-----------------------------------------------------------*/
/* Exported structure---------------------------------------------------------*/
/* Exported variable----------------------------------------------------------*/
/* Exported Prototype---------------------------------------------------------*/
void vKeypadRefresh(void);
void vResetKeypad(void);
uint8_t eKeyIsPressed(uint8_t ucKey);
uint8_t	eKeyIsReleased(uint8_t ucKey);
eKeyState_t eGetCurrentKeyState(uint8_t ucKey);


#endif /* HAL_INC_KEYPAD_H_ */
