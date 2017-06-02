#include "printf.h"
#include "fb.h"
#include "assert.h"
#include "reboot.h"
#include "memory.h"
#include "system.h"
#include "timer.h"

#define _WIDTH 640
#define _HEIGHT 512
#define _DEPTH 4

struct pixel {
    unsigned char b, g, r, alpha;
};
typedef volatile struct pixel pixel_t;

static pixel_t *fb;

// Writes v to the R, G, and B of each pixel in framebuffer.
void write_screen(unsigned char v) {
    for (volatile unsigned i = 0; i < fb_get_width() * fb_get_height(); i++) {
        pixel_t *p = &fb[i];
        p->r = p->g = p->b = v;
        p->alpha = 0xff;
    }
}

void write_screen_precomp(unsigned char v) {
    unsigned n = fb_get_width() * fb_get_height();

    for (volatile unsigned i = 0; i < n; i++) {
        pixel_t *p = &fb[i];
        p->r = p->g = p->b = v;
        p->alpha = 0xff;
    }
}

void write_screen_no_v(unsigned char v) {
    unsigned n = fb_get_width() * fb_get_height();

    for (unsigned i = 0; i < n; i++) {
        pixel_t *p = &fb[i];
        p->r = p->g = p->b = v;
        p->alpha = 0xff;
    }
}

void write_screen_word(unsigned char v) {
    unsigned n = fb_get_width() * fb_get_height();

    struct pixel px;
    px.r = px.g = px.b = v;
    px.alpha = 0xff;

    assert(sizeof px == sizeof(unsigned));

    unsigned u = *(unsigned *)&px;
    for (unsigned i = 0; i < n; i++) {
        pixel_t *p = &fb[i];
        *(unsigned *)p = u;
    }
}

void write_screen_ll(unsigned char v) {
    unsigned n = fb_get_width() * fb_get_height();

    struct pixel px;
    px.r = px.g = px.b = v;
    px.alpha = 0xff;

    assert(sizeof px == sizeof(unsigned));

    unsigned long long u = *(unsigned *)&px;
    u = (u << 32) | u;
    for (unsigned i = 0; i < n; i+=2) {
        unsigned long long *p = (void*)&fb[i];
        *p = u;
    }
}

void write_screen_induction(unsigned char v) {
    unsigned n = fb_get_width() * fb_get_height();

    struct pixel px;
    px.r = px.g = px.b = v;
    px.alpha = 0xff;
    unsigned long long u = *(unsigned *)&px;
    unsigned long long uu = u << 32 | u;

    volatile unsigned long long *p = (void*) fb;
    for (unsigned i = 0; i < n/2; i++, p++)
        *p = uu;
}

void write_screen_unroll(unsigned char v) {
    unsigned n = fb_get_width() * fb_get_height();

    struct pixel px;
    px.r = px.g = px.b = v;
    px.alpha = 0xff;
    unsigned long long u = *(unsigned *)&px;
    unsigned long long uu = u << 32 | u;

    volatile unsigned long long *p = (void*) fb;

    n = n/2;
    assert(n%8 == 0);
    for (unsigned i = 0; i < n; i+=8, p+=8)  {
        p[0] = uu;
        p[1] = uu;
        p[2] = uu;
        p[3] = uu;
        p[4] = uu;
        p[5] = uu;
        p[6] = uu;
        p[7] = uu;
    }
}

void assign8(void *dst, unsigned u, unsigned n);

void write_screen_asm(unsigned char v) {
    struct pixel px;
    px.r = px.g = px.b = v;
    px.alpha = 0xff;
    unsigned u = *(unsigned *)&px;

    unsigned n = fb_get_width() * fb_get_height();
    assert(n % 8 == 0);
    assign8((void*)fb, u, n/8);
}

#define TIME(cmd, val, iter) do {                       \
        printf("----------\n");                         \
        printf("running: " #cmd "\n");                  \
        int i;                                          \
        for (i = 0; i < iter; i++) {                    \
            unsigned start = timer_get_time();		\
            cmd(0x00);                                  \
            cmd(val);                                   \
            unsigned total = timer_get_time() - start;	\
            printf("took %d ticks\n", total);           \
        }                                               \
    } while (0)

void main() {
    timer_init();

    fb_init(_WIDTH, _HEIGHT, _DEPTH, 0);
    fb = (struct pixel *) fb_get_draw_buffer();

    TIME(write_screen, 0xff, 2);
    TIME(write_screen_precomp, 0xff, 4);
    TIME(write_screen_no_v, 0xff, 4);
    TIME(write_screen_word, 0xff, 4);
    TIME(write_screen_ll, 0xff, 4);
    TIME(write_screen_induction, 0xff, 4);
    TIME(write_screen_unroll, 0xff, 4);
    TIME(write_screen_asm, 0xff, 4);

    system_enable_cache();
    printf("caching!  wow!	wow!\n");

    TIME(write_screen, 0xff, 4);
    TIME(write_screen_asm, 0xff, 4);

    printf("%c", 4); // Send EOT to signal done.
}
