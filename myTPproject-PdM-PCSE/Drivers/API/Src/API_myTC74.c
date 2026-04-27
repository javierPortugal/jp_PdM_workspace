/*
 * API_myTC74.c
 *
 *  Created on: 27 abr 2026
 *      Author: javie
 */

#include "API_myTC74.h"

#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;

#define TC74_ADDRESS (0x48 << 1)
#define REG_TEMP  0x00

int8_t temperatura = 0;
uint8_t reg = REG_TEMP;




void get_temperature (){

// 1. Escribir el puntero del registro que queremos leer
 	 if(HAL_I2C_Master_Transmit(&hi2c1, TC74_ADDRESS, &reg, 1, 100) != HAL_OK)
 	 {
 	     printf("Error: Sensor no encontrado\r\n");
 	   }else {
 	         // 2. Leer el byte de temperatura
 	     if (HAL_I2C_Master_Receive(&hi2c1, TC74_ADDRESS, (uint8_t*)&temperatura, 1, 100) == HAL_OK) {
 	        printf("Temperatura actual es: %d grados C\r\n", temperatura);
 	     }
 	   }

}

