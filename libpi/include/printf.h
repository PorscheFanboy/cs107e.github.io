#ifndef PRINTF_H
#define PRINTF_H

/*
 * Functions for printing forrmatted strings.
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 *         Philip Levis <pal@cs.stanford.edu>
 *
 * Date: Mar 10, 2016
 */
#include <stdarg.h>

void printf_init();

int vsnprintf(char *out, int n, const char *format, va_list args);
int snprintf(char* s, int n, const char* format, ...);
int printf(const char *format, ...);

#endif
