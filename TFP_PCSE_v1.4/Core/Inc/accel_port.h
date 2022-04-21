#ifndef INC_ACCEL_PORT_H_
#define INC_ACCEL_PORT_H_

	#include "stm32f4xx_hal.h"
	#include "stdbool.h"


	#define I2C_ADD_MASTER        		0x00

	typedef bool bool_t;

	bool_t I2C_config(I2C_TypeDef * I2C_PORT);

	bool_t I2C_read(uint8_t i2c_addres, uint8_t reg_addres, uint8_t *buffer_rx, uint8_t buffer_rx_size);

	bool_t I2C_write(uint8_t I2c_add, uint8_t reg_addres, uint8_t reg_content);


#endif
