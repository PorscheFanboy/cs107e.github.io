int f10(void) { return 10; }
int f11(void) { return 11; }

/*
   0:	e3a00000 	mov	r0, #0
   4:	e24f100c 	sub	r1, pc, #12
   8:	e5912000 	ldr	r2, [r1]
   c:	e2822001 	add	r2, r2, #1
  10:	e5812000 	str	r2, [r1]
  14:	e12fff1e 	bx	lr
 */

void main() { 
	volatile unsigned code[6];
   	code[0] = 0xe24f100c;
   	code[0] = 0xe3a00000;
   	code[1] = 0xe24f100c;
   	code[2] = 0xe5912000;
   	code[3] = 0xe2822001;
   	code[4] = 0xe5812000;
   	code[5] = 0xe12fff1e;

	int (*fp)(void);

	fp = (int (*)(void))code;
	printf("fp() = %d, %d\n", fp(), code[0]);
	unsigned x;
	while((x = fp()) < 10) 
		printf("fp() = %d, %d\n", x, code[0]);
}
