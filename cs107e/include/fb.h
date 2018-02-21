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

enum fb_mode { FB_SINGLEBUFFER = 0, FB_DOUBLEBUFFER = 1 };

/*
 * Initialize the framebuffer.
 *
 * @param width  the requested width in pixels of the framebuffer
 * @param height the requested height in pixels of the framebuffer
 * @param depth  the requested depth in bytes of each pixel
 * @param mode   whether the framebuffer should be 
 *                      single buffered (FB_SINGLEBUFFER)
 *                      or double buffered (FB_DOUBLEBUFFER)
 */
void fb_init(unsigned int width, unsigned int height, unsigned int depth,
             unsigned int mode);

/*
 * Get the current width in pixels of the framebuffer.
 *
 * @return    the width in pixels
 */
unsigned int fb_get_width(void);

/*
 * Get the current height in pixels of the framebuffer.
 *
 * @return    the height in pixels
 */
unsigned int fb_get_height(void);

/*
 * Get the current depth in bytes of a single pixel.
 *
 * @return    the depth in bytes
 */
unsigned int fb_get_depth(void);

/*
 * Get the current pitch in bytes of a single row of pixels in the framebuffer.
 * The pitch is nominally the width (pixels per row) multiplied by the depth 
 * (in bytes per pixel). However, the pitch may be greater than that if the
 * GPU elects to add padding to the end of the row.
 *
 * @return    the pitch in bytes
 */
unsigned int fb_get_pitch(void);

/*
 * Get a pointer to the start address of the portion of the framebuffer
 * currently being drawn into. This address points to an array of size
 * pitch*height bytes.  
 *
 * The address of the draw buffer can change when in double buffering mode.
 *
 * @return    the current draw buffer address
 */
unsigned char* fb_get_draw_buffer(void);

/*
 * Swap the front and back buffers. The front buffer will be displayed,
 * and the back buffer will become the current draw buffer.
 */
void fb_swap_buffer(void);

#endif
