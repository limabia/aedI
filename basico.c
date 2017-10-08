#include <stdio.h>

typedef int * pontInt;

int main(){
  pontInt *x;
  pontInt y;
  int z;
  x=&y;
  y=&z;
  z = 5;
  *y = 7;
  **x = 9;

  printf("x: %p\n",x);
  printf("*x: %p\n",*x);
  printf("**x: %i\n",**x);
  printf("&x: %p\n",&x);

  int c[3];
  c[0] = 1;
  c[1] = 2;
  c[2] = 3;
  
  printf("c %p %p %i \n", &c, c, *c );
  printf("segundo c %p %p %p \n", &c[0], c+1, &c[1] );
  return 0;
}