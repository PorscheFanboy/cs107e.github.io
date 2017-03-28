/* example to generate identity() and self-modifying code */
int identity(int i) { return i; }
int plus_one(int i) { return i+1; }

// return 0, 1, 2, 3, 4, 5, 6...
void main() { 
	unsigned code[7];
	int (*fp)(int);

	code[0] =  0xe12fff1e;
	fp = (int (*)(int))code;
	/* how to generate code for identity? */

	printf("fp(10) = %d\n", fp(10));
	printf("fp(20) = %d\n", fp(20));

	int i;
	

	// code that modifies itself.
   	code[0] = 0xe3a0000d;
    	code[1] = 0xe24f100c;//       sub     r1, pc, #12
    	code[2] = 0xe5912000; 
    	code[3] = 0xe2822001 ;
    	code[4] = 0xe5812000 ;
    	code[5] = 0xe12fff1e;

	fp = (typeof(fp))code;
	for(i = 0; i < 32; i++) 
		printf("%d: inc() = %d\n", i, fp(0));
	

}
