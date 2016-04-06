/* Header Guard --------------------------------------------------------------*/
#ifndef HAL_INC_GPIO_H_
#define HAL_INC_GPIO_H_

/* Include----- --------------------------------------------------------------*/
#include "hal_lib.h"

/* Exported Enum--------------------------------------------------------------*/
typedef enum
{
	ePinLow,
	ePinHigh,
}ePinState_t;

typedef enum
{
	eInputModePu =0,
	eInputModeNoPu,
	eOutputMode,

}ePinMode_t;

/* Exported Struct------------------------------------------------------------*/
typedef struct
{
	uint8_t							ucID;
	volatile uint8_t                *ucPORTx;
	volatile uint8_t				*ucDDRx;
	volatile uint8_t				*ucPINx;
	uint8_t							ucPinNumber;
	ePinMode_t						xMode;
	ePinState_t						xDefaultState;
} PinDescriptor_t;

/* Exported Functions---------------------------------------------------------*/
void vGpioInitAllPin(void);
void vGpioConfigPin(eHalGpioId_t eId);
void vGpioSetPinMode(eHalGpioId_t eId, ePinMode_t eMode);
void vGpioSetPinState(eHalGpioId_t eId, ePinState_t xState);
void vGpioTogglePinState(eHalGpioId_t eId);
ePinState_t eGpioReadPinState(eHalGpioId_t eId);

#endif /* HAL_INC_GPIO_H_ */
