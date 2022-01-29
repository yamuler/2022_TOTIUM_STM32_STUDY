/*
 * fnd.c
 *
 *  Created on: 2020. 2. 26.
 *      Author: isjeon
 */

#include "main.h"

// FND_SEL3 share LED7 on board B
//
#define FND_SEL3_Pin LED7_Pin
#define FND_SEL3_GPIO_Port LED7_GPIO_Port

void fnd_fn(int ac, char *av[])
{
		  static int fnd_sel = 0;
          int i;
          printf("FND...\n");
          for(fnd_sel = 0 ; fnd_sel < 4 ; fnd_sel ++)
          {
        	  switch(fnd_sel)
        	  {
          	  case 0 :
                  FND_SEL0_GPIO_Port->BSRR = FND_SEL0_Pin;
                  FND_SEL1_GPIO_Port->BRR  = FND_SEL1_Pin;
                  FND_SEL2_GPIO_Port->BRR  = FND_SEL2_Pin;
                  FND_SEL3_GPIO_Port->BRR  = FND_SEL3_Pin;
                  break;
          	  case 1 :
                  FND_SEL0_GPIO_Port->BRR  = FND_SEL0_Pin;
                  FND_SEL1_GPIO_Port->BSRR  = FND_SEL1_Pin;
                  FND_SEL2_GPIO_Port->BRR  = FND_SEL2_Pin;
                  FND_SEL3_GPIO_Port->BRR  = FND_SEL3_Pin;
                  break;
          	  case 2 :
                  FND_SEL0_GPIO_Port->BRR  = FND_SEL0_Pin;
                  FND_SEL1_GPIO_Port->BRR  = FND_SEL1_Pin;
                  FND_SEL2_GPIO_Port->BSRR  = FND_SEL2_Pin;
                  FND_SEL3_GPIO_Port->BRR  = FND_SEL3_Pin;
                  break;
          	  case 3 :
                  FND_SEL0_GPIO_Port->BRR  = FND_SEL0_Pin;
                  FND_SEL1_GPIO_Port->BRR  = FND_SEL1_Pin;
                  FND_SEL2_GPIO_Port->BRR  = FND_SEL2_Pin;
                  FND_SEL3_GPIO_Port->BSRR  = FND_SEL3_Pin;
                  break;
          	  }
          	  for( i = 0 ; i < 8 ; i ++)
          	  {
                  GPIOB->ODR = (1 << i) << 0; // PB0~PB7
                  HAL_Delay(50);
          	  }
          }
          FND_SEL0_GPIO_Port->BRR  = FND_SEL0_Pin;
          FND_SEL1_GPIO_Port->BRR  = FND_SEL1_Pin;
          FND_SEL2_GPIO_Port->BRR  = FND_SEL2_Pin;
          FND_SEL3_GPIO_Port->BRR  = FND_SEL3_Pin;
  }
