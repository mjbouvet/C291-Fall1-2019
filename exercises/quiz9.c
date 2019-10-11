#include<stdio.h>

int main(){

  int hex;
  char s[30];
  int hour = 0;
  int minute = 0;
  int second = 0;

  //for e and i the scans were getting all screwed up by  having so many so to test just comment out b, g, and h and test them individually
  printf("%12.6u", (unsigned) 2001); //1a

  printf("\n");

  printf("Input Hex Value: ");
  scanf(" %x", &hex); //1b
  printf("%d", hex);

  printf("\n");

  printf("%+d %d\n", 800, 800); //1c

  printf("%#x\n", 200); //1d

  //printf("Insert Characters: (last character entered has to be z for next scan to work) ");
  //scanf("%[^z]s", s); //1e
  //printf("%s\n", s);

  printf("%09.3f\n", 3.150); //1f

  printf("Input time: ");
  scanf("%d%*c%d%*c%d", &hour, &minute, &second); // 1g
  printf("Hour is: %d, Minute is: %d, Second is : %d", hour, minute, second);

   printf("\nInput \"Character\": ");
   scanf (" \"%[^\"]", s); //1h
  printf("%s", s);

  //printf("\nInput time again with colons: ");
  //scanf("%d:%d:%d", &hour, &minute, &second); 1i
  //printf("Hour is: %d, Minute is: %d, Second is : %d", hour, minute, second);


  /*
    Problem 2:

    a) 40000
    b) Does not Print Anything
    c) 3124.982
    d) 021, 0x11, 1.008336e+03
    e) 7000000 + 4000000
    f) 4.549E+02
    g) 465
    h) 4196270

    Problem 3:
    
    a) Files
    b) Record
    c) Key
    d) Field
    e) The standard input, the standard output, the standard error
    f) fputc
    g) fputs
    h) fwrite
    l) fseek, seekset
   */
  return 0;
}
