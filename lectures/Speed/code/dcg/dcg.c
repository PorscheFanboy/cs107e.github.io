#include "printf.h"

unsigned code[6];  // if local?

void main() { 
    printf_init();

   	code[0] = 0xe3a00000;
   	code[1] = 0xe24f100c;
   	code[2] = 0xe5912000;
   	code[3] = 0xe2822001;
  	code[4] = 0xe5812000;
  	code[5] = 0xe12fff1e;

	int (*fp)();

	fp = (int (*)())code;

	unsigned x;
	while((x = fp()) < 10)
		printf("x = %d %x\n", x, code[0]);
	
}
