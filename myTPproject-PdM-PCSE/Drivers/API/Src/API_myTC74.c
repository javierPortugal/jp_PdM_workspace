/*
 * API_myTC74.c
 *
 *  Created on: 27 abr 2026
 *      Author: javie
 */
/*
#include "API_myTC74.h"

void get_temperature(I2C_HandleTypeDef *hi2c) {
    int8_t temp_val = 0;
    uint8_t reg_addr = REG_TEMP;

    // 1. Apuntar al registro de temperatura
    if (HAL_I2C_Master_Transmit(hi2c, TC74_ADDRESS, &reg_addr, 1, 100) != HAL_OK) {
        printf("Error: Sensor no responde en bus I2C\r\n");
        return;
    }

    // 2. Leer el valor
    if (HAL_I2C_Master_Receive(hi2c, TC74_ADDRESS, (uint8_t*)&temp_val, 1, 100) == HAL_OK) {
        printf("Temperatura actual es: %d grados C\r\n", temp_val);
    } else {
        printf("Error: Fallo al recibir datos\r\n");
    }
}
*/

#include "API_myTC74.h"
#include <stdio.h>

int8_t get_temperature(void) {
    int8_t temperatura = 0;
    uint8_t reg_temperatura = REG_TEMP;

    // Usamos la capa de abstracción (Port)
    if (port_I2C_Write_Temperature(TC74_ADDRESS, &reg_temperatura, 1) != PORT_OK) {
        printf("Error: Sensor no encontrado\r\n");
    } else {
        if (port_I2C_Read_Temperature(TC74_ADDRESS, (uint8_t*)&temperatura, 1) == PORT_OK) {
            printf("Temperatura actual es: %d grados C\r\n", temperatura);

            return temperatura;
        }
    }
    return -200;
}
