#include <stdio.h>

int i =  1;
int j =  2;
int *p =  &i;

int main()
{
    printf("i = %d\n", i);
    printf("p = &i\n");
    printf("p is %p\n", p);
    printf("*p is %d\n", *p);
    printf("*(p+0) is %d\n", *(p+0));
    printf("p[0] is %d\n", p[0]);
    printf("0[p] is %d\n", 0[p]);
    printf("p+1 is %p\n", p+1);
    printf("*(p+1) is %d\n", *(p+1));
    printf("p[1] is %d\n", p[1]);

    p =  &j;
    printf("j = %d\n", j);
    printf("p = &j\n");
    printf("p is %p\n", p);
    printf("*p is %d\n", *p);
}

