/* Header guard ------------------------------------------------------------- */
#ifndef _PIEZO_H_
#define _PIEZO_H_

/* Includes ----------------------------------------------------------------- */
#include "hal_lib.h"
#include "timer.h"

/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
void vInitPiezo(eHalGpioId_t ePiezoPin);
void vTurnPiezoOn(void);
void vTurnPiezoOff(void);
void vTurnPiezoOnForSec(uint8_t ulDelayInSec);
void vTurnPiezoOnForMs(uint32_t ulDelayInMs);

#endif /* _PIEZO_H_ */
