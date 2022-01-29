/*
 * buzzer.c
 *
 *  Created on: 2020. 2. 26.
 *      Author: isjeon
 */

#include "main.h"

void buz_fn(int ac, char *av[])
{
	int i;
    printf("BUZZER...\n");
    for( i = 0 ; i < 100 ; i ++)

    {
                  BUZZER_GPIO_Port->BSRR = BUZZER_Pin;
                  HAL_Delay(2);
                  BUZZER_GPIO_Port->BSRR = BUZZER_Pin << 16;
                  HAL_Delay(2);
    }
}
