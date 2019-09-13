// Program to read integers into a 3X3 matrix and display them

#include <stdio.h>
void display(int Matrix[3][3], int size);

int main(void) {
  int size = 3;
  int Matrix[size][size];
  printf("Enter 9 elements of the matrix:\n");
  int i = 0;
  for (i = 0; i < size; i++){
    int  j = 0;
    for (j = 0; j < size; j++){
      scanf("%d", &Matrix[i][j]);}
  }
  display(Matrix,3);
  return 0;
}



void display(int Matrix[3][3], int size) {
  int i = 0;
	for (i = 0; i < size; i++) {
	  int j = 0;
	  for (j = 0; j < size; j++) 
		  {
		    printf("%d, ", Matrix[i][j]);
		  }
		printf("\n");
	}
}
