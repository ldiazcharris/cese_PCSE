
#include "mpu9250.h"


init_mpu_state init_state;

init_mpu_state mpu9250_init(uint8_t sense_mag[3])
{

	uint8_t buffer;
	uint8_t sensibilidad[3] = {0};


	I2C_write_byte(MPU_ADDRES,PWR_MGMNT_1,INIT_BYTE_107);
	I2C_read(MPU_ADDRES,PWR_MGMNT_1,&buffer,1);

	if (buffer == INIT_BYTE_107)
	{
		init_state.clock_st = true;
	}
	else
	{
		init_state.clock_st = false;
	}


	I2C_write_byte(MPU_ADDRES, ACCEL_CONFIG, INIT_BYTE_28);
	I2C_read(MPU_ADDRES,ACCEL_CONFIG,&buffer,1);

	if (buffer == INIT_BYTE_28)
	{
		init_state.accel_st = true;
	}
	else
	{
		//printf("\r\nMPU accelerometer scale configuration...[ NOK ]\r\n");
		init_state.accel_st = false;
	}

	I2C_write_byte(MPU_ADDRES, GYRO_CONFIG, INIT_BYTE_27);
	I2C_read(MPU_ADDRES,GYRO_CONFIG,&buffer,1);

	if (buffer == INIT_BYTE_27)
	{
		//printf(buffer, "\r\nMPU gyroscope scale configuration...[ OK ]\r\n");

		init_state.gyro_st = true;
	}
	else
	{
		init_state.gyro_st = false;
		//printf("\r\nMPU gyroscope scale configuration...[ NOK ]\r\n");
	}


	I2C_write_byte(MPU_ADDRES,ACCEL_CONFIG_FILTER, INIT_BYTE_29);
	I2C_read(MPU_ADDRES,ACCEL_CONFIG_FILTER,&buffer,1);

	if (buffer == INIT_BYTE_29)
	{
		init_state.filter_accel_st = true;
		//printf("\r\nMPU accelerometer filter configuration...[ OK ]\r\n");
	}
	else
	{
		init_state.filter_accel_st = false;
		//printf("\r\nMPU accelerometer filter configuration...[ NOK ]\r\n");
	}


	I2C_write_byte(MPU_ADDRES,GYRO_CONFIG_FILTER, INIT_BYTE_26);
	I2C_read(MPU_ADDRES,GYRO_CONFIG_FILTER,&buffer,1);

	if (buffer == INIT_BYTE_26)
	{
		init_state.filter_gyro_st = true;
		//printf("\r\nMPU gyroscope filter configuration...[ OK ]\r\n");
	}
	else
	{
		init_state.filter_gyro_st = false;
		//printf("\r\nMPU gyroscope filter configuration...[ NOK ]\r\n");
	}



	I2C_write_byte(MPU_ADDRES, CTRL_MASTER_I2C, INIT_BYTE_106);
	I2C_read(MPU_ADDRES,CTRL_MASTER_I2C,&buffer,1);

	if (buffer == INIT_BYTE_106)
	{
		init_state.user_ctrl_st = true;
		//printf("\r\nMPU I2C master disabled...[ OK ]\r\n");
	}
	else
	{
		init_state.user_ctrl_st = false;
		//printf("\r\nMPU I2C master disabled...[ NOK ]\r\n");
	}


	I2C_write_byte(MPU_ADDRES, BYPASS_CONFIG_I2C, INIT_BYTE_55);
	I2C_read(MPU_ADDRES,BYPASS_CONFIG_I2C,&buffer,1);

	if (buffer == INIT_BYTE_55)
	{
		init_state.bypass_i2c_st = true;
		//printf("\r\nMPU I2C bypass mux enabled...[ OK ]\r\n");
	}
	else
	{
		init_state.bypass_i2c_st = false;
		//printf("\r\nMPU I2C bypass mux enabled...[ NOK ]\r\n");
	}


	I2C_write_byte(MAG_ID, MAG_CTRL_CONFIG, MAG_FUSE_MODE);
	HAL_Delay(1000);
	I2C_read(MAG_ID,MAG_CTRL_CONFIG,&buffer,1);

	if (buffer == MAG_FUSE_MODE)
	{

		init_state.mag_ene_st = true;
		//printf("\r\nMPU magnetometer fuse mode...[ OK ]\r\n");
	}
	else
	{
		init_state.mag_ene_st = false;
		//printf("\r\nMPU magnetometer fuse mode...[ NOK ]\r\n");
	}


	I2C_read(MAG_ID, MAG_ASAXYZ, sensibilidad, 3);

	sense_mag[0] = (sensibilidad[0]-128)*0.5/128+1;
	sense_mag[1] = (sensibilidad[1]-128)*0.5/128+1;
	sense_mag[2] = (sensibilidad[2]-128)*0.5/128+1;


	I2C_write_byte(MAG_ID, MAG_CTRL_CONFIG, MAG_PWR_DWN_MODE);
	HAL_Delay(1000);
	I2C_read(MAG_ID, MAG_CTRL_CONFIG, &buffer,1);

	if (buffer == MAG_PWR_DWN_MODE)
	{
		init_state.mag_set_sense_st = true;
		//printf("\r\nMPU magnetometer reset...[ OK ]\r\n");
	}
	else
	{
		init_state.mag_set_sense_st = false;
		//printf("\r\nMPU magnetometer reset...[ NOK ]\r\n");
	}


	I2C_write_byte(MAG_ID, MAG_CTRL_CONFIG, MAG_CONT2_MODE);
	HAL_Delay(1000);
	I2C_read(MAG_ID,MAG_CTRL_CONFIG,&buffer,1);

	if (buffer == MAG_CONT2_MODE)
	{
		init_state.mag_set_mode_st = true;
		//printf("\r\nMPU magnetometer reset mode 2 and 16 bit output...[ OK ]\r\n");
	}
	else
	{
		init_state.mag_set_mode_st = false;
		//printf("\r\nMPU magnetometer reset mode 2 and 16 bit output...[ NOK ]\r\n");
	}


	I2C_read(MPU_ADDRES, WHO_AM_I, &buffer,1);

	if (buffer == 0x71)
	{
		init_state.who_am_i_st = true;
		//printf("\r\nWho am I...[ OK ]\r\n");
	}
	else
	{
		init_state.who_am_i_st = false;
		//printf("\r\nWho am I...[ NOK ]\r\n");
	}
	return init_state;
}


mpu_data mpu9250_getData()
{
	uint8_t acumAccelGyroRead[14] = {0};
	int16_t vectorData[10]={0};
	mpu_data mpu_vector_data;
	uint8_t mag_drdy_bit = 0; //estado de los datos en el magnetómetro 0 = normal ; 1 = data is rady
	uint8_t mag_acum_vector[7] = {0};


	I2C_read(MPU_ADDRES, ACCEL_X_High, acumAccelGyroRead, 14);

	vectorData[0] = (acumAccelGyroRead[0]<<8)|(acumAccelGyroRead[1]); //acc_x
	vectorData[1] = (acumAccelGyroRead[2]<<8)|(acumAccelGyroRead[3]); //acc_y
	vectorData[2] = (acumAccelGyroRead[4]<<8)|(acumAccelGyroRead[5]); //acc_z
	vectorData[3] = (acumAccelGyroRead[6]<<8)|(acumAccelGyroRead[7]); //temperature
	vectorData[4] = (acumAccelGyroRead[8]<<8)|(acumAccelGyroRead[9]); //gyro_x
	vectorData[5] = (acumAccelGyroRead[10]<<8)|(acumAccelGyroRead[11]); //gyro_y
	vectorData[6] = (acumAccelGyroRead[12]<<8)|(acumAccelGyroRead[13]); //gyro_z


	I2C_read(MAG_ID, MAG_READ_REG, &mag_drdy_bit, 1);

	if ((mag_drdy_bit & MAG_MASK ) == MAG_DATA_READY)
	{
		I2C_read(MAG_ID, MAG_HXL_TO_HZH_REG, mag_acum_vector,7);

		if (!(mag_acum_vector[6] & MAG_OVERFLOW))
		{
			vectorData[7] = (mag_acum_vector[0] | (mag_acum_vector[1]<<8));
			vectorData[8] = (mag_acum_vector[2] | (mag_acum_vector[3]<<8));
			vectorData[9] = (mag_acum_vector[4] | (mag_acum_vector[5]<<8));
		}
	}

	mpu_vector_data.x_accel  = (float)vectorData[0];
	mpu_vector_data.y_accel  = (float)vectorData[1];
	mpu_vector_data.z_accel  = (float)vectorData[2];
	mpu_vector_data.temp     = (float)vectorData[3];
	mpu_vector_data.x_gyro = (float)vectorData[4];
	mpu_vector_data.y_gyro = (float)vectorData[5];
	mpu_vector_data.z_gyro = (float)vectorData[6];
	mpu_vector_data.x_mag  = (float)vectorData[7];
	mpu_vector_data.y_mag  = (float)vectorData[8];
	mpu_vector_data.z_mag  = (float)vectorData[9];

	return mpu_vector_data;
}


