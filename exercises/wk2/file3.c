/*Debugging quiz - File No: 3 */
/* This program should perform the duties of a basic calculator and print whether the result is >50 or <50 or equal to 50 */
/* the program should ask for the input until 'q' is enterd */
// Check for possible logical errors and rectify them 


#include<stdio.h>

int main(void){
  char input;
  float num1, num2, result;
  int forSwitch;
  
  while(input != 'q')
  {

printf("Welcome to the Calculator\nOperation choices:\tAddition(A)\n\t\t\tSubtraction(S)\n\t\t\tMultiplication(M)\n\t\t\tDivision(D)\nEnter choice: ");
  scanf(" %c", &input);

  if(input == 'A' | input == 'S' || input == 'M' ||  input == 'D'){
    printf("Enter both numbers in required sequence: ");
    scanf(" %f,  %f", &num1, &num2);
   
    switch(input){
      case 'A': 
        result = num1 + num2;
 	break;  
      case 'S': 
        result = num1 - num2;
	break;
      case 'M': 
        result = num1 * num2;
	break;
      case 'D': 
        result = num1 / num2;
	break; 
      default:
	printf("going through default");
	break;
    }

    if(result > 50){
      printf("Greater than 50.\n");
    }
    else if(result < 50) {
      printf("Less than 50\n");
    }
    else{
      printf("Equal to 50\n");
    }
  

  }else if(input != 'q'){
    printf("Please choose a valid operation\n");
  }

  }

  printf("Quit the menu.\n");
  return 0;
}
