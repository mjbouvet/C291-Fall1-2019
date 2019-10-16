#include <string.h>
#include <stdio.h>

void clean_quotes(char name[]);

int main(){
  char name[20];
  
  printf("Enter john: ");
  scanf("%s", name);
  printf("The word you entered was: %s\n\n", name);

  printf("Enter 'john': ");
  scanf("%s", name);
  printf("You word you entered was: %s\n\n", name);

  clean_quotes(name);
  printf("After Quotes Removed: %s\n\n", name);
 
  printf("Enter \"john\": ");
  scanf("%s", name);
  printf("You word you entered was: %s\n\n", name);

  clean_quotes(name);
  printf("After Quotes Removed: %s\n\n", name);


  return 0;
}

void clean_quotes(char name[]){
  int i,j;
  for(i = 0, j =0; name[j] != '\0'; j++){
    char c = name[j];
    if (c != '\'' && c != '"'){
      name[i] = c;
      i++;
    }
  }
  name[i] = '\0';
}
