#ifndef UART_H
#define UART_H

/*
 * Hardware abstractions for a serial port (UART).
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 * Date: Jan 24, 2016
 */

void uart_init(void);
int uart_getchar(void);
void uart_putchar(unsigned c);
void uart_flush(void);

#endif
