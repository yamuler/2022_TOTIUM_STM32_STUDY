/*
 * 7segment.c
 *
 *  Created on: 2022. 2. 10.
 *      Author: sikyung
 */

#include "main.h"
#include "7segment.h"


void SevenSeg_GPIO_Init()
{
	  HAL_GPIO_WritePin(GPIOA, FND_SEL0_Pin|FND_SEL1_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOC, FND_SEL3_Pin|FND_SEL2_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOB, FND0_Pin|FND1_Pin|FND2_Pin|FND3_Pin
	                          |FND4_Pin|FND5_Pin|FND6_Pin|FND7_Pin, GPIO_PIN_RESET);
}

void SevenSeg_SetNumber(int digit, int num, int dp)
{
	if( digit == DIGIT_1ST)	{
		HAL_GPIO_WritePin(GPIOB, FND0_Pin|FND1_Pin|FND2_Pin|FND3_Pin|FND4_Pin|FND5_Pin|FND6_Pin|FND7_Pin, GPIO_PIN_RESET);
	}

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
	if(dp == ON) {
		HAL_GPIO_WritePin(GPIOC, FND_SEL3_Pin, GPIO_PIN_RESET);
	} else if (dp == OFF) {
		HAL_GPIO_WritePin(GPIOA, FND_SEL1_Pin|FND_SEL0_Pin, GPIO_PIN_RESET);
	}
}
