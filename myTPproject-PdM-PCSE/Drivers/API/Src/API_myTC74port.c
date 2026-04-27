/*
 * API_myTC74port.c
 *
 *  Created on: 27 abr 2026
 *      Author: javie
 */

#include "API_myTC74port.h"

extern I2C_HandleTypeDef hi2c1; // Referencia al I2C

portStatus_t port_I2C_Write_Temperature(uint16_t devAddr, uint8_t *pData, uint16_t size) {
    if (HAL_I2C_Master_Transmit(&hi2c1, devAddr, pData, size, 100) == HAL_OK) {
        return PORT_OK;
    }
    return PORT_ERROR;
}

portStatus_t port_I2C_Read_Temperature(uint16_t devAddr, uint8_t *pData, uint16_t size) {
    if (HAL_I2C_Master_Receive(&hi2c1, devAddr, pData, size, 100) == HAL_OK) {
        return PORT_OK;
    }
    return PORT_ERROR;
}
