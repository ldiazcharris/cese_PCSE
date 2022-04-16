#ifndef INC_MPU9250_H_
#define INC_MPU9250_H_

// Includes
#include"port.h"

	// Definción de MACROS

	/* Estas MACROS corresponden a cada uno de los registros del MPU9250*/

	// MACROS para el acelerómetro y el giroscopio
	#define MPU_ADDRES 0x68 //0b1101000
	#define GYRO_CONFIG_FILTER 26 //0x1A
	#define GYRO_CONFIG 27 //0x1B
	#define ACCEL_CONFIG 28
	#define ACCEL_CONFIG_FILTER 29 //0x1D
	#define ACCEL_X_High 59  //Bits más significativos del acelerómetro
	#define PWR_MGMNT_1 107 //0x6B
	#define CTRL_MASTER_I2C 106 //0x6A
	#define BYPASS_CONFIG_I2C 55 //0x37
	#define WHO_AM_I 117

	//MACROS de configuración de Accel y Gyro

	#define INIT_BYTE_107 0b00000001   //0b00000001
	#define INIT_BYTE_28 0b00001000
	#define init_byte_106 0b00000001
	#define init_byte_104 0b00000111
	#define INIT_BYTE_27 0b00001000
	#define INIT_BYTE_29 0b00000101
	#define INIT_BYTE_26 0b00000101
	#define INIT_BYTE_106 0b00000000
	#define INIT_BYTE_55 0b00000010

	// MACROS para el magnetómetro
	#define MAG_ID 0x00 //id is: 0x48
	#define MAG_CTRL_CONFIG 10 //0x0A
	#define MAG_ASAXYZ 16 //0x10
	#define MAG_PWR_DWN_MODE 0b00000000 //Power-down mode
	#define MAG_SING_MODE 0b00000001 //SINGLE MEASURE mode
	#define MAG_CONT1_MODE 0b00000010 //CONTINUOUS mode 1 - 14 bits
	#define MAG_CONT2_MODE 0b00010110 //CONTINUOUS mode 2 - 16 bits
	#define MAG_EXTT_MODE 0b00000100 //External trigger measurement mode
	#define MAG_SELFT_MODE 0b00001000 //Self-test mode
	#define MAG_FUSE_MODE 0b00011111 //fuse mode
	#define MAG_READ_REG 2 //0x02
	#define MAG_MASK 0x01
	#define MAG_DATA_READY 0x01
	#define MAG_HXL_TO_HZH_REG 0x03
	#define MAG_OVERFLOW 0x9

	// Definición de estructuras

	typedef struct {
		float x_accel;
		float y_accel;
		float z_accel;
		float temp;
		float x_gyro;
		float y_gyro;
		float z_gyro;
		float x_mag;
		float y_mag;
		float z_mag;
	}mpu_data;


	typedef struct init_mpu_state {
		bool_t clock_st;
		bool_t accel_st;
		bool_t gyro_st;
		bool_t filter_accel_st;
		bool_t filter_gyro_st;
		bool_t user_ctrl_st;
		bool_t bypass_i2c_st;
		bool_t mag_ene_st;
		bool_t mag_set_sense_st;
		bool_t mag_set_mode_st;
		bool_t who_am_i_st;
	}init_mpu_state;

	// Definición de Funciones

	init_mpu_state mpu9250_init(uint8_t sense_mag[3]);

	mpu_data mpu9250_getData();


#endif
