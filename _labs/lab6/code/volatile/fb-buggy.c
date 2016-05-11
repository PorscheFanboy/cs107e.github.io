#include <stdio.h>
#include "bcm.h"
#include "mailbox.h"
#include "fb.h"

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
} fb_config_t;

// Why is fb volatile?
// Why is it aligned to a multiple of 16?
volatile fb_config_t fb __attribute__ ((aligned(16)));

#define MAILBOX_BASE   0x2000B880
#define MAILBOX_FULL   (1<<31)
#define MAILBOX_EMPTY  (1<<30)
#define MAILBOX_FRAMEBUFFER 1
typedef struct {
  unsigned int read;
  unsigned int padding[3]; // note padding to skip 3 words
  unsigned int peek;
  unsigned int sender;
  unsigned int status;
  unsigned int configuration;
  unsigned int write;
} mailbox_t;


void fb_init(unsigned width, unsigned height, unsigned depth) {
  fb.width = width;
  fb.virtual_width = width;
  fb.height = height;
  fb.virtual_height = height;
  fb.depth = depth * 8; // convert number of bytes to number of bits
  fb.x_offset = 0;
  fb.y_offset = 0;

  // the manual requires we to set these value to 0
  // the GPU will return new values
  fb.pitch = 0;
  fb.framebuffer = 0;
  fb.size = 0;

  volatile mailbox_t* mailbox = (volatile mailbox_t*)MAILBOX_BASE;
  while (mailbox->status & MAILBOX_FULL);
  mailbox->write = ((unsigned)&fb) + MAILBOX_FRAMEBUFFER;

  while (1) {
    while (mailbox->status & MAILBOX_EMPTY);
    unsigned ra = mailbox->read;
    if ((ra && 0xF) == MAILBOX_FRAMEBUFFER) {
      printf("width = %d\n", fb.width );
      printf("height = %d\n", fb.height );
      printf("virtual width = %d\n", fb.virtual_width );
      printf("virtual height = %d\n", fb.virtual_height );
      printf("depth = %d\n", fb.depth );
      printf("size = %d\n", fb.size );
      printf("pitch = %d\n", fb.pitch );
      printf("buffer = %08x\n", fb.framebuffer );
      return;
    }
  }
  return;
}

