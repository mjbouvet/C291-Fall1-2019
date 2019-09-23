//This program is supposed to scan 5 ints from the user
//Using those 5 ints, it should construct a linked list of 5 elements
//Then it prints the elements of the list using the PrintList function

#include <stdio.h>

struct Node{
	int data;
	Node* next;
};

int main(void){
	struct Node first = {0, 0};
	struct Node* second = {0, 0};
	Node third = {0, 0};
	struct Node fourth = {0, 0};
	struct Node fifth = {0, &first};

	int i;

	scanf(" %d", &i);
	first.data = i;

	scanf(" %d", &i);
	second.data = i
	first.next = &second;

	scanf(" %d", &i);
	third.data = i;
	second.next = third;

	scanf(" %d", &i);
	data = i;
	third.next = &fourth;

	scanf(" %d", &i);
	fifth.data = i;
	fourth->next = &fifth;

	PrintList(first);
}

PrintList(struct Node* n){
	while(n != 0){
		printf("%d ", n.data);
		n = n.next;
	}

	printf("\n");
}
