//This program is supposed to scan 5 ints from the user
//Using those 5 ints, it should construct a linked list of 5 elements
//Then it prints the elements of the list using the PrintList function

#include <stdio.h>
#include <stdlib.h>

struct Node{
	int data;
	struct Node* next;
};

void printList(struct Node* n){
    while(n != NULL){
      printf(" %d ", n->data);
      n = n->next;}

    printf("\n");
}



int  main(){
	struct Node* first = NULL;
	struct Node* second = NULL;
	struct Node* third = NULL;
	struct Node* fourth = NULL;
	struct Node* fifth = NULL;

	first  = (struct Node*)malloc(sizeof(struct Node)); 
	second = (struct Node*)malloc(sizeof(struct Node)); 
	third = (struct Node*)malloc(sizeof(struct Node)); 
	fourth = (struct Node*)malloc(sizeof(struct Node));
	fifth = (struct Node*)malloc(sizeof(struct Node));
	int i;

	printf("Please Enter First Digit: ");
	scanf(" %d", &i);
	first->data = i;

	printf("Please Enter Second Digit: ");
	scanf(" %d", &i);
	second->data = i;
	first->next = second;

	printf("Please Enter Third Digit: ");
	scanf(" %d", &i);
	third->data = i;
	second->next = third;

	printf("Please Enter Fourth Digit: ");
	scanf(" %d", &i);
	fourth->data = i;
	third->next = fourth;

	printf("Please Enter Fifth Digit: ");
	scanf(" %d", &i);
	fifth->data = i;
	fourth->next = fifth;

	fifth->next = NULL;
	printList(first);

	return 0;
}
