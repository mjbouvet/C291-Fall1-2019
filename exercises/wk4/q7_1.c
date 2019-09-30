//This program should read a string from the user and print it using a character pointer
//The program is setup to use pointer offset notation to get each character of the string

#include <stdio.h>
#include <string.h>

int main(void){
  char s[100];
  printf("Please Input a string: ");
	scanf(" %s", s);

	char *cPtr = s;
	char ch = s[0];

	int size = sizeof(s)/sizeof(s[0]);
	int i=0;
	while(ch != '\0'){
	  ch = *(cPtr + i);
	  printf("%c", ch);
	  i++;
	  
	}	
	printf("\n");
}
