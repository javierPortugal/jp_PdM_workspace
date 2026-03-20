/*
 * API_delay.c
 *
 *  Created on: 19 mar 2026
 *      Author: javie
 */


/* USER CODE BEGIN 0 */
#include "stm32f4xx_hal.h"
#include "API_delay.h"


void delayInit( delay_t * delay, tick_t duration ){
	delay->duration = duration;
	delay->running = false;
}

bool_t delayRead( delay_t * delay ){
	if(!delay->running) {
		delay->running = true;
		delay->startTime = HAL_GetTick();
	} else {
		tick_t tiempoActual = HAL_GetTick();
		tick_t diferencia = tiempoActual - delay->startTime;

		if(diferencia >= delay->duration){
			delay->running = false;
			return true;
		}
		return false;
	}
	return false;
}

void delayWrite( delay_t * delay, tick_t duration){
	delay->duration = duration;
}

/* USER CODE END 0 */


/* USER CODE BEGIN 2 */




