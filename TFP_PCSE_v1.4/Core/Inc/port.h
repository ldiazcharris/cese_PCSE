#ifndef INC_PORT_H_
#define INC_PORT_H_

#include "stm32f4xx_hal.h"
#include "stdbool.h"

typedef bool bool_t;

bool_t I2C_config(void);

bool_t I2C_read(uint8_t i2c_addres, uint8_t reg_addres, uint8_t *buffer_rx, uint8_t buffer_rx_size);

bool_t I2C_write(uint8_t i2c_add, uint8_t *buffer_rx, uint16_t buffer_tx_size);

bool_t I2C_write_byte(uint8_t I2c_add, uint8_t reg_addres, uint8_t reg_content);

void WHO_AM_I_vTest();

#define I2C_ADD_MASTER        				0x68F

#define I2C_PORT	                   		I2C2

#define SIZE_BUFFER(buffer)   				(sizeof(buffer)/sizeof(*(buffer)))

#define BUFFER_TX_SIZE                      (SIZE_BUFFER(buffer_tx) - 1)

#define BUFFER_RX_SIZE                      BUFFER_TX_SIZE


#endif
