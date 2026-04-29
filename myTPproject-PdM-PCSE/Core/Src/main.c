/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <API_mylcd_i2c.h>
#include <API_myRTC_i2c.h>
#include "API_myTC74.h"
#include <myPrinterUART.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */


#define ONESECONDS   1000



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

// Redirigir printf a UART2
int __io_putchar(int ch) {
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
typedef bool bool_t;
bool_t readButton_Hora();
bool_t readButton_Fecha();
bool_t readButton_Temperatura();
bool_t readButton_Printer();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
   //set_time(00, 52, 8, 3, 22,4, 26);
   mylcd_init();

   int8_t my_temperatura = 0;


   //monitore por serial y Tera term

   printf("Ingresando en Main despues de Inicializaciones...\r\n");
#define PORTGPIO GPIOC
#define BOTON_AZUL_HORA GPIO_PIN_13
#define BOTON_BLANCO_FECHA GPIO_PIN_11
#define BOTON_ROJO_TEMP GPIO_PIN_12
#define BOTON_NEGRO_PRINTER GPIO_PIN_10


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  	typedef enum{
  	 INICIAL =0,
  	 LECTURA_TIEMPO_HORA,
	 LECTURA_TIEMPO_FECHA,
  	 LECTURA_TEMPERATURA,
	 IMPRESION_TIEMPO_TEMPERATURA,
  	 } mySequenceState_t;


  	mySequenceState_t myEstado_t;

  	myEstado_t = INICIAL;

  	 mylcd_clear ();


  while (1)
  {


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	  switch (myEstado_t){

	  	  case INICIAL:
	  		  mylcd_put_cursor(LINE1);
	  		  mylcd_send_string("Azul -> Hora");
	  		  mylcd_put_cursor(LINE2);
	  		  mylcd_send_string("Blanco -> Fecha");
	  		  mylcd_put_cursor(LINE3);
	  		  mylcd_send_string("Rojo -> Temperatura");
	  		  mylcd_put_cursor(LINE4);
	  		  mylcd_send_string("Negro -> Imprimir");
	  		  HAL_Delay(ONESECONDS);

	  	    if (readButton_Hora()) {
	  	    	printf("Pin 13 Boton AZUL esta pulsado\r\n");
	  	    	myEstado_t = LECTURA_TIEMPO_HORA;
	  	        mylcd_clear();
	  	        break;
	  	    }
	  	    if (readButton_Fecha()) {
	  	    	printf("Pin 11 Boton Blanco esta pulsado\r\n");
	  	  	  	myEstado_t = LECTURA_TIEMPO_FECHA;
	  	  	  	mylcd_clear();
	  	  	  	break;
	  	  	}
	  	    if (readButton_Temperatura()) {
	  	    	printf("Pin 12 Boton ROJO esta pulsado\r\n");
	  	  	  	myEstado_t = LECTURA_TEMPERATURA;
	  	  	  	mylcd_clear();
	  	  	  	break;
	  	  	}
	  	    if (readButton_Printer()) {
	  	    	printf("Pin 10 Boton NEGRO esta pulsado\r\n");
	  	  	  	myEstado_t = IMPRESION_TIEMPO_TEMPERATURA;
	  	  	  	mylcd_clear();
	  	  	  	break;
	  	  	}

		  break;
	  	  case LECTURA_TIEMPO_HORA:

	  		   while(!readButton_Printer()){
	  			 get_time();
	  			 sprintf (data_buffer, "Hora: %02d:%02d:%02d", rtc_time.hour, rtc_time.minutes, rtc_time.seconds);
	  			 mylcd_put_cursor(LINE1);
	  			 mylcd_send_string(data_buffer);

	  		   }
	  		   mylcd_clear();
	  		   myEstado_t = INICIAL;

	  	  break;
	  	  case LECTURA_TIEMPO_FECHA:
	  		   get_time();
	  	  	   sprintf (data_buffer, "Fecha: %02d-%02d-20%02d", rtc_time.dayofmonth, rtc_time.month, rtc_time.year);
	  	  	   mylcd_put_cursor(LINE2);
	  	  	   mylcd_send_string(data_buffer);
	  		   while(!readButton_Printer()){

	  		   }
	  		   mylcd_clear();
	  		   myEstado_t = INICIAL;
	  	  break;
	  	  case LECTURA_TEMPERATURA:

	  		   while(!readButton_Printer()){
		  		   my_temperatura = get_temperature();

		  		   if (my_temperatura != -200) {

		  		   sprintf (data_buffer, "Temperatura: %d C", my_temperatura);
		  		   mylcd_put_cursor(LINE3);
		  		   mylcd_send_string(data_buffer);
		  		   }

	  		   }
	  		   mylcd_clear();
	  		   myEstado_t = INICIAL;
	  	  break;
	  	  case IMPRESION_TIEMPO_TEMPERATURA:
	  		   get_time();
	  		   sprintf (data_buffer, "Hora: %02d:%02d:%02d", rtc_time.hour, rtc_time.minutes, rtc_time.seconds);
	  		   Printer_PrintDateTime("La hora actual es:", data_buffer);
	  		   sprintf (data_buffer, "Fecha: %02d-%02d-20%02d", rtc_time.dayofmonth, rtc_time.month, rtc_time.year);
	  		   // Imprimir fecha y espacio final
	  		   Printer_PrintDateTime("La fecha actual es:", data_buffer);
	  		   Printer_PrintString(PRINTER_FINAL_SPACE);
	  		   HAL_Delay(ONESECONDS);

	  		   my_temperatura = get_temperature();
	  		   if (my_temperatura != -200) {
	  			sprintf (data_buffer, "Temperatura: %d C", my_temperatura);
		  		Printer_PrintTemperature("La temperatura actual es:", data_buffer);
		  		Printer_PrintString(PRINTER_FINAL_SPACE);

	  		   }
	  		   HAL_Delay(ONESECONDS);

	  		   mylcd_put_cursor(LINE4);
	  		   mylcd_send_string("Imprimiendo  ....  !");
	  		   printf("Estado de IMPRESION Temperatura, Fecha y Hora\r\n");

	  		   HAL_Delay(ONESECONDS);
	  		   myEstado_t = INICIAL;
	  		   mylcd_clear();

	  	  break;

	  	  default:
	  		   printf("Estado default, Estado Erroneo\r\n");
	  		   mylcd_clear();
	  		   mylcd_put_cursor(LINE2);
	  		   mylcd_send_string("Estado Erroneo");
	  		   mylcd_put_cursor(LINE3);
	  		   mylcd_send_string("Oprima Reset");
	  		   HAL_Delay(ONESECONDS);
	  		   HAL_Delay(ONESECONDS);

	  }







  }
  /* USER CODE END 3 */
}


bool_t readButton_Hora() {
    return !HAL_GPIO_ReadPin(PORTGPIO, BOTON_AZUL_HORA);
}

bool_t readButton_Fecha() {
    return HAL_GPIO_ReadPin(PORTGPIO, BOTON_BLANCO_FECHA);
}

bool_t readButton_Temperatura(){
	return HAL_GPIO_ReadPin(PORTGPIO, BOTON_ROJO_TEMP);
}

bool_t readButton_Printer(){
	return HAL_GPIO_ReadPin(PORTGPIO, BOTON_NEGRO_PRINTER);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PC10 PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
