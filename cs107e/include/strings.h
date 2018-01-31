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
 * Returns the original value of `dst`.
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
 * Size-bounded string concatenation. Append the null-terminated string `src`
 * to the end of `dst`. Appends at most `dstsize - strlen(dst) - 1` bytes, and
 * null-terminates the result.
 *
 * Returns the initial length of `dst` plus the length of `src`.
 */
int strlcat(char *dst, const char *src, int dstsize);

/*
 * Convert the string `str` to an `unsigned integer`. `str` should be in base
 * 10.  Does not support padding.
 *
 * Returns the result of the conversion as an `unsigned integer`
 */
unsigned int strtou(const char *str, char **endptr, int base);

#endif
