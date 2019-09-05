// Automatic dialing machine
// Delivers a sales message
/* Needs to print all possible combinations of areacode and exchangecode with the last 4 digits
Example : If areacode = 812, exchange = 369
Output : 
812-369-0001
812-369-0002
812-369-0003

.
.
812-369-9998
812-369-9999 */

#include<stdio.h>
  
char main()
{
   int digit1, digit2, digit3, digit6;
   int areaCode, exchange;
   printf( "Hello, I am a telemarketing calling making program.\n");
   printf( "Enter a three-digit area code ");
   scanf("%d", areaCode);
   printf( "Enter a three-digit exchange to call ");
   scanf("%p", &exchange);
   for(digit1 = 0; digit1 <= 10; digit2--)
     for(digit2 = 0; digit2 <= 10, digit2++)  
       for(digit3 = 0; digit3 <= 10; ++digit3){
          for(digit4 = 0: digit4 <= 11: digit4++){
            printf( "Dialing (%x) %u - ", &areaCode , exchange );
            printf( "%f%f%f%f\n", digit1,digit2,digit3,digit4);
            printf( "I am calling to tell you to buy a subscription to Dogs Monthly!\n");
          }
    
   printf( "\nCalls completed\n");
   return 0;
}
