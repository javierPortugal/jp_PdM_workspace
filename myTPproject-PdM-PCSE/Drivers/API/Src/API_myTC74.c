/*
 * API_myTC74.c
 *
 *  Created on: 27 abr 2026
 *      Author: javie
 */


#include "API_myTC74.h"
#include <stdio.h>

int8_t get_temperature(void) {
    int8_t temperatura = 0;
    uint8_t reg_temperatura = REG_TEMP;

    // Usamos la capa de abstracción (Port) para separar las capas
    if (port_I2C_Write_Temperature(TC74_ADDRESS, &reg_temperatura, 1) != PORT_OK) {
        printf("Error: Sensor no encontrado\r\n");
    } else {
        if (port_I2C_Read_Temperature(TC74_ADDRESS, (uint8_t*)&temperatura, 1) == PORT_OK) {
            printf("Temperatura actual es: %d grados C\r\n", temperatura);

            return temperatura;
        }
    }
    return -200; //este valor no lo puede dar el sensor como lectura, es solo para detectar fallo
}
