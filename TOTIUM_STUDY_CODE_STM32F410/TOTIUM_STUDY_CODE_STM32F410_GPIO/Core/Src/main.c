/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {



/* KYG CODE---------------------------------------------------------*/
/* KYG CODE BEGIN

KYG CODE END */



/* Copy from gpio.c ---------------------------------------------------------*/
/* Copy from gpio.c BEGIN

	  //HAL_GPIO_TogglePin(GPIOC, LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin);
	  //HAL_GPIO_TogglePin(GPIOB, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin);
      //HAL_Delay(1000);
	  //HAL_GPIO_WritePin(GPIOC, LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin, GPIO_PIN_SET);
	  //HAL_GPIO_WritePin(GPIOB, LED0_Pin|LED1_Pin|LED2_Pin|LED3_Pin, GPIO_PIN_RESET);
	  //HAL_Delay(1000);

Copy from gpio.c END */



/* GPIO SET, RESET ---------------------------------------------------------*/
/* GPIO SET, RESET BEGIN

	  HAL_GPIO_WritePin(GPIOB, LED0_Pin, GPIO_PIN_SET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_SET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PIN_SET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(GPIOB, LED3_Pin, GPIO_PIN_SET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(GPIOC, LED4_Pin, GPIO_PIN_SET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(GPIOC, LED5_Pin, GPIO_PIN_SET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(GPIOC, LED6_Pin, GPIO_PIN_SET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(GPIOC, LED7_Pin, GPIO_PIN_SET);
	  HAL_Delay(500);

	  HAL_GPIO_WritePin(GPIOC, LED7_Pin, GPIO_PIN_RESET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(GPIOC, LED6_Pin, GPIO_PIN_RESET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(GPIOC, LED5_Pin, GPIO_PIN_RESET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(GPIOC, LED4_Pin, GPIO_PIN_RESET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(GPIOB, LED3_Pin, GPIO_PIN_RESET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PIN_RESET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_RESET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(GPIOB, LED0_Pin, GPIO_PIN_RESET);
	  HAL_Delay(500);

GPIO SET, RESET END */



/* GPIO TOGGLE---------------------------------------------------------*/
/* GPIO TOGGLE BEGIN

	  HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	  HAL_Delay(500);
	  HAL_GPIO_TogglePin(GPIOB, LED1_Pin);
	  HAL_Delay(500);
	  HAL_GPIO_TogglePin(GPIOB, LED2_Pin);
	  HAL_Delay(500);
	  HAL_GPIO_TogglePin(GPIOB, LED3_Pin);
	  HAL_Delay(500);
	  HAL_GPIO_TogglePin(GPIOC, LED4_Pin);
	  HAL_Delay(500);
	  HAL_GPIO_TogglePin(GPIOC, LED5_Pin);
	  HAL_Delay(500);
	  HAL_GPIO_TogglePin(GPIOC, LED6_Pin);
	  HAL_Delay(500);
	  HAL_GPIO_TogglePin(GPIOC, LED7_Pin);
	  HAL_Delay(500);

	  HAL_GPIO_TogglePin(GPIOC, LED7_Pin);
	  HAL_Delay(500);
	  HAL_GPIO_TogglePin(GPIOC, LED6_Pin);
	  HAL_Delay(500);
	  HAL_GPIO_TogglePin(GPIOC, LED5_Pin);
	  HAL_Delay(500);
	  HAL_GPIO_TogglePin(GPIOC, LED4_Pin);
	  HAL_Delay(500);
	  HAL_GPIO_TogglePin(GPIOB, LED3_Pin);
	  HAL_Delay(500);
	  HAL_GPIO_TogglePin(GPIOB, LED2_Pin);
	  HAL_Delay(500);
	  HAL_GPIO_TogglePin(GPIOB, LED1_Pin);
	  HAL_Delay(500);
	  HAL_GPIO_TogglePin(GPIOB, LED0_Pin);
	  HAL_Delay(500);

GPIO TOGGLE END */



/* FOR LOOP---------------------------------------------------------*/
/* FOR LOOP BEGIN
 *
	   * for(int i=0; i< 8 ; i++)
	  {

		  switch(i){
		case 0: HAL_GPIO_TogglePin(GPIOB, LED0_Pin); break;
		case 1: HAL_GPIO_TogglePin(GPIOB, LED1_Pin); break;
		case 2: HAL_GPIO_TogglePin(GPIOB, LED2_Pin); break;
		case 3: HAL_GPIO_TogglePin(GPIOB, LED3_Pin); break;
		case 4: HAL_GPIO_TogglePin(GPIOC, LED4_Pin); break;
		case 5: HAL_GPIO_TogglePin(GPIOC, LED5_Pin); break;
		case 6: HAL_GPIO_TogglePin(GPIOC, LED6_Pin); break;
		case 7: HAL_GPIO_TogglePin(GPIOC, LED7_Pin); break;


		}
		HAL_Delay(50);
	  }

FOR LOOP END */






/* SungChun CODE ------------------------------------------------------------*/
/* SungChun CODE BEGIN

	  	  	HAL_GPIO_WritePin(GPIOB, LED0_Pin, GPIO_PIN_SET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOB, LED0_Pin, GPIO_PIN_RESET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_SET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_RESET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PIN_SET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PIN_RESET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOB, LED3_Pin, GPIO_PIN_SET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOB, LED3_Pin, GPIO_PIN_RESET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOC, LED4_Pin, GPIO_PIN_SET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOC, LED4_Pin, GPIO_PIN_RESET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOC, LED5_Pin, GPIO_PIN_SET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOC, LED5_Pin, GPIO_PIN_RESET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOC, LED6_Pin, GPIO_PIN_SET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOC, LED6_Pin, GPIO_PIN_RESET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOC, LED7_Pin, GPIO_PIN_SET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOC, LED7_Pin, GPIO_PIN_RESET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOC, LED6_Pin, GPIO_PIN_SET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOC, LED6_Pin, GPIO_PIN_RESET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOC, LED5_Pin, GPIO_PIN_SET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOC, LED5_Pin, GPIO_PIN_RESET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOC, LED4_Pin, GPIO_PIN_SET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOC, LED4_Pin, GPIO_PIN_RESET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOB, LED3_Pin, GPIO_PIN_SET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOB, LED3_Pin, GPIO_PIN_RESET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PIN_SET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PIN_RESET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_SET);
	        HAL_Delay(100);
	        HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_RESET);
	        HAL_Delay(100);

SungChun CODE END */





/* FOR, SWITCH LOOP---------------------------------------------------------*/
/* FOR, SWITCH LOOP BEGIN */
//LED0,1,2,3 => PB12, 13, 14,15 LED4,5,6,7=>PC0,1,2,3

	  for(int i=0 ; i< 16 ; i++)
	      {
	         switch(i){
	           case 0:
	           case 1:
	           case 2:
	           case 3:
	              HAL_GPIO_TogglePin(GPIOB, 1<<(i+12));
	              HAL_Delay(10);
//	              HAL_GPIO_TogglePin(GPIOB, 1<<(i+12));break;
	           case 4:
	           case 5:
	           case 6:
	           case 7:
	              HAL_GPIO_TogglePin(GPIOC, 1<<(i-4));
	              HAL_Delay(10);
//	              HAL_GPIO_TogglePin(GPIOC, 1<<(i-4));break;
	           case 8:
	           case 9:
	           case 10:
	           case 11:
	              HAL_GPIO_TogglePin(GPIOC,  1<<((8-i)+3));
	              HAL_Delay(10);
//	              HAL_GPIO_TogglePin(GPIOC,  1<<((8-i)+3));break;
	           case 12:
	           case 13:
	           case 14:
	           case 15:
	              HAL_GPIO_TogglePin(GPIOB, 1<<((15-i)+12));
	              HAL_Delay(10);
//	              HAL_GPIO_TogglePin(GPIOB, 1<<((15-i)+12));break;

	             }
	         HAL_Delay(50);

	      }
/*FOR, SWITCH LOOP END */






    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */




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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
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

