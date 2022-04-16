
#include"port.h"

/*
 * @brief:
 * Los pines PF0 y PF1 corresponden al módulo I2C2 de la placa núecleo F429zi
 * 				PF0: señal de data
 * 				PF1: señal de clock
 *
 *
 */


I2C_HandleTypeDef I2cHandle;

uint8_t buffer_tx[]="";

uint8_t buffer_rx[BUFFER_RX_SIZE];




bool_t I2C_config(void){

	bool_t state = false;

	I2cHandle.Instance = I2C_PORT;
	I2cHandle.Init.ClockSpeed = 400000;
	I2cHandle.Init.DutyCycle = I2C_DUTYCYCLE_16_9;
	I2cHandle.Init.OwnAddress1 = I2C_ADD_MASTER;
	I2cHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2cHandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;


	if(HAL_I2C_Init(&I2cHandle) != HAL_OK)
	{

	  state = true;
	}else{state = false;}
	return state;
}


bool_t I2C_read(uint8_t i2c_addres, uint8_t reg_addres, uint8_t *buffer_rx, uint8_t buffer_rx_size)
{

	bool_t state = false;

	I2C_write(i2c_addres, &reg_addres, 1);


    while(HAL_I2C_Master_Receive(&I2cHandle, (uint16_t)(i2c_addres<<1), buffer_rx, (uint16_t)buffer_rx_size, (uint32_t)100) != HAL_OK)
          //HAL_I2C_Master_Transmit(hi2c, DevAddress, pData, Size, Timeout);
    {

        if (HAL_I2C_GetError(&I2cHandle) != HAL_I2C_ERROR_AF)
        {
        	state = false;
        }else{state = true;}
    }


    while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY)
    {
    	state = false;
    }

    return state;
}

bool_t I2C_write(uint8_t I2c_add, uint8_t *buffer_tx, uint16_t txbuffsz)
{
	bool_t state = false;

    while(HAL_I2C_Master_Transmit(&I2cHandle, (uint16_t)(I2c_add<<1),(uint8_t*)buffer_tx,txbuffsz,(uint32_t)100)!= HAL_OK)
    {


        if (HAL_I2C_GetError(&I2cHandle) != HAL_I2C_ERROR_AF)
        {
        	state = false;
        }else{state = true;}

    }


      while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY)
      {
    	  state = false;
      }
    return state;
}

bool_t I2C_write_byte(uint8_t i2c_add, uint8_t reg_addres, uint8_t reg_content)
{

	bool_t state = false;
	uint8_t buffer_tx[2];

	buffer_tx[0] = reg_addres;
	buffer_tx[1] = reg_content;


    while(HAL_I2C_Master_Transmit(&I2cHandle, (uint16_t)(i2c_add<<1),buffer_tx, (uint16_t)2, (uint32_t)100)!= HAL_OK)
    {


        if (HAL_I2C_GetError(&I2cHandle) != HAL_I2C_ERROR_AF)
        {
        	state = false;
        }else{state = true;}

    }


      while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY)
      {
    	  state = false;
      }

    return state;
}
