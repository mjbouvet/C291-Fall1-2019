#include <stdio.h>

int main(){
  FILE *ofPtr;
  FILE *tfPtr;
  FILE* nfPtr;
  
  int accountNum;
  char name[30];
  float currentBalance;
  float dollarAmount;

  int transactionAccount;
  int oldAccount;

  int n = 0;
  int j = 0;
  int count = 0;

  ofPtr = fopen("oldmast.dat", "r"); //open the files, old and trans are read, new mast is  write
  tfPtr = fopen("trans.dat", "r" );
  nfPtr = fopen("newmast.dat", "w" );

  while(n < 4){
    fscanf(tfPtr,"%d%f\n", &accountNum, &dollarAmount); //Outer loop iterates through transaction
    transactionAccount = accountNum;
    while(j < 4){
      fscanf(ofPtr,"%d%s%f\n", &accountNum, name, &currentBalance); //Inner loop iterates through oldmast to see if the account num is the same
      if(transactionAccount == accountNum){ //if the account help from the transaction loop matches one of the account numbers in the oldmast then the balance is added and printed to new mast
	currentBalance = dollarAmount + currentBalance;
	fprintf(nfPtr, "%d %s %.2f\n", accountNum, name, currentBalance);
	count = 1;}
      else if(j == 3&&count == 0){
	printf("Unmatched transaction reacord for account number: %d\n", transactionAccount); //if all of oldmast is gone thorugh then say there is no match for the trans record
      }
      j++;
    }
    n++;
    count = 0;
    j = 0;
    rewind(ofPtr); //reset the oldmaster to be compared for next value from transaction
    }

  n = 0;
  j = 0;
  count = 0;
  rewind(ofPtr); //reset variables to loop through in opposite direction
  rewind(tfPtr);

  while(n < 4){
    fscanf(ofPtr,"%d%s%f\n", &accountNum, name, &currentBalance); //this loop does the same as the one above but the outer loop goes  through old mast and the inner loop goes through transcation
    oldAccount = accountNum;
    while(j < 4){
      fscanf(tfPtr,"%d%f\n", &accountNum, &dollarAmount);
      if(oldAccount == accountNum){ //if there is a  match then skip the value in oldmast
	count = 1;}
      else if(j == 3&&count == 0){
	fprintf(nfPtr, "%d %s %.2f\n", oldAccount, name, currentBalance); //if the end of transaction is reached and there is no match then  add the oldmast account to newmast
      }
      j++;
    }

    n++;
    rewind(tfPtr); //reset transaction to be iterated through again
    j = 0;
    count = 0;
  }
    
  return 0;
}
