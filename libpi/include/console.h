/*
 * Interface to a text console printed on the screen for
 * Stanford's CS107E class.
 *
 * You will implement this interface as part of assignment 5.
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 * Date: 3/24/16
 */

#ifndef CONSOLE_H
#define CONSOLE_H

void console_init( unsigned nrows, unsigned ncols );

void console_putc( int ch );

void console_printf( const char *format, ... );

char console_get_char( const unsigned row, unsigned col );

#endif
