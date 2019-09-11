#include <stdio.h>

main()
{
int peopleCount = 0;
int consecutiveCount = 0;
int enteringNumber = 0;
printf("Enter Starting Number of People: ");
scanf(" %d", &peopleCount);
while(consecutiveCount < 2){
	printf("How many people are entering or leaving (enter as negative)?: ");
	scanf(" %d", &enteringNumber);
	if(peopleCount == 149 && enteringNumber > 0){
		printf("The room is full, we are not accepting anymore people right now\n");
		consecutiveCount++;}
	else if(peopleCount + enteringNumber == 149){
		printf("Your group can enter and the room is full\n");
		peopleCount = 149;
		printf("The number of people in the room now is 149 and is full\n");
		consecutiveCount = 0;}
	else if(peopleCount + enteringNumber > 149 && enteringNumber > 0){
		printf("The whole group may not enter, but %d can enter\n", 149 - peopleCount);
		peopleCount = 149;
		printf("The total number of people in the room now is 149 and is full\n");
		consecutiveCount = 0;}
	else if(peopleCount + enteringNumber < 149 && enteringNumber > 0){
		printf("Ok your group is free to enter\n");
		peopleCount = peopleCount + enteringNumber;
		printf("The total number of people in the room is now: %d\n", peopleCount);
		consecutiveCount = 0;}
	else if(enteringNumber < 0){
		printf("Ok your group is free to leave\n");
		peopleCount = peopleCount + enteringNumber;
		printf("The total number of people in the room is now: %d\n", peopleCount);}
	}		
}
