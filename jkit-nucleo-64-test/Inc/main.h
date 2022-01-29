/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define AIN2_Pin GPIO_PIN_13
#define AIN2_GPIO_Port GPIOC
#define LED4_Pin GPIO_PIN_0
#define LED4_GPIO_Port GPIOC
#define LED5_Pin GPIO_PIN_1
#define LED5_GPIO_Port GPIOC
#define LED6_Pin GPIO_PIN_2
#define LED6_GPIO_Port GPIOC
#define LED7_Pin GPIO_PIN_3
#define LED7_GPIO_Port GPIOC
#define SPI1_NCS_Pin GPIO_PIN_1
#define SPI1_NCS_GPIO_Port GPIOA
#define SW2_Pin GPIO_PIN_4
#define SW2_GPIO_Port GPIOA
#define FND_SEL2_Pin GPIO_PIN_4
#define FND_SEL2_GPIO_Port GPIOC
#define LCD_D4_Pin GPIO_PIN_5
#define LCD_D4_GPIO_Port GPIOC
#define FND0_Pin GPIO_PIN_0
#define FND0_GPIO_Port GPIOB
#define FND1_Pin GPIO_PIN_1
#define FND1_GPIO_Port GPIOB
#define FND2_Pin GPIO_PIN_2
#define FND2_GPIO_Port GPIOB
#define BIN1_Pin GPIO_PIN_10
#define BIN1_GPIO_Port GPIOB
#define SPI2_NSS_Pin GPIO_PIN_12
#define SPI2_NSS_GPIO_Port GPIOB
#define LCD_D5_Pin GPIO_PIN_6
#define LCD_D5_GPIO_Port GPIOC
#define LCD_D6_Pin GPIO_PIN_7
#define LCD_D6_GPIO_Port GPIOC
#define LCD_D7_Pin GPIO_PIN_8
#define LCD_D7_GPIO_Port GPIOC
#define LCD_RS_Pin GPIO_PIN_9
#define LCD_RS_GPIO_Port GPIOC
#define PWMA_Pin GPIO_PIN_8
#define PWMA_GPIO_Port GPIOA
#define PWMB_Pin GPIO_PIN_9
#define PWMB_GPIO_Port GPIOA
#define FND_SEL0_Pin GPIO_PIN_10
#define FND_SEL0_GPIO_Port GPIOA
#define FND_SEL1_Pin GPIO_PIN_11
#define FND_SEL1_GPIO_Port GPIOA
#define LCD_E_Pin GPIO_PIN_12
#define LCD_E_GPIO_Port GPIOA
#define AIN1_Pin GPIO_PIN_13
#define AIN1_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_15
#define BUZZER_GPIO_Port GPIOA
#define BIN2_Pin GPIO_PIN_12
#define BIN2_GPIO_Port GPIOC
#define SW1_Pin GPIO_PIN_2
#define SW1_GPIO_Port GPIOD
#define FND3_Pin GPIO_PIN_3
#define FND3_GPIO_Port GPIOB
#define FND4_Pin GPIO_PIN_4
#define FND4_GPIO_Port GPIOB
#define FND5_Pin GPIO_PIN_5
#define FND5_GPIO_Port GPIOB
#define FND6_Pin GPIO_PIN_6
#define FND6_GPIO_Port GPIOB
#define FND7_Pin GPIO_PIN_7
#define FND7_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
