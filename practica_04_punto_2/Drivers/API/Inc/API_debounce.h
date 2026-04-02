/*
 * API_debounce.h
 *
 *  Created on: 1 abr 2026
 *      Author: javie
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdint.h>
#include <stdbool.h>
//#include "API_delay.h"


typedef enum{
 BUTTON_UP,
 BUTTON_FALLING,
 BUTTON_DOWN,
 BUTTON_RAISING,
 } debounceState_t;

void debounceFSM_init();		// debe cargar el estado inicial
void debounceFSM_update();		// debe leer las entradas, resolver la lógica de transición de estados y actualizar las salidas
void buttonPressed();			// debe encender el LED
void buttonReleased();			// debe apagar el LED




 //debounceState_t myEstado_t;









#endif /* API_INC_API_DEBOUNCE_H_ */
