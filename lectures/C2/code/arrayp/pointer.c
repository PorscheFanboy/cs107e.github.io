#include <stdio.h>

int a[4] = {1, 2, 3, 4};
int *p = &a[0];

int main()
{
    printf("a = %p\n", a);
    printf("p = &a[0]\n");

    printf("p is %p\n", p);

    printf("a[0] is %d\n", a[0]);
    printf("p[0] is %d\n", p[0]);
    printf("*a is %d\n", *a);
    printf("*p is %d\n", *p);

    printf("a[1] is %d\n", a[1]);
    printf("p[1] is %d\n", p[1]);

    printf("p+1 is %p\n", p+1);
    printf("a+1 is %p\n", a+1);
    printf("*(p+1) is %d\n", *(p+1));
    printf("*(a+1) is %d\n", *(a+1));

    p = a;
    printf("p = a\n");

    printf("p is %p\n", p);

    printf("a[0] is %d\n", a[0]);
    printf("p[0] is %d\n", p[0]);
    printf("*a is %d\n", *a);
    printf("*p is %d\n", *p);

    //a = p;

}

