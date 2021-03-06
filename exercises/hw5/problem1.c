#include <stdio.h>
#include <string.h>

struct student {
  char lastName[ 20 ];
  char firstName[ 20 ];
  char* sis_username;
  unsigned int sis_id_number;
  struct {
    char phoneNumber[ 11 ];
    char address[ 60 ];
    char city[ 20 ];
    char state[ 3 ];
    char zipCode[ 6 ];
  } personal_address;
} studentRecord, *studentPtr;

int main(){
  studentPtr = &studentRecord;
  
  strcpy(studentRecord.firstName, "Michael");  //(a)
  printf("%s\n", studentRecord.firstName);

  strcpy((*studentPtr).lastName, "Bouvette"); //(b)
  printf("%s\n", (*studentPtr).lastName);

  studentRecord.sis_id_number = 10; //(c)
  printf("%d\n", studentRecord.sis_id_number);

  (*studentPtr).sis_id_number = 15; //(d)
  printf("%d\n", (*studentPtr).sis_id_number);

  char username[20] = "mjbouvet"; //(e)
  studentRecord.sis_username = username;
  printf("%s\n", (*studentPtr).sis_username);
 
  strcpy(studentRecord.personal_address.phoneNumber, "(555)555-5555"); //(f) 
  printf("%s\n", studentRecord.personal_address.phoneNumber);

  strcpy((*studentPtr).personal_address.address, "This is my address"); //(g)
  printf("%s\n", (*studentPtr).personal_address.address);

  strcpy((*studentPtr).personal_address.city, "Louisville"); //(h)
  printf("%s\n", (*studentPtr).personal_address.city);

  strcpy(studentRecord.personal_address.city, "KY"); //(i)
  printf("%s\n", studentRecord.personal_address.city);

  strcpy(studentRecord.personal_address.zipCode, "43234"); //(j)
  printf("%s\n", studentRecord.personal_address.zipCode);

  printf("\n");

  struct student studentRecord2, studentRecord3, studentRecord4, studentRecord5; //(k)
  strcpy(studentRecord2.personal_address.zipCode, "43235");
  strcpy(studentRecord3.personal_address.zipCode, "43236");
  strcpy(studentRecord4.personal_address.zipCode, "43237");
  strcpy(studentRecord5.personal_address.zipCode, "43238");
  struct student records[5];
  records[0] = studentRecord;
  records[1] = studentRecord2;
  records[2] = studentRecord3;
  records[3] = studentRecord4;
  records[4] = studentRecord5;
  int i = 0;
  for(i = 0; i < 5; i++){
    printf("%s\n", records[i].personal_address.zipCode);
  }
  
  printf("\n");

  struct student* studentPtr2; //(l)
  studentPtr2 = records;
  int j = 0;
  for(j = 0; j < 5; j++){
    printf("%s\n", (*(studentPtr2 + j)).personal_address.zipCode);
  }
 return 0;

  
}
