#include <stdio.h>
#include <unistd.h>

int main(void) {
        printf(" \"{Hello! Welcome to a Beautiful Fall @ IU!},/\\ This is Fall 2019's 1st 8 Week Course\"");
	printf("\n");
	int count = 0;
	printf("Michael Bouvette");
	while(1){
		printf(".");
		count = count + 1;
		if(count % 5 == 0){
		printf("\n");}
		if(count == 30){
			printf("Michael Bouvette");
			count = 0;}
		fflush(stdout);
		sleep(1);}
  return 0;
}
