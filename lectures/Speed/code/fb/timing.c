#include "printf.h"
#include "video.h"
#include "assert.h"
#include "reboot.h"
#include "memory.h"

struct pixel {
        unsigned char r,
                      g,
                      b,
                      alpha;
};
typedef unsigned uint_t;
typedef unsigned char uchar_t;
typedef volatile struct pixel *fb_config_t;

static fb_config_t fb;
static uint_t h, w;

unsigned gettime(void) { return GET32(0x20003004); }

void write_screen(unsigned char v) {
	volatile int i;

	for(i = 0; i < fb_width() * fb_height(); i++) {
		fb_config_t p = &fb[i];
		p->r = p->g = p->b = v;
		p->alpha = 0xff;
	}
}

void write_screen_precomp(unsigned char v) {
	volatile int i;
	unsigned n = fb_width() * fb_height();

	for(i = 0; i < n; i++) {
		fb_config_t p = &fb[i];
		p->r = p->g = p->b = v;
		p->alpha = 0xff;
	}
}

void write_screen_no_v(unsigned char v) {
	int i;
	unsigned n = fb_width() * fb_height();

	for(i = 0; i < n; i++) {
		fb_config_t p = &fb[i];
		p->r = p->g = p->b = v;
		p->alpha = 0xff;
	}
}

void write_screen_word(unsigned char v) {
	int i;
	unsigned n = fb_width() * fb_height();

	struct pixel px;
	px.r = px.g = px.b = v;
	px.alpha = 0xff;

	assert(sizeof px == sizeof(unsigned));

	unsigned u = *(unsigned *)&px;
	for(i = 0; i < n; i++) {
		fb_config_t p = &fb[i];
		*(unsigned *)p = u;
	}
}

void write_screen_ll(unsigned char v) {
	int i;
	unsigned n = fb_width() * fb_height();

	struct pixel px;
	px.r = px.g = px.b = v;
	px.alpha = 0xff;

	assert(sizeof px == sizeof(unsigned));

	unsigned long long u = *(unsigned *)&px;
	u = (u << 32) | u;
	for(i = 0; i < n; i+=2) {
		unsigned long long *p = (void*)&fb[i];
		*p = u;
	}
}

void write_screen_induction(unsigned char v) {
        int i;
        unsigned n = fb_width() * fb_height();

        struct pixel px;
        px.r = px.g = px.b = v;
        px.alpha = 0xff;
        unsigned long long u = *(unsigned *)&px;
        unsigned long long uu = u << 32 | u;

        volatile unsigned long long *p = (void*) fb;
        for(i = 0; i < n/2; i++, p++)
                *p = uu;

}


void write_screen_unroll(unsigned char v) {
        int i;
        unsigned n = fb_width() * fb_height();

        struct pixel px;
        px.r = px.g = px.b = v;
        px.alpha = 0xff;
        unsigned long long u = *(unsigned *)&px;
        unsigned long long uu = u << 32 | u;

        volatile unsigned long long *p = (void*) fb;

        n = n/2;
        assert(n%8 == 0);
        for(i = 0; i < n; i+=8, p+=8)  {
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

void assign8(void *, unsigned u, unsigned n);

void write_screen_asm(unsigned char v) {
        struct pixel px;
        px.r = px.g = px.b = v;
        px.alpha = 0xff;
        unsigned u = *(unsigned *)&px;

        unsigned n = fb_width() * fb_height();
        assert(n%8 == 0);
        assign8((void*)fb, u, n/8);
}

void enable_cache(void) {
        unsigned r;
        asm volatile ("MRC p15, 0, %0, c1, c0, 0" : "=r" (r));
        r |= (1 << 12); // l1 instruction cache
        r |= (1 << 11); // branch prediction
        asm volatile ("MCR p15, 0, %0, c1, c0, 0" :: "r" (r));
}



#define TIME(cmd, val, iter) do {                            \
        printf("running: " #cmd "\n");                  \
        int i;                                          \
        for(i = 0; i < iter; i++) {                     \
                unsigned start = gettime();             \
                        cmd(val);  cmd(0x00); 		\
                unsigned total = gettime() - start;     \
                printf("took %d ticks\n", total);       \
        }                                               \
} while(0)
	
void main {
	fb_init();
	
	fb = (void*)fb_writeable_buffer();
	h = fb_height();
	w = fb_width();

	TIME(write_screen, 0xff, 2);
#if 0
	TIME(write_screen_precomp, 0xff, 4);
	TIME(write_screen_no_v, 0xff, 10);
	TIME(write_screen_word, 0xff, 10);
	TIME(write_screen_ll, 0xff, 10);
	TIME(write_screen_induction, 0xff, 4);
	TIME(write_screen_unroll, 0xff, 4);
#endif
	TIME(write_screen_asm, 0xff, 4);

	enable_cache();
	printf("caching!  wow!  wow!\n");
	TIME(write_screen_asm, 0xff, 4);

#if 0


	printf("DONE: fp = %x\n", fb);
#endif
	reboot();
}
