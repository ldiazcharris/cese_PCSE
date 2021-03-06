#ifndef INC_MPU9250_H_
#define INC_MPU9250_H_

// Includes
#include "accel_port.h"

	// Definción de MACROS

/*
 * Estas MACROS corresponden a cada uno de los registros del MPU9250
 *
 * */

// MACROS para registros del acelerómetro y el giroscopio
	#define MPU_ADDRESS 0x68
	#define PWR_MGMNT_1 107
	#define PWR_MGMNT_2 108
	#define CTRL_MASTER_I2C 106
	#define BYPASS_CONFIG_I2C 55
	#define WHO_AM_I 117

//MACROS para registros relacionados con el Acelerómetro
	#define ACCEL_CONFIG 28
	#define ACCEL_CONFIG_FILTER 29
	#define ACCEL_X_High 59  //Bits más significativos del acelerómetro

// MACROS para registros del magnetómetro
	#define MAG_ID 0
	#define MAG_CTRL_CONFIG 10
	#define MAG_CTRL_CONFIG2 11


// Definición de estructuras

/*
 * @Brief. Esta estructura permite almacenar los datos de las mediciones transmitidas por
 * el módulo, de una forma compacta.
 * */

	typedef struct {
		float x_accel;
		float y_accel;
		float z_accel;

	}accel_data;

/*
 * @Brief. Esta estructura permite almacenar los estados de la inicialización de los sensores
 * del módulo. De esta forma el programador podrá consultarlas en cualquier momento.
 * */

	typedef struct init_mpu_state {
		bool_t clock_st;
		bool_t accel_st;
		bool_t gyro_disable_st;
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

/*
 * @Brief. Esta función permite inicializar por defecto el módulo MPU-9250 como acelerometro.
 * Estas configuraciones son:
	 * Habilita el Acelerómetro. setea el rango dinámico con escala 4g y el filtro pasabajos.
	 * Deshabilita el Giroscopo.
	 * Deshabilita el Magnetómetro
 * Si el usuario de este driver desea habilitar otras configuraciones deberá disponer del
 * manual del módulo para modificar las inicializaciones y usar las funciones de escritura
 * y lectura declaradas en accel_port.h.
 *
 * Esta función recibe como parámetro el puerto I2C al cual se va a conectar el módulo
 * Con el objetivo de hacer las configuraciones de comunicación I2C correspodientes
 *
 * */

	init_mpu_state accel_init(I2C_TypeDef * I2C_PORT);


/*
 * @Brief. Esta función permite leer por defecto el módulo MPU-9250.
 * Acelerometro, Giroscopio y magnetometro
 *
 * Esta función retorna una estructura del tipo "mpu_data", con los valores del acelerometro
 * en los ejes x, y, z.
 *
 * */

	accel_data accel_getData();


#endif
