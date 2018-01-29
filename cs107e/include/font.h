#ifndef FONT_H
#define FONT_H

/*
 * Functions that provide bitmaps of ASCII
 * characters. Each character is font_get_height() rows of
 * font_get_width() columns, with each pixel being font_get_depth()
 * bytes. The pixels are 32-bits (RGBA), so get_depth() is always 4,
 * with 0xFFFFFFFF being a white pixel and 0x00000000 being a black
 * pixel.
 *
 * You do not have to implement this interface: the source code for
 * its implementation is provided as part of assignment 5.
 *
 * Author: Philip Levis <pal@cs.stanford.edu>
 * Date: Mar 25 2016
 */

/* The pixel height of a character. */
int font_get_height(void);

/* The pixel width of a character. */
int font_get_width(void);

/* The depth (in bytes) of a character pixel. */
int font_get_depth(void);

/* The number of bytes needed to store a character
   image. This is equal to height * width * depth. */
int font_get_size(void);

/* Fill in the image of character `ch` into the buffer
   pointed by `buf`. Returns 0 on failure and 1 on success.
   Failure is when `buflen` does not equal the value
   returned by font_buflen(), used as a basic sanity
   check, or if the character is out of the displayable range.
   If this function returns, buf is a width*height
   image of the pixel, i.e., a char[height][width][depth]
   array. */
int font_get_char(char ch, char* buf, int buflen);


#endif
