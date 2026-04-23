#ifndef INC_API_MYLCD_I2C_H_
#define INC_API_MYLCD_I2C_H_


#include "stm32f4xx_hal.h"

/*
 * Estas definiciones se agregan para segmentar cada linea del display
 * de acuerdo a las direcciones de memoria para un lcd de 4 lineas
*/

#define LINE1 0x80|0x00
#define LINE2 0x80|0x40
#define LINE3 0x80|0x14
#define LINE4 0x80|0x54


/*
 * las funciones a utilizar con el LCD son:
 *
 * mylcd_init para inicializar hardware
 * mylcd_send_command para enviar los comandos respectivos
 * mylcd_send_string para la informacion a desplegar
 * mylcd_clear para limpiar la pantalla del lcd
 *
 */
void mylcd_init (void);

void mylcd_send_command (char command);

void mylcd_send_data (char data);

void mylcd_send_string (char *str);

void mylcd_clear (void);




#endif




