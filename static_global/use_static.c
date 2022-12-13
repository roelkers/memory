#include <stdio.h>
#include <stdlib.h>
#include "static.c"

extern int foo;

int use_static_global() {
  printf("hello foo %i\n", foo);
  printf("hello hey %i\n", hey);
  return 0;

}
