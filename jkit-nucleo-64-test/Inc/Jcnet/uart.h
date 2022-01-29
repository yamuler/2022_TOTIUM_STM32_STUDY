/*
 * uart.h
 *
 *  Created on: 2020. 2. 26.
 *      Author: isjeon
 */

#ifndef UART_H_
#define UART_H_

#define UART_Q_SZ 16
typedef struct _uart_tag_ {
	uint8_t data[UART_Q_SZ];
	uint8_t wr, rd;
} uart_rx_queue_t;

#endif /* UART_H_ */
