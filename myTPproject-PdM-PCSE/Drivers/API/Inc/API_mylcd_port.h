/*
 * API_mylcd_port.h
 *
 *  Created on: 27 abr 2026
 *      Author: javie
 */

#ifndef API_INC_API_MYLCD_PORT_H_
#define API_INC_API_MYLCD_PORT_H_

#include "stm32f4xx_hal.h"

// Definición del manejador de I2C
extern I2C_HandleTypeDef hi2c1;
#define LCD_I2C_HANDLE  &hi2c1

// Dirección del LCD
#define MYLCD_ADDRESS   0x4E

// Prototipo de la función de bajo nivel para transmit y poder generar la abstraccion de port
HAL_StatusTypeDef LCD_IO_Transmit(uint8_t *pData, uint16_t Size);



#endif /* API_INC_API_MYLCD_PORT_H_ */
