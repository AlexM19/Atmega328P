/*******************************************************************************
  * @file			I2C.h
  * @brief
  * @description
  * @author			Alexandre Mercier
  * @date			Apr 14, 2016
  * @note
  *****************************************************************************/
/* Header guard ------------------------------------------------------------- */
#ifndef _I2C_H
#define _I2C_H

/* Includes ----------------------------------------------------------------- */
#include "hal_lib.h"

/* Define ------------------------------------------------------------------- */
#define I2C_READ 0x01
#define I2C_WRITE 0x00

/* Exported macro ----------------------------------------------------------- */
/* Exported enum ------------------------------------------------------------ */
/* Exported struct ---------------------------------------------------------- */
/* Global variables --------------------------------------------------------- */
/* Exported function prototypes --------------------------------------------- */
void i2c_init(void);
uint8_t i2c_start(uint8_t address);
uint8_t i2c_write(uint8_t data);
uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);
uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
void i2c_stop(void);

#endif /*_I2C_H*/
