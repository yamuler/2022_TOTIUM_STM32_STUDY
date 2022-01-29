/*
 * temp.c
 *
 *  Created on: 2020. 3. 6.
 *      Author: isjeon
 */

#include "main.h"

extern I2C_HandleTypeDef hi2c1;
void temp_fn(int ac, char *av[])
{
    uint8_t buf[2];
    printf("Temperature...\t");
    HAL_I2C_Master_Receive(&hi2c1,0x4c<<1, buf,2,1000);
    printf("Temp=%d.%c\n",buf[0],buf[1]&0x80?'5':'0');
    CLCD_printf(0,1,"TEMP VAL=%02d.%c  ",buf[0],buf[1]&0x80?'5':'0');
}
