
/*
 * motor.c
 *
 *  Created on: 2020. 3. 6.
 *      Author: isjeon
 */

#include "main.h"

void motor_fn(int ac, char *av[])
{
     int i, j;
     static int dir = 0;
     static int phase[4][4] =
     {
       {1,0,0,1}, //
       {1,1,0,0}, //
       {0,1,1,0}, //
       {0,0,1,1}, //
     };

     printf("MOTOR...\n");

     for( j = 0 ; j < 50 ; j ++)
     {
		 for( i = 0 ; i < 4 ; i ++)
		 {
		  AIN1_GPIO_Port->BSRR = AIN1_Pin << (16 * !phase[i][0]);
		  AIN2_GPIO_Port->BSRR = AIN2_Pin << (16 * !phase[i][2]);
		  if(dir == 0)
		  {
		   BIN1_GPIO_Port->BSRR = BIN1_Pin << (16 * !phase[i][1]);
		   BIN2_GPIO_Port->BSRR = BIN2_Pin << (16 * !phase[i][3]);
		  }
		  else
		  {
		   BIN1_GPIO_Port->BSRR = BIN1_Pin << (16 * !phase[i][3]);
		   BIN2_GPIO_Port->BSRR = BIN2_Pin << (16 * !phase[i][1]);
		  }
		  HAL_Delay(10);
		 }
    }
}
