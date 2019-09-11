
#include <stdio.h>

main()
{

float  convertAmount = 0.00;
float convertedAmount = 0.00;
char conversionSymbol;

while(1)
{
  printf("Enter Dollar Amount to Convert (Range: 1.00 to 1000.00):\n");
  scanf(" %f", &convertAmount);
  printf("Enter Symbol For Specific Conversion:\n E for Euro \n P for Pound \n A for Australian Dollars \n R for Renmibi \n L for Turkish Lira \n Y to Japanese Yen \n S to Swiss Franc \n # to Convert to all Currencies \n Q to Quit\n");
  scanf(" %c", &conversionSymbol);

  if(convertAmount < 1.00 || convertAmount > 1000.00){
    printf("Please enter a valid dollar amount\n");}
  else if(conversionSymbol == 'E' || conversionSymbol == 'e'){
    convertedAmount = convertAmount * .9;
    printf("The U.S. Dollar Amount %.2f, is %.2f in Euros\n", convertAmount, convertedAmount);}
  else if(conversionSymbol == 'P' || conversionSymbol == 'p'){
    convertedAmount = convertAmount * .81;
    printf("The U.S. Dollar Amount %.2f, is %.2f in Pounds\n", convertAmount, convertedAmount);}
  else if(conversionSymbol == 'A' || conversionSymbol == 'a'){
    convertedAmount = convertAmount * 1.46;
    printf("The U.S. Dollar Amount %.2f, is %.2f in Australian Dollars\n", convertAmount, convertedAmount);}
  else if(conversionSymbol == 'R' || conversionSymbol == 'r'){
    convertedAmount = convertAmount * 7.12;
    printf("The U.S. Dollar Amount %.2f, is %.2f in Chinese Renminbi\n", convertAmount, convertedAmount);}
  else if(conversionSymbol == 'L' || conversionSymbol == 'l'){
    convertedAmount = convertAmount * 5.75;
    printf("The U.S. Dollar Amount %.2f, is %.2f in Turkish Lira\n", convertAmount, convertedAmount);}
  else if(conversionSymbol == 'Y' || conversionSymbol == 'y'){
    convertedAmount = convertAmount * 107.15;
    printf("The U.S. Dollar Amount %.2f, is %.2f in Japanese Yen\n", convertAmount, convertedAmount);}
  else if(conversionSymbol == 'S' || conversionSymbol == 's'){
    convertedAmount = convertAmount * .99;
    printf("The U.S. Dollar Amount %.2f, is %.2f in Swiss Francs\n", convertAmount, convertedAmount);}
  else if(conversionSymbol == '#'){
    convertedAmount = convertAmount * .9;
    printf("The U.S. Dollar Amount %.2f, is %.2f in Euros\n", convertAmount, convertedAmount);
    convertedAmount = convertAmount * .81;
    printf("The U.S. Dollar Amount %.2f, is %.2f in Pounds\n", convertAmount, convertedAmount);
    convertedAmount = convertAmount * 1.46;
    printf("The U.S. Dollar Amount %.2f, is %.2f in Australian Dollars\n", convertAmount, convertedAmount);
    convertedAmount = convertAmount * 7.12;
    printf("The U.S. Dollar Amount %.2f, is %.2f in Chinese Renminbi\n", convertAmount, convertedAmount);
    convertedAmount = convertAmount * 5.75;
    printf("The U.S. Dollar Amount %.2f, is %.2f in Turkish Lira\n", convertAmount, convertedAmount);
    convertedAmount = convertAmount * 107.15;
    printf("The U.S. Dollar Amount %.2f, is %.2f in Japanese Yen\n", convertAmount, convertedAmount);
    convertedAmount = convertAmount * .99;
    printf("The U.S. Dollar Amount %.2f, is %.2f in Swiss Francs\n", convertAmount, convertedAmount);}
  else if(conversionSymbol == 'q' || conversionSymbol == 'Q'){
    break;}
  else{
    printf("Please Enter a valid Input\n");}
}

}
