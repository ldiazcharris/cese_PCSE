
#include "accel.h"


init_mpu_state init_state;

init_mpu_state accel_init(I2C_TypeDef * I2C_PORT){
	I2C_config(I2C_PORT);

	/*
	 *
	 * Se deshabilita la posibilidad de que el mpu sea master
	 * */

	if (I2C_write(MPU_ADDRESS, CTRL_MASTER_I2C, 0b00000000u) == true){
		init_state.user_ctrl_st = true;
	}
	else{
		init_state.user_ctrl_st = false;
	}

/*
 * Se configura el módulo para que auto-seleccione la fuente de reloj (interna o externa)
 * */

	if (I2C_write(MPU_ADDRESS, PWR_MGMNT_1,  0b00000001u) == true){
		init_state.clock_st = true;
	}
	else{
		init_state.clock_st = false;
	}

/*
 * Se configura el módulo para deshabilitar el giroscopio
 * */

	if (I2C_write(MPU_ADDRESS, PWR_MGMNT_2,  0b00001111u) == true){
			init_state.gyro_disable_st = true;
	}
	else{
			init_state.gyro_disable_st = false;
	}

/*
 * Se configura el módulo para deshabilitar el magnetómetro
 * */

	if (I2C_write(MAG_ID, MAG_CTRL_CONFIG, 0b00000000) == true){
		init_state.mag_set_sense_st = true;

	}
	else{
		init_state.mag_set_sense_st = false;
	}

/*
 * Se configura la escala de medición del acelerómetro se escoge 4g
 * */

	if (I2C_write(MPU_ADDRESS, ACCEL_CONFIG, 0b00001000u) == true){
		init_state.accel_st = true;
	}
	else{
		init_state.accel_st = false;
	}

/*
 * Se configura el bloque de filtrado del acelerómetro
 * */

	if (I2C_write(MPU_ADDRESS, ACCEL_CONFIG_FILTER, 0b00000101) == true ){
		init_state.filter_accel_st = true;
	}
	else{
		init_state.filter_accel_st = false;
	}


/*
 * Se deshabilita el modo bypass porque no se usan sensores externos
 * */
	if (I2C_write(MPU_ADDRESS, BYPASS_CONFIG_I2C, 0b00000000) == true){
		init_state.bypass_i2c_st = true;
	}
	else{
		init_state.bypass_i2c_st = false;
	}

	return init_state;
}


accel_data accel_getData(){
	uint8_t acum_accel_data_bits[6] = {0};
	accel_data accel_data;

	I2C_read(MPU_ADDRESS, ACCEL_X_High, acum_accel_data_bits, 6);

	accel_data.x_accel  = (double)((acum_accel_data_bits[0]<<8)|(acum_accel_data_bits[1]));
	accel_data.y_accel  = (double)((acum_accel_data_bits[2]<<8)|(acum_accel_data_bits[3]));
	accel_data.z_accel  = (double)((acum_accel_data_bits[4]<<8)|(acum_accel_data_bits[5]));

	return accel_data;
}


