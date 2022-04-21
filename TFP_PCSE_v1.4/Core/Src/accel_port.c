
#include <accel_port.h>

/*
 * @brief:
 * Los pines PF0 y PF1 corresponden al módulo I2C2 de la placa núecleo F429zi
 * 				PF0: señal de data
 * 				PF1: señal de clock
 *
 *Los pines PB8 y PB9 corresponden al módulo I2C1 de la placa núecleo F429zi
 * 				PB8: señal de clock
 * 				PB9: señal de data
 *
 *
 */


I2C_HandleTypeDef I2cHandle;

bool_t I2C_config(I2C_TypeDef * I2C_PORT){

	bool_t state = false;

	I2cHandle.Instance = I2C_PORT;
	I2cHandle.Init.ClockSpeed = 400000;
	I2cHandle.Init.DutyCycle = I2C_DUTYCYCLE_2;
	I2cHandle.Init.OwnAddress1 = I2C_ADD_MASTER;
	I2cHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2cHandle.Init.OwnAddress2 = 0;
	I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2cHandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;


	if(HAL_I2C_Init(&I2cHandle) != HAL_OK){

	  state = true;
	}else{
		state = false;
	}



	if (HAL_I2CEx_ConfigAnalogFilter(&I2cHandle, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	  {
		state = true;
	  }else
	  {
		  state = false;
	  }



	  if (HAL_I2CEx_ConfigDigitalFilter(&I2cHandle, 0) != HAL_OK)
	  {
		  state = true;
	  }else
	  {
		  state = false;
	  }

	  return state;
}



bool_t I2C_read(uint8_t i2c_addres, uint8_t reg_addres, uint8_t *buffer_rx, uint8_t buffer_rx_size){

	bool_t state = false;


    while(HAL_I2C_Mem_Read(&I2cHandle, (uint16_t)(i2c_addres<<1), reg_addres, 1u, buffer_rx, 1u, 100u) != HAL_OK){

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


bool_t I2C_write(uint8_t i2c_add, uint8_t reg_addres, uint8_t reg_content){

	bool_t state = false;


    while(HAL_I2C_Mem_Write(&I2cHandle, i2c_add, reg_addres, 1u, &reg_content, 1u, 100u) != HAL_OK)
    {


        if (HAL_I2C_GetError(&I2cHandle) != HAL_I2C_ERROR_AF){
        	state = false;
        }else{state = true;}

    }

      while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY){
    	  state = false;
      }

    return state;
}
