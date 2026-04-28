/*
 * API_mylcd_port.c
 *
 *  Created on: 27 abr 2026
 *      Author: javie
 */


#include "API_mylcd_port.h"

/**
  * @brief Encapsula la transmisión I2C de HAL para la librería LCD
  */
HAL_StatusTypeDef LCD_IO_Transmit(uint8_t *pData, uint16_t Size)
{
    return HAL_I2C_Master_Transmit(LCD_I2C_HANDLE, MYLCD_ADDRESS, pData, Size, 100);
}
