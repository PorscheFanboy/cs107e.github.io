#include <stdio.h>

int main() {
  char  a[4] = {1, 2, 3, 4};
  char* p = NULL;

  printf("a: 0x%08x, &a: 0x%08x\n", (unsigned)a, (unsigned)&a);
  printf("p: 0x%08x, &p: 0x%08x\n", (unsigned)p, (unsigned)&p);

  p = a;
  printf("a: 0x%08x, &a: 0x%08x\n", (unsigned)a, (unsigned)&a);
  printf("p: 0x%08x, &p: 0x%08x\n", (unsigned)p, (unsigned)&p);

  printf("&*p : 0x%08x\n", (unsigned)&*p);
}
