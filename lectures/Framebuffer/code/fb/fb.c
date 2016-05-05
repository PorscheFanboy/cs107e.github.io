#include <stdio.h>
#include "bcm.h"
#include "timer.h"
#include "mailbox.h"
#include "timer.h"

typedef struct {
    unsigned int width;       // width of the display
    unsigned int height;      // height of the display
    unsigned int virtual_width;  // width of the virtual framebuffer
    unsigned int virtual_height; // height of the virtual framebuffer
    unsigned int pitch;       // number of bytes per row
    unsigned int depth;       // number of bits per pixel
    unsigned int x_offset;    // x of the upper left corner of the virtual fb
    unsigned int y_offset;    // y of the upper left corner of the virtual fb
    unsigned int framebuffer; // pointer to the start of the framebuffer
    unsigned int size;        // number of bytes in the framebuffer
} fb_t;

static volatile fb_t fb __attribute__((aligned(16)));

const int WIDTH = 640;
const int HEIGHT = 480;
const int DEPTH = 32;

int fb_init(void) {
    fb.width = fb.virtual_width = WIDTH;
    fb.height = fb.virtual_height = HEIGHT;
    fb.depth = DEPTH;
    fb.x_offset = 0;
    fb.y_offset = 0;

    fb.pitch = 0;
    fb.framebuffer = 0;
    fb.size = 0;

    mailbox_write(MAILBOX_FRAMEBUFFER, (unsigned)&fb + GPU_NOCACHE);
    int err =  mailbox_read(MAILBOX_FRAMEBUFFER);
    return err;
}

void main(void) {
    delay(2);
    int err = fb_init();
    printf("err = %x\n", err);
    printf("width = %d\n", fb.width);
    printf("height = %d\n", fb.height);
    printf("virtual width = %d\n", fb.virtual_width);
    printf("virtual height = %d\n", fb.virtual_height);
    printf("depth = %d\n", fb.depth);
    printf("size = %d\n", fb.size);
    printf("pitch = %d\n", fb.pitch);
    printf("buffer = %08x\n", fb.framebuffer);
}
