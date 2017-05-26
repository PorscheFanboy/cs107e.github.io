#include <stdio.h>
#include <stdlib.h>

int* foo(int n) {
  int x = n;
  return &x;
}

int main() {
  int* int_ptr = foo(2);
  foo(3);
  printf("%d\n", *int_ptr);

  void* void_ptr = malloc(8);
  free(void_ptr);
  free(void_ptr);
}
