/*
Step 1: Define Function, printSeating will print the 2D array, assignFirstClass will try to assign a first class seat and give options for business and economy if first class is full, assignBusinessClass and assignEconomyClass will do the same but give options for the other classes if the respective class is full, also there are functions to print the passenger manifest and boarding pass as well as two functions to go back and forth between the A->F seating and the 0->5 column numbers to access the array. 
Step 2: Populate the array with zeros to simulate empty plane
Step 3: prompt to ask what the user would like to do
Step 4: If the user wants to get a seat then ask if they would like first class, business or economy and assign respective functions based on their input
Step 5: If the user wants to print manifest, then call that function
Step 6: If the user wants to print boarding pass, then call that function
Step 7: Give option for user to break out of code and exit the menu, also check for invalid input
Step 8: For programs assignFirstClass, AssignBusinessClass, and assignEconomyClass, first check if the location in the array is 0, if it is assign the person to that location, if it is not then move to the next location and check, do this until the final position in the designated area(rows 1 and 2 are first, 3 - 5 are business, and 6-12 are economy), if that position is full then ask the user what they would like to do and either call the function for the requested area or exit the menu and go back to prompt the user if they would like to do anything else, before all this check if the array is full in the main and if it is then return that the flight is full and there is no need to calla fucntion. Also prompt for user's name after checking if a location is available, that is then stored in an alternate 2d character array which is accessed by printing methods to print the name of the person in each seat.
Step 9: For PrintPassengerMainfest loop through the array and if the location is equal to 1 then print out the information and bypass locations that have the value 0 because they are not populated, use the convertSeatNumber to convert the number location to a letter A->F
Step 10: For printBoardingPass prompt for which seat they would like they would like using convertSeatLetter to get the numerical location of the inputted A->F character, then print the information at that location in the array
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void  printSeating(int arr[12][6]);
int assignFirstClass(int arr[12][6], char charArr[72][20]);
int assignBusinessClass(int arr[12][6], char charArr[72][20]);
int assignEconomyClass(int arr[12][6], char charArr[72][20]);
int printPassengerManifest(int arr[12][6], char charArr[72][20]);
int printBoardingPasss(int arr[12][6], char charArr[72][20]);
char convertSeatNumber(int loc);
int convertSeatLetter(char loc);
int findCharArrayPos(int row, int column);
int find2DArrayColumn(int loc);
int find2DArrayRow(int loc);

int main(){
  int disp[12][6];
  int i, j,k;
  int input;
  int placed;
  int insideinput;
  char nameArray[72][20];

  for(i = 0; i<12; i++){
    for(j = 0; j < 6; j++){
      disp[i][j] = 0;
    }
  }

  while(1){
    printf("Press 1 to reserve a seat, Press 2 to Print the Seating Chart, Press 3 to print a Passenger Manifest, or Press 4 to print a boarding pass, or Press 5 to Quit the Menu: \n");
    scanf("%d", &input);
    if(input ==  1){
      printf("Please type 1 for First Class, 2 for Business Class, or 3 for Economy Class, or Anything Else to go Back to the Menu: \n");
      scanf("%d", &insideinput);
      if(disp[11][5] == 1 && disp[4][5] && disp[1][5]){
	printf("Sorry the flight is completly full");
	insideinput = 10;}
      else if(insideinput == 1){
	assignFirstClass(disp, nameArray);
      }
      else if(insideinput == 2){
	assignBusinessClass(disp, nameArray);
      }
      else if(insideinput == 3){
	assignEconomyClass(disp, nameArray);
      } 
    }
    else if(input == 2){
      printSeating(disp);}
    else if(input == 3){
      printPassengerManifest(disp, nameArray);}
    else if(input == 4){
      printBoardingPass(disp, nameArray);}
    else if(input == 5){
      break;}
    else{
      printf("Please Enter a Valid Input");}
  }
  return 0;
}

void printSeating(int arr[12][6]){
  int i, j;
  int count = 12;
  for(i = 11; i >= 0; i--){
    for(j = 0; j< 6; j++){
      printf("%d", arr[i][j]);
    }
    printf("- Row %d\n", count);
    count--;
  }
  printf("ABCDEF\n");
}

int assignFirstClass(int arr[12][6], char charArr[72][20]){
  int answer;
  int i, j, k;
  int nameLoc;
  char name[20];
  char temp;
    for(i = 0; i < 2; i++){
      for(j = 0; j < 6; j++){
	if(arr[i][j] == 0){
	  nameLoc = findCharArrayPos(i, j);
	  printf("Please Enter Your Name: ");
	  scanf("%c", &temp);
	  scanf("%[^\n]",name);
	  for(k = 0; k < 20; k++){
	    strcpy(charArr[nameLoc], name);}
	  arr[i][j] = 1;
	  return 0;}
	else if(i == 1 && j == 5){
	  printf("First Class if Full, please press 1 if it is ok to be placed in business class, and 2 if you would prefer to find a different flight: \n");
	  scanf("%d", &answer);
	  if(answer == 1){
	    assignBusinessClass(arr, charArr);}
	  else{
	    printf("Sorry for the Inconvience\n");
	    return 100;}
	}
      }
    }
}

int assignBusinessClass(int arr[12][6], char charArr[72][20]){
  int answer;
  int i, j,k;
  int nameLoc;
  char name[20];
  char temp;
  for(i = 2; i < 5; i++){
    for(j = 0; j < 6; j++){
      if(arr[i][j] == 0){
	nameLoc = findCharArrayPos(i, j);
	printf("Please Enter Your Name: ");
	scanf("%c", &temp);
	scanf("%[^\n]",name);
	for(k = 0; k < 20; k++){
	  strcpy(charArr[nameLoc], name);}
	arr[i][j] = 1;
	return 0;}
      else if(i == 4 && j == 5){
	printf("First Class if Full, please press 1 if you would like to upgrade to First class, 2 if you would\
 like to try to find a seat in economy, or 3 if you would like to find a different flight: \n");
	scanf("%d", &answer);
	if(answer == 1){
	  assignFirstClass(arr, charArr);}
	else if(answer == 2){
	  assignEconomyClass(arr, charArr);}
	else{
	  printf("Sorry for the Inconvience\n");
	  return 100;}
      }
    }
  }

}

int assignEconomyClass(int arr[12][6], char charArr[72][20]){
  int answer;
  int i, j, k;
  int nameLoc;
  char name[20];
  char temp;
  for(i = 5; i < 12; i++){
    for(j = 0; j < 6; j++){
      if(arr[i][j] == 0){
	nameLoc = findCharArrayPos(i, j);
        printf("Please Enter Your Name: ");
        scanf("%c", &temp);
        scanf("%[^\n]",name);
        for(k = 0; k < 20; k++){
          strcpy(charArr[nameLoc], name);}
        arr[i][j] = 1;
        return 0;}
      else if(i == 11 && j == 5){
        printf("Economy is Full, please press 1 if you would like to upgrade to First class, 2 if you would\
 like to upgrade to Business Class, or 3 if you would like to find a different flight: \n");
        scanf("%d", &answer);
        if(answer == 1){
          assignFirstClass(arr, charArr);}
        else if(answer == 2){
          assignBusinessClass(arr, charArr);}
        else{
          printf("Sorry for the Inconvience\n");
          return 100;}
      }
    }
  }
  return 0;
}

int printPassengerManifest(int arr[12][6], char charArr[72][20]){
  int i, j;
  char seat;
  for(i = 0; i < 12; i++){
    for(j = 0; j < 6; j++){
      if(arr[i][j] == 1){
	seat = convertSeatNumber(j);
	int loc = findCharArrayPos(i, j);
	printf("Passenger Name is: %s, Seat is %d%c\n", charArr[loc], i+1,  seat);
      }
    }
  }
  return 0;
}

int printBoardingPass(int arr[12][6], char charArr[72][20]){
  int row;
  char position;
  int posForArray;
  int loc;
  printf("Please enter the row of the seat you need a boarding pass for followed by the position: \n");
  scanf("%d%c", &row, &position);
  posForArray = convertSeatLetter(position);
  if(arr[row-1][posForArray] == 0 || row < 1 || row > 12 || posForArray < 0 || posForArray > 5){
    printf("Seat Unassigned - No Boarding pass available. Try Again!\n");}
  else if(row <= 2){
    loc = findCharArrayPos(row-1, posForArray);
    printf("%s, Seat: %d%c, Level: First Class\n", charArr[loc], row, position);}
  else if(row > 2 && row <= 5){
    loc = findCharArrayPos(row-1, posForArray);
    printf("%s, Seat: %d%c, Level: Business Class\n", charArr[loc], row, position);}
  else if(row > 5 && row <= 12){
    loc = findCharArrayPos(row-1, posForArray);
    printf("%s, Seat: %d%c, Level: Economy\n", charArr[loc], row, position);}
  return 0;
}

char convertSeatNumber(int loc){
  if(loc == 0){
    return 'A';}
  else if(loc == 1){
    return 'B';}
  else if(loc == 2){
    return 'C';}
  else if(loc == 3){
    return 'D';}
  else if(loc == 4){
    return 'E';}
  else if(loc == 5){
    return 'F';}
}

int convertSeatLetter(char loc){
  if(loc == 'A'){
    return 0;}
  else if(loc == 'B'){
    return 1;}
  else if(loc == 'C'){
    return 2;}
  else if(loc == 'D'){
    return 3;}
  else if(loc == 'E'){
    return 4;}
  else if(loc == 'F'){
    return 5;}
  else if(loc == 'a'){
    return 0;}
  else if(loc == 'b'){
    return 1;}
  else if(loc == 'c'){
    return 2;}
  else if(loc == 'd'){
    return 3;}
  else if(loc == 'e'){
    return 4;}
  else if(loc == 'f'){
    return 5;}

}


int findCharArrayPos(int row, int column){
  int finalpos;
  finalpos = row*6 + column;
  return finalpos;}

int find2DArrayColumn(int loc){
  int column;
  column  = loc % 6;
  return column;}

int find2DArrayRow(int loc){
  int row;
  row = loc / 6;
  return row;}
  
