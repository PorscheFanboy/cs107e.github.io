#ifndef PRINTF_H
#define PRINTF_H

#include <stdarg.h>

int vsnprintf(char *out, int n, const char *format, va_list args);
int vsprintf(char *out, const char *format, va_list args);
int snprintf(char* s, int n, const char* format, ...);
int sprintf(char* s, const char *format, ...);
int printf(const char *format, ...);

#endif
