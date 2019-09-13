/* Instructions:
 *
 *
 1. Write a program to assign a grade to Student. 
	Get the number of assignmnets from user.
  Get the students score out of how many points for each assignmnet.
	Calculate percentage and return the grade associated with a range of marks.

 2. The score range and the associated grades are as follows:
     a. [97-100] = A+
     b. [90-97] = A
     c. [80-90] = B
     d. [70-80] = C
     e. less than 70 is a failing grade and should be given an F
     e. greater than 100 or less than 0 is invalid and your code should print "Invalid"

 3. Use the skeleton code provided below to create a new function "printGrade" to assign a grade based on the score ranges.

 4. Use print statements in your function to display the grade. For example, if the input marks is 77, the output should read:
        "Your grade is : C"

 5. Please adhere to standard C syntax conventions and use comments to explain your code. Failure to do so will result in a penalty.

 *
 *
 * */

#include<stdio.h>
void printGrade(int score){
  if(score >= 97 && score <= 100){
    printf("Your Grade is : A+");}
  else if(score >= 90 && score < 97){
    printf("Your Grade is : A");}
  else if(score >= 80 && score < 90){
    printf("Your Grade is : B");}
  else if(score >= 70 && score < 80){
    printf("Your Grade is : C");}
  else if(score < 70 && score >= 0){
    printf("You're failing the class, your grade is: F");}
  else if(score > 100 || score < 0){
    printf("Invalid");}
	//print the students grade based on their score in the class
}
int main(void){
	char ch;
	float score;
	int assignments;
	do {
	  score = 0;
	  assignments = 0;
		printf("How many assignmnets did you have ? ");
		scanf("%d", &assignments); //reads integer input of number of assignments
    //get the number of assignmnets from the student

		printf("Enter your score for all assignments in the form Your Score,Maximum Score : \n" );
		//reads the input of assignments in form "the score they got, the maximum possible score"
		int i = 0;
		float myScore = 0;
		float maxScore = 0;
		char temp;
		do{ 
		  scanf("%f,%f%c", &myScore, &maxScore, &temp);
		  score += myScore/maxScore;
		  i++;
		}while(temp != '\n');//this do while loop goes through the input and takes two floats one is their score and one is the max score then adds the float division of the two against each other to a total score float value until the scanner reaches the line end character which signals the end of the input
		  
    //get the student's score and the max score for each assignment

    //calculate the student's percentage in the class using the information you've gathered.
		int percent;
		percent = (score / assignments) * 100;//Calculates Student's percentage by divding the total scores by the total number of assignments and multiplying that value by 100;
		printGrade(percent);

		printf(" \n Do you want to continue? (Y/N) ");
		scanf(" %c",&ch);
	} while(ch == 'y'|| ch == 'Y');
}
