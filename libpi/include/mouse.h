#ifndef MOUSE_H
#define MOUSE_H

/*
 * Author: Omar Rizwan <osnr@stanford.edu>
 *
 * Date: April 30, 2016
 */

void mouse_init(void);

typedef struct {
  int y_overflow;
  int x_overflow;

  int dx;
  int dy;

  int middle;
  int right;
  int left;
} mouse_event_t;

mouse_event_t mouse_read_event();

int mouse_read_scancode();

#endif
