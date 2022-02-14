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
void FND_Select(int selNum);
void SevenSeg_SetNumber(int num);
void FND_setNumber(int num) ;// 4ms 마다 불려�??�� ?��?��..
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
int fndNum=0;
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
  //SEL0,1
  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_SET);
  // LL_GPIO_WriteOutputPort(GPIOA,LL_GPIO_PIN_10|LL_GPIO_PIN_11);
  //SEL2,3
  //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_SET);
  // LL_GPIO_WriteOutputPort(GPIOC,LL_GPIO_PIN_3|LL_GPIO_PIN_4);
  //FND 0~7
  //Disp 0
//  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
  //                         |GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_SET);
  //Disp 1
  //  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
     //FND_setNumber(1234);
	 if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4) ==0) //SWITCH2
	 {
		 fndNum++;
		 if(fndNum>9999)
			 {
			 	 fndNum=9999;
			 }
	 }
	 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) ==0) //SWITHCH1
	 {
		 if(fndNum)
			 fndNum--;
	 }
     HAL_Delay(10);
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

void FND_Select(int selNum)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET); // SEL ALL OFF
     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);
     switch(selNum)
     {
         case 0 : HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); break;//SEL0 ON
         case 1 : HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);  break;//SEL1 ON
         case 2 : HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);break;//SEL2 ON
         case 3 : HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET); break;//SEL3 ON
     }//end of switch
}

void SevenSeg_SetNumber(int num)
{
   HAL_GPIO_WritePin(GPIOB, FND0_Pin|FND1_Pin|FND2_Pin|FND3_Pin|FND4_Pin|FND5_Pin|FND6_Pin|FND7_Pin, GPIO_PIN_RESET);

   switch(num)
   {
      case 0:
         HAL_GPIO_WritePin(GPIOB, FND0_Pin|FND1_Pin|FND2_Pin|FND3_Pin|FND4_Pin|FND5_Pin, GPIO_PIN_SET);
         break;
      case 1:
         HAL_GPIO_WritePin(GPIOB, FND1_Pin|FND2_Pin, GPIO_PIN_SET);
         break;
      case 2:
         HAL_GPIO_WritePin(GPIOB, FND0_Pin|FND1_Pin|FND3_Pin|FND4_Pin|FND6_Pin, GPIO_PIN_SET);
         break;
      case 3:
         HAL_GPIO_WritePin(GPIOB, FND0_Pin|FND1_Pin|FND2_Pin|FND3_Pin|FND6_Pin, GPIO_PIN_SET);
         break;
      case 4:
         HAL_GPIO_WritePin(GPIOB, FND1_Pin|FND2_Pin|FND5_Pin|FND6_Pin, GPIO_PIN_SET);
         break;
      case 5:
         HAL_GPIO_WritePin(GPIOB, FND0_Pin|FND2_Pin|FND3_Pin|FND5_Pin|FND6_Pin, GPIO_PIN_SET);
         break;
      case 6:
         HAL_GPIO_WritePin(GPIOB, FND0_Pin|FND2_Pin|FND3_Pin|FND4_Pin|FND5_Pin|FND6_Pin, GPIO_PIN_SET);
         break;
      case 7:
         HAL_GPIO_WritePin(GPIOB, FND0_Pin|FND1_Pin|FND2_Pin|FND5_Pin, GPIO_PIN_SET);
         break;
      case 8:
         HAL_GPIO_WritePin(GPIOB, FND0_Pin|FND1_Pin|FND2_Pin|FND3_Pin|FND4_Pin|FND5_Pin|FND6_Pin, GPIO_PIN_SET);
         break;
      case 9:
         HAL_GPIO_WritePin(GPIOB, FND0_Pin|FND1_Pin|FND2_Pin|FND5_Pin|FND6_Pin, GPIO_PIN_SET);
         break;
   }
}

void FND_setNumber(int num) // 4ms 마다 불려�??�� ?��?��..
{
#if 0
   static int selNum=0;
    int digit1;
    int digit10;
    int digit100;
    int digit1000;

   selNum++;
   if(selNum>3)
      selNum=0;
   //selNum &=0x3;

   FND_Select(selNum);

   digit1 = num%10;
   digit10 = (num/10)%10;
   digit100 = (num/100)%10;
   digit1000 = (num/1000)%10;

   switch(selNum)
    {
       case 0 : SevenSeg_SetNumber(digit1); break;
       case 1 : SevenSeg_SetNumber(digit10); break;
       case 2 : SevenSeg_SetNumber(digit100); break;
       case 3 : SevenSeg_SetNumber(digit1000); break;
    }//end of switch
#else
   static int selNum=0;
   int digit[4];

   selNum++;
   if(selNum>3)
      selNum=0;
   //selNum &=0x3;
   FND_Select(selNum);
   digit[0] = num%10;
   digit[1] = (num/10)%10;
   digit[2] = (num/100)%10;
   digit[3] = (num/1000)%10;
   SevenSeg_SetNumber(digit[selNum]);

#endif
}




void CheckButtons(void) // 10ms 마다 불려진다
{
   static int sw1ConfirmCnt=0;
   static int sw2ConfirmCnt=0;

   int sw1Status = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11);
   int sw2Status = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);

   if(sw2Status ==0 && ++sw2ConfirmCnt > 5  ) //SWITCH2
   {
       fndNum++;
       if(fndNum>9999)
       {
          fndNum =9999;
       }
    }else if(sw2Status==1)
    {
       sw2ConfirmCnt=0;
    }

   if(sw1Status ==0 && ++sw1ConfirmCnt > 5 ) //SWITCH1
   {
         if(fndNum)
            fndNum--;
   }else if(sw1Status ==1)
   {
      sw1ConfirmCnt=0;
   }

}



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

