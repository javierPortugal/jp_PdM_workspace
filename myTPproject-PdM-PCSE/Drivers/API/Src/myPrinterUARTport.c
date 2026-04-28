/*
 * myPrinterUARTport.c
 *
 *  Created on: Apr 28, 2026
 *      Author: javie
 */


#include "myPrinterUARTport.h"

extern UART_HandleTypeDef huart1; // Asegúrate que sea la UART conectada a la impresora
#define PRINTER_TIMEOUT 1000

printerStatus_t port_UART_Transmit(uint8_t *pData, uint16_t size) {
    if (HAL_UART_Transmit(&huart1, pData, size, PRINTER_TIMEOUT) == HAL_OK) {
        return PRINTER_OK;
    }
    return PRINTER_ERROR;
}
