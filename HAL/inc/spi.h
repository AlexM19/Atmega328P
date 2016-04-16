/*******************************************************************************
  * @file			spi.h
  * @brief
  * @description
  * @author			Alexandre
  * @date			Apr 14, 2016
  * @note
  *****************************************************************************/
/* Header guard ------------------------------------------------------------- */
#ifndef HAL_INC_SPI_H_
#define HAL_INC_SPI_H_


/* Includes ----------------------------------------------------------------- */
#include "hal_lib.h"

/* Define ------------------------------------------------------------------- */
/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
extern void spi_init();
extern void spi_transfer_sync (uint8_t * dataout, uint8_t * datain, uint8_t len);
extern void spi_transmit_sync (uint8_t * dataout, uint8_t len);
extern uint8_t spi_fast_shift (uint8_t data);


#endif /* HAL_INC_SPI_H_ */
