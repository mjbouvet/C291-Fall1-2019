#include<stdio.h>

int main(){
  short int value1;
  short int value2;
  short int *lPtr; //a
  value1 = 70000;

  lPtr = &value1; //b
  
  printf("%hi\n", *lPtr);//c

  value2 = *lPtr; //d

  printf("%hi\n", value2); //e

  printf("%p\n", &value1); //f

  printf("%p\n", lPtr); //g //yes it is the same address
  return 0;
}
