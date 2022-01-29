/*
 * clcd.c
 *
 *  Created on: 2020. 2. 16.
 *      Author: isjeon
 */


#include "main.h"

#define delay_us(x) HAL_Delay(1)

#define BIT4_LINE2_DOT58  0x28
#define DISPON_CUROFF_BLKOFF 0x0c
#define DISPOFF_CUROFF_BLKOFF 0x08
#define INC_NOSHIFT  0x06
#define DISPCLEAR  0x01

#define CUR1LINE   0x80
#define CUR2LINE   0xc0
#define CURHOME    0x02

#define LCD_D4_Pin GPIO_PIN_5
#define LCD_D4_GPIO_Port GPIOC

#define RS_LOW	  LCD_RS_GPIO_Port->BSRR = LCD_RS_Pin << 16
#define RS_HIGH	  LCD_RS_GPIO_Port->BSRR = LCD_RS_Pin << 0
#define E_LOW     LCD_E_GPIO_Port->BSRR  = LCD_E_Pin << 16
#define E_HIGH     LCD_E_GPIO_Port->BSRR  = LCD_E_Pin << 0
#define E_PULSE   E_HIGH; delay_us(1); E_LOW; delay_us(9)

//extern void delay_us();
extern void(*polling_fn)();
void CLCD_cmd(uint8_t cmd)
{
	RS_LOW;// RS = 0
//	HAL_Delay(10);

	GPIOC->ODR = (GPIOC->ODR & ~(0xF << 5)) | ((cmd & 0xf0) << 1);
	E_PULSE;
	GPIOC->ODR = (GPIOC->ODR & ~(0xF << 5)) | ((cmd & 0xf) << 5);
	E_PULSE;
//	HAL_Delay(10);
}

void CLCD_cmd_high_nibble(uint8_t cmd)
{
	RS_LOW;// RS = 0
//	HAL_Delay(10);

	GPIOC->ODR = (GPIOC->ODR & ~(0xF << 5)) | ((cmd & 0xf0) << 1);
	E_PULSE;
//	HAL_Delay(10);
}

void CLCD_data(uint8_t data)
{
	RS_HIGH; // RS = 1
	HAL_Delay(1);

	GPIOC->ODR = (GPIOC->ODR & ~(0xF << 5)) | ((data & 0xf0) << 1);
	E_PULSE;

	GPIOC->ODR = (GPIOC->ODR & ~(0xF << 5)) | ((data & 0xf) << 5);
	E_PULSE;
//	HAL_Delay(1);
}
void CLCD_puts(uint8_t *str)
{
	while(*str) {
		CLCD_data(*str++);
	}
}

#include <stdarg.h>

static char buf[80];
void CLCD_printf(uint8_t x, uint8_t y, uint8_t *str,...)
{
	va_list argp;
	va_start(argp,str);
	vsprintf(buf,str,argp);
	CLCD_cmd(0x80 + 0x40*y + x);
//	HAL_Delay(10);
	CLCD_puts(buf);
	va_end(argp);
}
void CLCD_init()
{

	CLCD_cmd_high_nibble(0x30);
	CLCD_cmd_high_nibble(0x30);
	CLCD_cmd_high_nibble(0x30);
	CLCD_cmd_high_nibble(0x20);
	CLCD_cmd(BIT4_LINE2_DOT58);
	CLCD_cmd(DISPON_CUROFF_BLKOFF);
	CLCD_cmd(INC_NOSHIFT);
	CLCD_cmd(DISPCLEAR);

	HAL_Delay(2);
	CLCD_cmd(CUR1LINE);
	HAL_Delay(2);
	CLCD_puts("Hi~ holic~");
	HAL_Delay(2);
	CLCD_cmd(CUR2LINE);
}

void clcd_fn(int ac, char *av[])
{
	int i;
	char buf[16];
    printf("CLCD...\n");
	CLCD_init();
	CLCD_printf(0,0,"Welcome to JKIT");
	for( i = 0 ; i < 4 ; i ++)
	{
		sprintf(buf,"CLCD test..%c","-/-\\"[i%4]);
		CLCD_printf(0,1,buf);
		HAL_Delay(200);
	}
	CLCD_printf(0,1,"CLCD test done");
}

