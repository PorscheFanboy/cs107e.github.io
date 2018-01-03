#include "mouse.h"
#include "gl.h"

#define POINTER_SIZE 5

#define COLOR_BACKGROUND GL_WHITE
#define COLOR_POINTER GL_BLACK
#define COLOR_DRAW GL_AMBER

int cmd_paint(int argc, const char* argv[]) {
    gl_init(gl_get_width(), gl_get_height(), GL_SINGLEBUFFER);
    gl_clear(COLOR_BACKGROUND);

    int pointer_x = 0;
    int pointer_y = 0;
    color under_pointer[POINTER_SIZE][POINTER_SIZE];

    for (int x = pointer_x; x < pointer_x + POINTER_SIZE; x++) {
        for (int y = pointer_y; y < pointer_y + POINTER_SIZE; y++) {
            under_pointer[x - pointer_x][y - pointer_y] = COLOR_BACKGROUND;
        }
    }

    while (1) {
        mouse_event_t evt = mouse_read_event();

        // Restore whatever is under the pointer right now.
        for (int x = pointer_x; x < pointer_x + POINTER_SIZE; x++) {
            for (int y = pointer_y; y < pointer_y + POINTER_SIZE; y++) {
                gl_draw_pixel(x, y, under_pointer[x - pointer_x][y - pointer_y]);
            }
        }

        pointer_x += evt.dx;
        if (pointer_x <= POINTER_SIZE) {
            pointer_x = 0;
        }
        if (gl_get_width() <= pointer_x + POINTER_SIZE) {
            pointer_x = gl_get_width() - POINTER_SIZE;
        }

        pointer_y -= evt.dy;
        if (pointer_y <= POINTER_SIZE) {
            pointer_y = 0;
        }
        if (gl_get_height() <= pointer_y + POINTER_SIZE) {
            pointer_y = gl_get_height() - POINTER_SIZE;
        }

        // Draw if we're drawing or erasing.
        if (evt.left) {
            gl_draw_rect(pointer_x, pointer_y,
                         POINTER_SIZE, POINTER_SIZE,
                         COLOR_DRAW);
        } else if (evt.middle) {
            gl_draw_rect(pointer_x, pointer_y,
                         POINTER_SIZE, POINTER_SIZE,
                         COLOR_BACKGROUND);
        }

        // Save whatever is going to be under the pointer before we draw it.
        for (int x = pointer_x; x < pointer_x + POINTER_SIZE; x++) {
            for (int y = pointer_y; y < pointer_y + POINTER_SIZE; y++) {
                under_pointer[x - pointer_x][y - pointer_y] = gl_read_pixel(x, y);
            }
        }
        // Draw the pointer.
        gl_draw_rect(pointer_x, pointer_y, POINTER_SIZE, POINTER_SIZE, COLOR_POINTER);

        if (evt.dx == 0 && evt.dy == 0 && evt.right) {
            break;
        }
    }

    gl_init(gl_get_width(), gl_get_height(), GL_DOUBLEBUFFER);
    return 0;
}
