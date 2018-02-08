#ifndef _STRINGS_H
#define _STRINGS_H

#include <stddef.h>

/*
 * Write `n` bytes of value `c` (converted to an unsigned char) to the memory
 * area pointed to by `s`.
 *
 * Return its first argument: `s`.
 */
void *memset(void *s, int c, size_t n);

/*
 * Copy `n` bytes from the memory area `src` to the memory area `dst`. If `dst`
 * and `src` overlap, behavior is undefined.
 *
 * Returns its first argument: `dst`.
 */
void *memcpy(void *dst, const void *src, size_t n);

/*
 * Find the length of a string `s`, returned as an `int`.
 *
 * Returns the number of characters that precede the null-terminator.
 */
int strlen(const char *s);

/*
 * Lexicographically compare the null-terminated strings `s1` and `s2`.
 *
 * Returns an integer value greater than, equal to, or less than 0, according
 * as the string `s1` is greater than, equal to, or less than the string `s2`.
 * Comparison is done as unsigned characters.
 */
int strcmp(const char *s1, const char *s2);

/*
 * Convert the string `str` to an `unsigned integer`. The `base` argument
 * indicates whether `str` is expressed in decimal (base 10) or hexadecimal
 * (base 16). No other values for base are supported. This version does
 * not skip over space characters, nor allow leading minus for negative.
 * It converts all characters of string `str`, stopping early if it 
 * encounters a character that is not a valid digit in `base`. 
 * If `endptr` is not NULL, *endptr is assigned the address of the character
 * in `str` where conversion stopped. This is either the address of the
 * first invalid character in `str` or the address of the terminating null
 * in `str` if all characters are valid digits.
 *
 * Returns the result of the conversion as an `unsigned integer`, 0 is
 * returned if the first character of `str` or `base` is invalid.
 */
unsigned int strtou(const char *str, char **endptr, int base);

/*
 * Size-bounded string concatenation. Append the null-terminated string `src`
 * to the end of `dst`. Appends at most `maxsize - strlen(dst) - 1` bytes, and
 * null-terminates the result.
 *
 * Returns the initial length of `dst` plus the length of `src`.
 */
int strlcat(char *dst, const char *src, int maxsize);

#endif
