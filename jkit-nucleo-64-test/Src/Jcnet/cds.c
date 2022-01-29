/*
 * cds.c
 *
 *  Created on: 2020. 2. 26.
 *      Author: isjeon
 */

#include "main.h"

extern ADC_HandleTypeDef hadc1;
extern void buz_fn(int ac, char *av[]);
void cds_fn(int ac, char *av[])
{
	static int adc_started = 0;
	int val;
    printf("CDS(ADC)...\t");
//	if(!adc_started)
	{
		HAL_ADC_Start(&hadc1);
		adc_started = 1;
	}
    HAL_ADC_PollForConversion(&hadc1,1000);
      val = HAL_ADC_GetValue(&hadc1);
    if(val < 1000) buz_fn(0,0);
    printf("adc val = %d\n",val);
    CLCD_printf(0,0,"ADC VAL= %04d  ",val);
}
