#include "gpio.h"
#include "keyboard.h"
#include "gl.h"

const int MAXLINE = 80;

void main(void) 
{
  gpio_init();
  keyboard_init();

  gl_init(1280, 960, GL_DOUBLEBUFFER);

  char line[MAXLINE+1];
  unsigned int index = 0;
  line[index] = '\0';
  gl_draw_string(0, 0, "Waiting...", GL_WHITE);
  gl_swap_buffer();

  while (1) {
    int ch = keyboard_read_next();
    if (index < MAXLINE) {
      line[index++] = ch;
      line[index] = 0;
    }
    gl_clear(GL_BLACK);
    gl_draw_string(20, 20, line, GL_WHITE);
    gl_swap_buffer();
  }
}
