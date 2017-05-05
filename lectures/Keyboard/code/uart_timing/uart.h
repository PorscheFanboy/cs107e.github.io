#ifndef UART_H
#define UART_H

/*
 * Hardware abstractions for a serial port (UART).
 * Modified by Phil for keyboard lecture so we can 
 * easily change the baud rate.
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 * Date: Jan 24, 2016
 */

void uart_init(unsigned baud);
int uart_getc(void);
void uart_putc(unsigned c);
void uart_flush(void);

#endif
