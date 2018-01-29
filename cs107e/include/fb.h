#ifndef FB_H
#define FB_H


/*
 * Low-level frameuffer routines for controlling a bare metal
 * Raspberry Pi's graphics. Presents a useful abstraction of hardware
 * that a graphics library can then use to provide useful drawing
 * primitives.
 *
 * In assignment 6 you are given a single-buffered implementation
 * of this module and extend it to provide double-buffering.
 *
 * Author: Philip Levis <pal@cs.stanford.edu>
 * Date: Mar 23 2016
 */

#define FB_SINGLEBUFFER 0
#define FB_DOUBLEBUFFER 1

void fb_init(unsigned width, unsigned height, unsigned depth,
             unsigned doublebuffer);

unsigned fb_get_width(void);
unsigned fb_get_height(void);
unsigned fb_get_depth(void);
unsigned fb_get_pitch(void);

unsigned char* fb_get_draw_buffer(void);
void fb_swap_buffer(void);

#endif
