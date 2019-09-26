//This program includes a struct called cat that is used to store information about a given cat
//The program should ask the user for information about their cat and initialize a cat structure with the given information
//The program should also print the information using a pointer to the initialized struct
//The information printed using the struct and the pointer should be the same

#include <stdio.h>
#include <string.h>

struct cat{
	char name;
	int age;
	float weight;
}

int main(void){
	char n[20];
	int a;
	float w;

	printf("What is your cat's name: ");
	scanf(" %s", n);

	printf("How old is your cat:" );
	scanf(" %d", &a);

	printf("How much does your cat weigh: ");
	scanf(" %f", %w);

	struct cat c;
	struct cat *cPtr = c;

	printf("Cat's name is %s, and should be the same as %s.\n", c.name, cPtr);
	printf("Cat's age is %d, and should be the same as %p.\n", c(age), cPtr);
	printf("Cat's weight is %f, and should be the same as %f.\n", c,weight, cPtr->weight);
}
