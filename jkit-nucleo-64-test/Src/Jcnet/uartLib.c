/*
 * misclib.c
 *
 *  Created on: 2020. 2. 16.
 *      Author: isjeon
 */


#include "main.h"
#include "uart.h"
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern __IO uint8_t rxBuff3[2];
extern __IO uint8_t rxBuff2[2];
__IO uint32_t rx_flag3, rx_char3;


uart_rx_queue_t stdin_uart;
int insert_uart_Q(uart_rx_queue_t *Q, uint8_t ch)
{
	if((Q->wr + 1) % UART_Q_SZ == Q->rd)
	{
		return -1; // Full
	}
	Q->data[Q->wr] = ch;
	Q->wr = (Q->wr + 1) % UART_Q_SZ;
	return 0;
}

int delete_uart_Q(uart_rx_queue_t *Q)
{
	int ch;
	if(Q->wr == Q->rd) return -1;
	ch = Q->data[Q->rd];
	Q->rd = (Q->rd + 1) % UART_Q_SZ;
	return ch;
}

int is_available(uart_rx_queue_t *Q)
{
	return (Q->wr != Q->rd);
}

void uart_rx_ready_IT(UART_HandleTypeDef *huart,uint8_t *buf)
{
	 HAL_UART_Receive_IT(huart, buf , 1);
}

#include <stdio.h>
int _write(int file, char *data, int len)
{
    int bytes_written;

    HAL_UART_Transmit(&huart2,(uint8_t *)data, len,1000);

    bytes_written = len;
    return bytes_written;
}

void my_putchar(char c)
{
        _write(1,&c,1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart3)
	{

//		printf("Usart3 rx=%c\n",rxBuff3[0]);
		rx_char3 = rxBuff3[0];
		rx_flag3 = 1;
		rxBuff3[0] ++;

		  HAL_UART_Receive_IT(&huart3, rxBuff3 , 1);
		HAL_UART_Transmit(&huart2,(uint8_t *)rxBuff3,1,1000);
	}
	if(huart == &huart2)
	{
		insert_uart_Q(&stdin_uart,rxBuff2[0]);
		HAL_UART_Receive_IT(&huart2, rxBuff2 , 1);
//		printf("Usart2 rx=%c\n",rxBuff2[0]);
	}
}
