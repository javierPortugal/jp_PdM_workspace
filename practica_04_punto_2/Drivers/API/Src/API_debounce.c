/*
 * API_debounce.c
 *
 *  Created on: 1 abr 2026
 *      Author: javie
 */

//#include "API_delay.h"
//#include "API_delay.c"
//#include "main.h"
#include "API_debounce.h"
#include "API_delay.h"
#include "stm32f4xx_hal.h"

#define STARTTIME		0
#define DEBOUNCETIME	4
#define MEDIOSEG		500
#define CIENMILISEG		100
#define CUARENTAMILISEG	40
#define UNSEG			1000

#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

//const tick_t TIEMPOS[] = {MEDIOSEG,CIENMILISEG,CIENMILISEG,UNSEG,CUARENTAMILISEG};
debounceState_t myEstado_t;




void debounceFSM_init(){
	// debe cargar el estado inicial y hacer RESET en el LD2


	myEstado_t = BUTTON_UP;
	buttonReleased();

}

void debounceFSM_update(){
	//debe leer las entradas, resolver la lógica de
	// transición de estados y actualizar las salidas



	  switch (myEstado_t){

		  case BUTTON_UP:

			  //asigna el estado Button_up y asigna los estados siguientes dependiendo de la transicion
			  buttonReleased();

			  if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)){

				  myEstado_t = BUTTON_UP;
			  }
			  if (!HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)){

				  myEstado_t = BUTTON_FALLING;
			  }


			  break;

		  case BUTTON_FALLING:

			  	  //aplica el tiempo para realizar el debounce y verificar que
			  	  //efectivamente se presiono el boton azul

		  		  if(delayRead(&myDelay)){

		  			if (!HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)){

		  				myEstado_t = BUTTON_DOWN;
		  			}

		  		  }

		  		  break;

		  case BUTTON_DOWN:
			  	  //modifica la salida de acuerdo a la liberacion del boton azul y asigno el nuevo estado
			  	  	  buttonPressed();

			  	  	  if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)){

			  	  		  myEstado_t = BUTTON_RAISING;

			  	  	  }

			  	  	  if (!HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)){

			  	  		  myEstado_t = BUTTON_DOWN;
			  	  				  }


		  	  		  break;

		  case BUTTON_RAISING:
			  //aplica el tiempo para realizar el debounce y verificar que
			  //efectivamente se libero el boton azul

			  	  	  if(delayRead(&myDelay)){

			  		  	if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)){

			  		  		myEstado_t = BUTTON_UP;
			  		  	}

			  		  }


		  	  	  		  break;
	//Fin del case
		  }

}

void buttonPressed(){
	// debe encender el LED
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, SET);

}
void buttonReleased(){
	// debe apagar el LED
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, RESET);

}
