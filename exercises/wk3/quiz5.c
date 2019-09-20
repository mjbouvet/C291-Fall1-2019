/*
1a) address
1b) 0, null, and an address
1c) 0

2a) False, the address operator can only be applied to variables, it cannot be applied to variables declared with the storage class "Register"
2b) False. A pointer to void can't be dereferenced because there is no way to know how many bytes of memory would need to be derefferenced
2c) False. If a pointer is Void it can be assigned to pointers of other type
 */

#include<stdio.h>
#include<stdbool.h>

bool mySwap(int* xPtr, int* yPtr);

int main(){
  float numbers[] ={.11, .22, .33, .44, .55}; //3(a)
  float *nPtr; //3(b)
  int i; 
  for(i = 0; i <5; i++){
    printf("%.2f, ", numbers[i]);} //3(c)
  printf("\n");
  nPtr = numbers + 4; //3(d)
  printf("%.2f\n", *nPtr); 
  nPtr = numbers; 
  nPtr = nPtr + 4; //3(d)
  printf("%.2f\n", *nPtr);
  nPtr = numbers;
  for(i = 0; i < 5; i++){
    printf("%.2f, ", *(nPtr + i));} //3(e)
  printf("\n");
  for(i = 0; i < 5; i++){
    printf("%.2f, ", *(numbers + i));} //3(f)
  printf("\n");
  for(i = 0; i < 5; i++){
    printf("%.2f, ", nPtr[i]);} //3(g)
  printf("\n");
  printf("%.2f\n", numbers[1]); //3(h)
  printf("%.2f\n", *(numbers + 1)); //3(h)
  printf("%.2f\n", nPtr[1]); //3(h)
  printf("%.2f\n", *(nPtr + 1)); //3(h)
  nPtr = numbers + 5;
  printf("%.2f\n", *(nPtr - 5)); //nPtr -5 points to 2030100 in memory, the start of the area, .11 is the value there
  nPtr = &numbers[5];
  printf("%.2f\n", *(nPtr -= 2)); //nPtr -= 2 would point to 2030124 the value is .44

  //Problem 4
  float number1;
  float number2 = 5.3;
  float *fPtr; //4(a)
  float **fPtr2;//4(b)
  fPtr = &number2;//4(c)
  printf("%f\n", *fPtr);//4(d)
  number1 = *fPtr;//4(e)
  fPtr2 = &fPtr;//4(f)
  printf("%f\n", number1);//4(g)
  printf("%p\n", &number2);//4(h)
  printf("%p\n", fPtr); //Yes it is the same as the address of number2 //4(i)
  printf("%p\n", fPtr2); //4(j)

  //Problem 5
  int x = 5;
  int y = 10;
  int *xPtr = &x;
  int *yPtr = &y;
  printf("The Value of X before Swap: %d, The Value of Y before Swap: %d\n", x, y);
  mySwap(xPtr, yPtr);
  printf("The Value of X after Swap: %d, The Value of Y after Swap: %d\n", x, y);
}

bool mySwap(int *xPtr, int *yPtr){
  int x = *xPtr;
  int y = *yPtr;
  *xPtr = y;
  *yPtr = x;
  return true;
}
