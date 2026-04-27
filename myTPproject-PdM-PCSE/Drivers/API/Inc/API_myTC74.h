/*
 * API_myTC74.h
 *
 *  Created on: 27 abr 2026
 *      Author: javie
 */

#ifndef API_INC_API_MYTC74_H_
#define API_INC_API_MYTC74_H_
/*
#include "stm32f4xx_hal.h"
#include <stdio.h> // Para el printf

#define TC74_ADDRESS (0x48 << 1)
#define REG_TEMP     0x00

// Agregamos parámetros para que sea flexible
void get_temperature(I2C_HandleTypeDef *hi2c);
*/

#include "API_myTC74port.h" // Importante: incluimos el port

#define TC74_ADDRESS (0x48 << 1)
#define REG_TEMP     0x00

int8_t get_temperature(void);



#endif /* API_INC_API_MYTC74_H_ */
