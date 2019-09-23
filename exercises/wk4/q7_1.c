//This program should read a string from the user and print it using a character pointer
//The program is setup to use pointer offset notation to get each character of the string

#include <stdio.h>
#include <string.h>

int main(void){
	char s[];
	scanf(" %c", s);

	char *cPtr = s[1];

	int i=0;
	while(1){
		printf("%c", cPtr+i);
		i++;
	}

	printf("\n");
}
