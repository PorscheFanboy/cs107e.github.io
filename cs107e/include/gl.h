#ifndef GL_H
#define GL_H

/*
 * Functions for a simple bare metal Raspberry Pi graphics library
 * that draws pixels, text, lines, triangles, and rectangles. Builds
 * on the framebuffer library fb.[ch] for frame buffer access and
 * configuration; trying to use both simultaneously is discouraged.
 *
 * You implement this module in assignment 6 (rectangles are required,
 * lines and triangles are an extension).
 *
 * Author: Philip Levis <pal@cs.stanford.edu>
 * Date: Mar 23 2016
 */

#include "fb.h"

#define GL_SINGLEBUFFER FB_SINGLEBUFFER
#define GL_DOUBLEBUFFER FB_DOUBLEBUFFER

void gl_init(unsigned width, unsigned height, unsigned mode);
unsigned gl_get_width(void);
unsigned gl_get_height(void);

#define GL_BLACK  0xFF000000
#define GL_WHITE  0xFFFFFFFF
#define GL_RED    0xFFFF0000
#define GL_GREEN  0xFF00FF00
#define GL_BLUE   0xFF0000FF
#define GL_AMBER  0xFFFFBF00
#define GL_YELLOW 0xFFFFFF00

typedef unsigned color;
color gl_color(unsigned char r, unsigned char g, unsigned char b);

void gl_clear(color c);
void gl_swap_buffer(void);

void gl_draw_pixel(int x, int y, color c);
color gl_read_pixel(int x, int y);

#define GL_FONT_DEFAULT 0
#define GL_FONT_ALT1    1
#define GL_FONT_ALT2    2
void gl_select_font(int font);
void gl_draw_char(int x, int y, char letter, color c);
void gl_draw_string(int x, int y, char* string, color c);
unsigned gl_get_char_height(void);
unsigned gl_get_char_width(void);

void gl_draw_line(int x1, int y1, int x2, int y2, color c);
void gl_draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, color c);
void gl_draw_rect(int x1, int y1, int width, int height, color c);

#endif
