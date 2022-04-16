# Repositorio TP final
## Asignatura: Protocoloas de Comunicación en Sistemas Embebidos

### Descripción del proyecto

El presente proyecto implementa un driver para obtener los datos del módulo MPU-9250 que cuenta con tres tipos de sensores a saber: 
    - Acelerómetro
    - Giroscopio 
    - Temperatura
    - Magnetómetro

El driver fue desaarrollado para la plca Nucleo F429zi, e implementa el módulo I2C de la misma. El driver se basa en la comunicación I2C2, de la placa Nucleo. Por lo tanto, a continuación se describen los pines que se requieren conectar en la placa:
    - SDA:
        - Pin: GPIO_PIN_0
        - Puerto: GPIOF
    - SCL:
        - Pin: GPIO_PIN_1
        - Puerto: GPIOF

Los pines correspondientes del módulo MPU-9250 deberán conectarse a estos pines de la placa Nucleo F429zi.

### Advertencia:

    - Para otras placas o microcontroladores, deberá revisarse la distribución de pines correspondientes al puerto I2C2.

    - Si el usuario de este driver quisiera cambiar el puerto I2C del microcontrolador que use, puede dirigirse al archivo "port.h" y cambiar el valor de la MACRO denominada I2C_PORT, por el puerto I2C de su preferencia e igualmente deberá revisar la distribución de pines correspondientes.

## Contenido del driver:
El driver está distribuido en 4 archivos:

1. ***port.h***
2. ***port.c***
3. ***mpu9250.h***
4. ***mpu9250.c***