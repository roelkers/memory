#include <stdio.h>
#include <stdlib.h>
#include "static.c"

int hello = 7;
extern int foo;

int main() {
  printf("hello %i\n", hello);
  printf("foo %i\n", foo);
  printf("hey %i\n", hey);
  hey = 0;
  printf("hey %i\n", hey);
  foo = 0;
  use_static_global();
}
