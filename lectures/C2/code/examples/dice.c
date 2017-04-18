#include <stdlib.h>
#include <stdio.h>

/*
  int rand() { return 4;}
  #define printf(...) ;
*/

int main(int argc, char *argv[])
{
    int nrolls = 0;

    while (1) {
        int val = rand() % nrolls;
        if (val == 4) break;
        nrolls++;
    }
    printf("It took %d tries to roll a 4.\n", nrolls);
    return 0;
}
