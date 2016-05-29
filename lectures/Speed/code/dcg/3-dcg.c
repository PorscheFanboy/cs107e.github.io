int f10(void) { return 10; }
int f11(void) { return 11; }

/*
   0:	e24f1008 	sub	r1, pc, #8
   4:	e5910000 	ldr	r0, [r1]
   8:	e2802001 	add	r2, r0, #1
   c:	e5812000 	str	r2, [r1]
  10:	e12fff1e 	bx	lr
 */
//unsigned inc(unsigned *u) { *u = *u + 1; return *u;}
void main() { 
	// printf("f() = %d\n", f10());

	// if you don't make it volatile?
	volatile unsigned buf[6], *code = &buf[1];
	buf[0] = 0;
   	code[0] = 0xe24f100c;
   	code[1] = 0xe5910000;
   	code[2] = 0xe2802001;
   	code[3] = 0xe5812000;
   	code[4] = 0xe12fff1e;
	int (*fp)(void);

	fp = (int (*)(void))code;
	printf("fp() = %d, %d\n", fp(), buf[0]);
	unsigned x;
	while((x = fp()) < 10) 
		printf("fp() = %d, %d\n", x, buf[0]);
}
