/*Debugging quiz - File No: 1 */
/* using a for loop, print all the characters from A-Z*/
/* Print the sum of all even numbers from 2 to 100 */
/* Correct the logical errors in the program */



#include<stdio.h>

int main (void){

  int limit = 100, sum = 0, counter;
  char  alphabet = 'A';
  printf("The limit is %d\n", limit);
  for(counter = 2; counter <= limit; counter++){
    if(counter % 2 == 0)
	sum += counter;
    if(counter < 28){
      printf("%c\n",alphabet++);}  
  }
    printf("Sum = %d\n", sum);
}

//Wasn't sure if the 100 was inclusive so to prove that I know what is going on
//If the 100 was not inclusive then the sum would be 2450 in the first if statement because
//the 100 would not be added into the total
