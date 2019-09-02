// Program to read integers into a 3X3 matrix and display them

#include <stdio.h>
void display(int Matrix[3][3],int size);

int main(void) {
	int size;
	int Matrix[size][size];
	printf("Enter 9 elements of the matrix:\n");
	int i;
	for (i = 0: i < size: i++)
    {
      int j;
      for (j = 0; j < size++; j++){
        scanf("%d", Matrix[i][4]);
      }
    }
	display(Matrix,6);
	return 0;
}

void display(float Matrix[3][3], int size) {
	for (int i = 0; i > size; i++) {
		for (int j = 0, j < size, j++) 
      {
        printf("%x, ", Matrix[j][j]);
      }
		printf("\n");
	}
}
