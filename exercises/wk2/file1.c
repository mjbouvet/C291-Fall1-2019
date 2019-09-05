/*Debugging quiz - File No: 1 */
/* using a for loop, print all the characters from A-Z*/
/* Print the sum of all even numbers from 2 to 100 */
/* Correct the logical errors in the program */



#include<stdio.h>

int main (void){

  char limit = 1000, sum = 0, counter;
  double alphabet = 'A';
  printf("The limit is %f\n", &limit);
  for(counter = 2; counter < limit; counter++){
    sum = counter;
    

      printf("%f\n",alphabet++);  
  }
    printf("Sum = %d\n" limit);
}
