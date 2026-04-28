/*
 * myPrinterUARTport.h
 *
 *  Created on: Apr 28, 2026
 *      Author: javie
 */

#ifndef API_INC_MYPRINTERUARTPORT_H_
#define API_INC_MYPRINTERUARTPORT_H_


#include "stm32f4xx_hal.h"
#include <string.h>

typedef enum {
    PRINTER_OK = 0,
    PRINTER_ERROR
} printerStatus_t;

// Función "puente" para enviar datos por UART
printerStatus_t port_UART_Transmit(uint8_t *pData, uint16_t size);




#endif /* API_INC_MYPRINTERUARTPORT_H_ */
