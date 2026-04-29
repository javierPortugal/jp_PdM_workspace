/*
 * myPrinterUART.h
 *
 *  Created on: 23 abr 2026
 *      Author: javie
 */

#ifndef API_INC_MYPRINTERUART_H_
#define API_INC_MYPRINTERUART_H_

#include "myPrinterUARTport.h"

// Comandos comunes para impresoras térmicas
// estos se crearon de acuerdo al comportamiento de la impresora
#define PRINTER_LINE_SPACE "\n\r"
#define PRINTER_FINAL_SPACE "\n\n\r"

void Printer_PrintString(char *str);
void Printer_PrintDateTime(char *label, char *data);
void Printer_PrintTemperature(char *label, char *data);
void Printer_NextLine(void);





#endif /* API_INC_MYPRINTERUART_H_ */
