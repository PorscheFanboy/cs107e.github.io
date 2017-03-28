int f10(void) { return 10; }
int f11(void) { return 11; }

void main() { 
	// printf("f() = %d\n", f10());

	unsigned code[3];
    	code[0] = 0xe3a0000b;
    	code[1] = 0xe12fff1e;
	int (*fp)(void);

	fp = (int (*)(void))code;
	printf("fp() = %d\n", fp());
}
