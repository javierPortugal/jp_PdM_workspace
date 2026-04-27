/*
 * API_myTC74port.h
 *
 *  Created on: 27 abr 2026
 *      Author: javie
 */

#ifndef API_INC_API_MYTC74PORT_H_
#define API_INC_API_MYTC74PORT_H_


#include "stm32f4xx_hal.h"
#include <stdbool.h>

// Definimos un tipo para el estado (así no dependemos de HAL_StatusTypeDef)
typedef enum {
    PORT_OK = 0,
    PORT_ERROR
} portStatus_t;

// Prototipos de las funciones "puente"
portStatus_t port_I2C_Write_Temperature(uint16_t devAddr, uint8_t *pData, uint16_t size);
portStatus_t port_I2C_Read_Temperature(uint16_t devAddr, uint8_t *pData, uint16_t size);

#endif /* API_INC_API_MYTC74PORT_H_ */
