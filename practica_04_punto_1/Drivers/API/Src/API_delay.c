/*
 * API_delay.c
 *
 *  Created on: 19 mar 2026
 *      Author: Javier Portugal
 */


/* USER CODE BEGIN 0 */
#include "API_delay.h"
#include "stm32f4xx_hal.h"



void delayInit( delay_t * delay, tick_t duration ){
	// Inicializo el delay con la duración dada e inicializar como no corriendo
	  if(delay != NULL) {
	    delay->duration = duration;
	    delay->running = false;
	  }
}

bool_t delayRead( delay_t * delay ){
  // Si el delay es NULL, no debe de ejecutarse por lo quehay que devolver false
  if(delay == NULL) {
    return false;
  }

  // Si el delay no está corriendo, iniciar ->guardo el tiempo de inicio en startTime
  if(!delay->running) {
		delay->running = true;
		delay->startTime = HAL_GetTick();
	} else {
		tick_t tiempoActual = HAL_GetTick();
		tick_t diferencia = tiempoActual - delay->startTime;

    // Sacar la cuenta, si es mayor a duracion, retornar true
		if(diferencia >= delay->duration){
			delay->running = false;
			return true;
		}
		return false;
	}
	return false;
}

void delayWrite( delay_t * delay, tick_t duration){
	//verificando null
	if(delay == NULL) {
	    return;
	  }
	delay->duration = duration;
}

bool_t delayIsRunning( delay_t* delay ){
	  //verificando null
	  if(delay == NULL) {
	    return false;
	  }
	  return (delay->running);
}









/* USER CODE END 0 */






