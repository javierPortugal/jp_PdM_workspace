/*
 * myPrinterUART.c
 *
 *  Created on: 23 abr 2026
 *      Author: javie
 */

#include "myPrinterUART.h"
#include <string.h>

void Printer_PrintString(char *str) {
    port_UART_Transmit((uint8_t *)str, strlen(str));
}

void Printer_NextLine(void) {
    port_UART_Transmit((uint8_t *)PRINTER_LINE_SPACE, 2);
}

void Printer_PrintDateTime(char *label, char *data) {
    Printer_NextLine();
    Printer_PrintString(label);
    Printer_NextLine();
    Printer_PrintString(data);
    Printer_NextLine();
}

void Printer_PrintTemperature(char *label, char *data) {
    Printer_NextLine();
    Printer_PrintString(label);
    Printer_NextLine();
    Printer_PrintString(data);
    Printer_NextLine();
}
