/*
 * API_uart.h
 *
 *  Created on: 8 abr 2026
 *      Author: javie
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_


#include "API_delay.h"

// Definiciones de constantes para la UART
#define UART_MAX_STRING_LENGTH 256
#define UART_MIN_STRING_LENGTH 1
#define UART_MAX_TRANSMIT_ATTEMPTS 10
#define UART_TRANSMIT_TIMEOUT 1000
#define UART_RECEIVE_TIMEOUT 1000

// Pines de UART
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA

/** Función para inicializar la UART
  * return: true si la inicialización fue exitosa, false en caso contrario
  */
bool_t uartInit(void);

/** Función para enviar una cadena de caracteres por UART
  * pstring: Puntero al string a enviar
  */
void uartSendString(uint8_t * pstring);

/** Función para enviar una cadena de caracteres por UART con un tamaño específico
  * pstring: Puntero al string a enviar
  * size: Tamaño del string a enviar
  */
void uartSendStringSize(uint8_t * pstring, uint16_t size);

/** Función para recibir una cadena de caracteres por UART con un tamaño específico
  * pstring: Puntero al buffer donde se almacenará la cadena recibida
  * size: Tamaño del string a recibir
  */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

/** Función para saber si hubo una lectura exitosa
 *  return: true si hay nuevos datos, false en caso contrario
 */
bool isNewDataOnRx(void);

/**Función para obtener la tasa de baudios actual
 * return: La tasa de baudios actual
 */
uint32_t getCurrentBaudrate(void);

/** Función para cambiar la tasa de baudios
 *  newBaudrate: La nueva tasa de baudios a configurar
 *  return: true si el cambio fue exitoso, false en caso contrario
 */
bool_t changeCurrentBaudrate(uint32_t newBaudrate);





#endif /* API_INC_API_UART_H_ */
