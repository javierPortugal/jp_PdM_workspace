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

//#define TC74_ADDRESS 0x48 << 1
//#define REG_TEMP  0x00




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
   //uint8_t reg = REG_TEMP;
   //monitore por serial y Tera term
   printf("Primer inicio de lectura de TC74...\r\n");



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	  #define ESPACIO_SIZE 2
	  #define TIMEOUT	   100
	  #define FIVESECONDS  5000
	  #define HALFSECONDS  500
	  #define ONESECONDS   1000
  	  char mensaje_hora[]= "La hora actual es: \n\r";
  	  char espacio[]= "\n\r";
  	  char espacio_final[]= "\n\n\r";

  	  get_time();
  	  sprintf (data_buffer, "Hora: %02d:%02d:%02d", rtc_time.hour, rtc_time.minutes, rtc_time.seconds);
  	  mylcd_send_command(LINE1);
  	  mylcd_send_string(data_buffer);
  	  HAL_Delay(HALFSECONDS);
  	  HAL_UART_Transmit(&huart1, (uint8_t *)( espacio) ,  ESPACIO_SIZE, TIMEOUT);
  	  HAL_UART_Transmit(&huart1, (uint8_t *)( mensaje_hora) ,  strlen(mensaje_hora), TIMEOUT);
  	  HAL_UART_Transmit(&huart1, (uint8_t *)( espacio) ,  ESPACIO_SIZE, TIMEOUT);
  	  HAL_UART_Transmit(&huart1, (uint8_t *)(data_buffer) ,  strlen(data_buffer), TIMEOUT);
  	  HAL_UART_Transmit(&huart1, (uint8_t *)( espacio) ,  ESPACIO_SIZE, TIMEOUT);

  	  char mensaje_fecha[]= "La fecha actual es: \n\r";

  	  sprintf (data_buffer, "Fecha: %02d-%02d-20%02d", rtc_time.dayofmonth, rtc_time.month, rtc_time.year);
  	  mylcd_send_command(LINE2);
  	  mylcd_send_string(data_buffer);

  	 HAL_Delay(HALFSECONDS);
  	 HAL_UART_Transmit(&huart1, (uint8_t *)( espacio) ,  ESPACIO_SIZE, TIMEOUT);
  	 HAL_UART_Transmit(&huart1, (uint8_t *)( mensaje_fecha) ,  strlen(mensaje_fecha), TIMEOUT);
  	 HAL_UART_Transmit(&huart1, (uint8_t *)( espacio) ,  ESPACIO_SIZE, TIMEOUT);
  	 HAL_UART_Transmit(&huart1, (uint8_t *)(data_buffer) ,  strlen(data_buffer), TIMEOUT);
  	 HAL_UART_Transmit(&huart1, (uint8_t *)( espacio) ,  ESPACIO_SIZE, TIMEOUT);
  	 HAL_UART_Transmit(&huart1, (uint8_t *)( espacio_final) ,  ESPACIO_SIZE, TIMEOUT);

  	 HAL_Delay(HALFSECONDS);
/*
  	char mensaje_temperatura[]= "La temperatura actual es: \n\r";

// 1. Escribir el puntero del registro que queremos leer
 	 if (HAL_I2C_Master_Transmit(&hi2c1, TC74_ADDRESS, &reg, 1, 100) != HAL_OK) {
 	     printf("Error: Sensor no encontrado\r\n");
 	   }else {
 	         // 2. Leer el byte de temperatura
 	     if (HAL_I2C_Master_Receive(&hi2c1, TC74_ADDRESS, (uint8_t*)&temperatura, 1, 100) == HAL_OK) {
 	        printf("Temperatura actual es: %d grados C\r\n", temperatura);


 	          sprintf (data_buffer, "Temperatura: %d C", temperatura);
 	       	  mylcd_send_command(LINE3);
 	       	  mylcd_send_string(data_buffer);

 	       	HAL_UART_Transmit(&huart1, (uint8_t *)( espacio) ,  ESPACIO_SIZE, TIMEOUT);
 	       	HAL_UART_Transmit(&huart1, (uint8_t *)( mensaje_temperatura) ,  strlen(mensaje_temperatura), TIMEOUT);
 	       	HAL_UART_Transmit(&huart1, (uint8_t *)( espacio) ,  ESPACIO_SIZE, TIMEOUT);
 	       	HAL_UART_Transmit(&huart1, (uint8_t *)(data_buffer) ,  strlen(data_buffer), TIMEOUT);
 	       	HAL_UART_Transmit(&huart1, (uint8_t *)( espacio) ,  ESPACIO_SIZE, TIMEOUT);
 	       	HAL_UART_Transmit(&huart1, (uint8_t *)( espacio_final) ,  ESPACIO_SIZE, TIMEOUT);

 	       	HAL_Delay(HALFSECONDS);


 	         }
 	     }

 	     HAL_Delay(1000); // Leer cada segundo

*/

  	 HAL_Delay(1000);

  	// mylcd_send_command(LINE3);
  	// mylcd_send_string("try 22");

  	// HAL_Delay(FIVESECONDS);
/*
  	 mylcd_clear ();
  	 mylcd_send_command(LINE1);
  	 mylcd_send_string("Para iniciar la ");
  	 mylcd_send_command(LINE2);
  	 mylcd_send_string("secuencia oprime el ");
  	 mylcd_send_command(LINE3);
  	 mylcd_send_string("pulsador azul ..... ");
*/

/*
  	typedef enum{
  	 INICIAL,
  	 LECTURA_TIEMPO_HORA,
	 LECTURA_TIEMPO_FECHA,
  	 LECTURA_TEMPERATURA,
	 IMPRESION_TIEMPO_TEMPERATURA,
  	 } mySequenceState_t;


  	mySequenceState_t myEstado_t;

  	myEstado_t = INICIAL;

  	*/


  while (1)
  {


/* USER CODE END WHILE */

/* USER CODE BEGIN 3 */
	  my_temperatura =get_temperature(); // obtengo temperatura desde la función de la API

	  if (my_temperatura != -1000) {

	   sprintf (data_buffer, "Temperatura: %d C", my_temperatura);
	   mylcd_send_command(LINE3);
	   mylcd_send_string(data_buffer);

	    }



	  HAL_Delay(1000);   // Espera 1 segundo entre lecturas


  }
  /* USER CODE END 3 */
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
