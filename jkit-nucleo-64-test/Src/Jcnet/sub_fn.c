/*
 * sub_fn.c
 *
 *  Created on: 2020. 2. 26.
 *      Author: isjeon
 */

#include "main.h"

void led_fn(int ac, char *av[])
{
    uint32_t led;
    int i;
    printf("LED...\n");
    led = 1;
    for( i = 0 ; i < 8 ; i ++, led <<= 1)
    {
            GPIOB->ODR = (GPIOB->ODR & ~(0xf << 12)) | ((led & 0xf) << 12);
            GPIOC->ODR = (GPIOC->ODR & ~(0xf << 0 )) | ((led & 0xf0) >> 4);
            HAL_Delay(300);
    }
    led = 0;
    GPIOB->ODR = (GPIOB->ODR & ~(0xf << 12)) | ((led & 0xf) << 12);
    GPIOC->ODR = (GPIOC->ODR & ~(0xf << 0 )) | ((led & 0xf0) >> 4);
}


void switch_fn(int ac, char *av[])
{
	uint32_t prev,flag = 0;
    printf("SW...\n");
	prev = HAL_GetTick();
	while(1)
	{
		 if(!(SW2_GPIO_Port->IDR & SW2_Pin))
		 {
			 printf("SW2 pushed\n");
			 while(!(SW2_GPIO_Port->IDR & SW2_Pin))
			 { if(HAL_GetTick() - prev >= 5000) return;}
			 prev = HAL_GetTick();
			 flag ++;
		 }
		 if(!(SW1_GPIO_Port->IDR & SW1_Pin))
		 {
				 printf("SW1 pushed\n");
				 while(!(SW1_GPIO_Port->IDR & SW1_Pin))
				 {
					 if(HAL_GetTick() - prev >= 5000) return;
				 }
				 prev = HAL_GetTick();
				 flag ++;
		 }
		 if(flag >= 2)
		 {
			 buz_fn(ac,av);
			 return;
		 }

	}
}

void step_motor_fn(int ac, char *av[])
{

}

void fatfs_fn(int ac, char *av[])
{
    printf("Micro SD...\n");
	fatfs_test(0);
}

extern void MX_SPI2_Init(void);

void run_all(int ac, char *av[])
{
	led_fn(ac,av);
	fnd_fn(ac,av);
	buz_fn(ac,av);
	motor_fn(ac,av);
	fatfs_test(0);
	clcd_fn(ac,av);

	// wating for next TFT LCD Test!
	while (SW2_GPIO_Port->IDR & SW2_Pin)	;
    MX_SPI2_Init();

	tft_fn(ac,av);
	uint32_t prev;

	while(1)
	{
		if(!(SW2_GPIO_Port->IDR & SW2_Pin))
		{
			temp_fn(ac,av);
			prev = HAL_GetTick();
			while(!(SW2_GPIO_Port->IDR & SW2_Pin))
			{
				if(HAL_GetTick() - prev > 3000)
				{
					goto out;
				}
			}

		}
		if(!(SW1_GPIO_Port->IDR & SW1_Pin))
		{
			cds_fn(ac,av);
			prev = HAL_GetTick();
			while(!(SW1_GPIO_Port->IDR & SW1_Pin))
			{
				if(HAL_GetTick() - prev > 3000)
				{
					goto out;
				}
			}

		}
	}
out:;
	while(!(SW2_GPIO_Port->IDR & SW2_Pin) || !(SW1_GPIO_Port->IDR & SW1_Pin));
	CLCD_printf(0,0,"                ");
	CLCD_printf(0,1," Test Loop exit ");
	HAL_Delay(1000);
}
