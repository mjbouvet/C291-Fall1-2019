#include<stdio.h>

int main(){
  unsigned int values[10] = {1, 3, 5, 7, 9, 11, 13}; //a
  unsigned int* vPtr;//b
  int i = 0;
  
  for(i = 0; i < 10; i++){
    printf("%d, ", values[i]);} //c
  printf("\n");

  vPtr = values;
  printf("%p\n", vPtr); //d
  vPtr = &values[0];
  printf("%p\n", vPtr);
 
  for(i = 0; i < 10; i++){
    printf("%d, ", *(vPtr + i));} //e
  printf("\n");

  for(i = 0; i < 10; i++){
    printf("%d, ", *(values + i));} //f
  printf("\n");

  for(i = 0; i < 10; i++){
    printf("%d, ", vPtr[i]);} //g
  printf("\n");

  printf("%d\n", values[4]);  //h
  printf("%d\n", *(values + 4)); //h
  printf("%d\n", vPtr[4]); //h
  printf("%d\n", *(vPtr + 4)); //h

  printf("%p\n", vPtr + 5); //This would be 100430 in terms of the address and given that unsigned integers are 6 bytes in the problem //i
  printf("%d\n", *(vPtr + 5));

  printf("%d\n", *(vPtr + 6));
  vPtr = &values[6];
  printf("%d\n", *vPtr); //j
  printf("%p\n", vPtr);
  printf("%d\n", *(vPtr -= 3)); //Would be 100418 and the value is 7 
 return 0;
}
