// Exercise 7.28
#include <stdbool.h>
#include <stdio.h>

// define commands
#define SIZE 800 //changed to 800 so that memory array size is 800 therefore holding 800 memory locations (a) 
#define SENTINEL -99999
#define READ 10 
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

#define REMAINDER 44
#define EXPONENTIATION 45
#define NEWLINE 46
#define TAKESTRING 47

// function prototypes
void load(int *loadMemory);
void execute(int *memory, int *acPtr, size_t *icPtr, int *irPtr,
             int *opCodePtr, int *opPtr);
void dump(int *memory, int accumulator, size_t instructionCounter,
          int instructionRegister, int operationCode,
          int operand);
bool validWord(int word);

int main()
{ 
  int memory[SIZE]; // define memory array
  int ac = 0; // accumulator
  size_t ic = 0; // instruction counter
  int opCode = 0; // operation code
  int op = 0; // operand
  int ir = 0; // instruction register

  size_t i = 0;
  // clear memory
  for (i = 0; i < SIZE; ++i) {
    memory[i] = 0;
  } 
   
  load(memory); 
  execute(memory, &ac, &ic, &ir, &opCode, &op);  
  dump(memory, ac, ic, ir, opCode, op);
} 

// function loads instructions
void load(int *loadMemory)
{ 
  size_t i = 0; // indexing variable

  printf("%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n\n", 
	 "***           Welcome to Simpletron             ***",
	 "*** Please enter your program one instruction   ***",
	 "*** (or data word) at a time. I will type the ***",
	 "*** location number and a question mark (?).  ***",
	 "*** You then type the word for that location.   ***",
	 "*** Type the sentinel -99999 to stop entering   ***",
	 "*** your program.                               ***");
          
  printf("%s", "00 ? ");
  int instruction; // current instruction
  scanf("%p", &instruction); // read instruction
   
  // while sentinel is not read from user
  while (instruction != SENTINEL) { 

    // test instruction for validity
    if (!validWord(instruction)) {
      puts("Number out of range. Please enter again.\n");
    } 
    else { // load instruction
      loadMemory[i++] = instruction;
    } 

    printf("%p ? ", i);
    scanf("%p", &instruction);
  } 

} 

// carry out the commands
void execute(int *memory, int *acPtr, size_t *icPtr, int *irPtr,
             int *opCodePtr, int *opPtr)
{ 
  bool fatal = false; // fatal error flag
  int temp; // temporary holding space

  puts("\n************START SIMPLETRON EXECUTION************\n\n");

  // separate operation code and operand
  *irPtr = memory[*icPtr];
  *opCodePtr = *irPtr / 100;
  *opPtr = *irPtr % 100;
   
  // loop while command is not HALT or fatal
  while (*opCodePtr != HALT && !fatal) { 
    // determine appropriate action
    switch (*opCodePtr) { 
      // read data into location in memory
    case READ:
      puts("Enter an integer or float: ");
      scanf("%d||%f", &temp);
            
      // check for validity
      while (!validWord(temp)) { 
	puts("Number out of range. Please enter again: ");
	scanf("%d", &temp);
      } 
            
      memory[*opPtr] = temp; // write to memory
      ++(*icPtr);
      break; // exit switch

      // write data from memory to screen
    case WRITE:
      printf("Contents of %02d: %d\n", *opPtr, memory[*opPtr]);
      ++(*icPtr);
      break; // exit switch

      // load data from memory into accumulator
    case LOAD:
      *acPtr = memory[*opPtr];
      ++(*icPtr);
      break; // exit switch

      // store data from accumulator into memory
    case STORE:
      memory[*opPtr] = *acPtr;
      ++(*icPtr);
      break; // exit switch

      // add data from memory to data in accumulator
    case ADD:
      temp = *acPtr + memory[*opPtr];
            
      // check validity
      if (!validWord(temp)) { 
	puts("*** FATAL ERROR: Accumulator overflow ***\n");
	puts("*** Simpletron execution ");
	puts("abnormally terminated ***\n");
	fatal = true;
      } 
      else { 
	*acPtr = temp;
	++(*icPtr);
      } 
               
      break; // exit switch

      // subtract data in memory from data in accumulator
    case SUBTRACT:
      temp = *acPtr - memory[*opPtr];
            
      // check validity
      if (!validWord(temp)) { 
	puts("*** FATAL ERROR: Accumulator overflow ***\n");
	puts("*** Simpletron execution ");
	puts("abnormally terminated ***\n");
	fatal = true;
      } 
      else { 
	*acPtr = temp;
	++(*icPtr);
      } 
               
      break; // exit switch

      // divide data in memory into data in accumulator
    case DIVIDE:

      // check for divide by zero error
      if (memory[*opPtr] == 0) { 
	puts("*** FATAL ERROR: Attempt to divide by zero ***\n");
	puts("*** Simpletron execution ");
	puts("abnormally terminated ***\n");
	fatal = true;
      } 
      else { 
	*acPtr /= memory[*opPtr];
	++(*icPtr);
      } 
            
      break; // exit switch

      // multiply data in memory by data in accumulator
    case MULTIPLY:
      temp = *acPtr * memory[*opPtr];
            
      // check validity
      if (!validWord(temp)) { 
	puts("*** FATAL ERROR: Accumulator overflow ***\n");
	puts("*** Simpletron execution ");
	puts("abnormally terminated ***\n");
	fatal = true;
      } 
      else { 
	*acPtr = temp;
	++(*icPtr);
      } 

      break; // exit switch

      // branch to specific location in memory
    case BRANCH:
      *icPtr = *opPtr;
      break; // exit switch

      // branch to location in memory if accumulator is negative
    case BRANCHNEG:

      // if accumulator is negative
      if (*acPtr < 0) {
	*icPtr = *opPtr;
      } 
      else {
	++(*icPtr);
      } 

      break; // exit switch

      // branch to location in memory if accumulator is zero
    case BRANCHZERO:

      // if accumulator is zero
      if (*acPtr == 0) {
	*icPtr = *opPtr;
      } 
      else {
	++(*icPtr);
      } 

      break; // exit switch

    case REMAINDER:
      temp = *acPtr *=  memory[*opPtr];

      // check validity
      if (!validWord(temp)) {
        puts("*** FATAL ERROR: Accumulator overflow ***\n");
        puts("*** Simpletron execution ");
        puts("abnormally terminated ***\n");
        fatal = true;
      }
      else {
        *acPtr = temp;
        ++(*icPtr);
      }

      break; // exit switch

    case EXPONENTIATION:
      temp = *acPtr * memory[*opPtr];

      // check validity
      if (!validWord(temp)) {
        puts("*** FATAL ERROR: Accumulator overflow ***\n");
        puts("*** Simpletron execution ");
        puts("abnormally terminated ***\n");
        fatal = true;
      }
      else {
        *acPtr = temp;
        ++(*icPtr);
      }

      break; // exit switch

    
    case NEWLINE: 
      printf("\n");
      break;

    case TAKESTRING:
      char string[10] = "";
      scanf("Enter String: %s", &string);
      memory[*opPtr] = sizeOf(string);
      break;

    default:
      puts("*** FATAL ERROR: Invalid opcode detected ***\n");
      puts("*** Simpletron execution ");
      puts("abnormally terminated ***\n");
      fatal = true;     
      break; // exit switch 
    } 
      
    // separate next operation code and operand
    *irPtr = memory[*icPtr];
    *opCodePtr = *irPtr / 100;
    *opPtr = *irPtr % 100;
  } 

  puts("\n*************END SIMPLETRON EXECUTION*************\n");
} 

// print out name and content of each register and memory
void dump(int *memory, int accumulator, size_t instructionCounter,
          int instructionRegister, int operationCode,
          int operand)
{    
  printf("\n%s\n%-23s%+05d\n%-23s%5.2u\n%-23s%+05d\n%-23s%5.2d\n%-23s%5.2d",
	 "REGISTERS:", "accumulator", accumulator, "instructioncounter",
	 instructionCounter, "instructionregister", instructionRegister,
	 "operationcode", operationCode, "operand", operand);

  puts("\n\nMEMORY:\n   ");
   
  unsigned int i = 0;
  // print column headers
  for (i = 0; i <= 9; ++i) {
    printf("%5u ", i);
  } 
      
  // print row headers and memory contents
  for (i = 0; i < SIZE; ++i) { 

    // print in increments of 10
    if (i % 10 == 0) {
      printf("\n%2u ", i);
    } 
      
    printf("%+05d ", memory[i]);
  } 
   
  puts("");
} 

// function tests validity of word
bool validWord(int word)
{ 
  return word >= -9999 && word <= 9999;
} 



/*************************************************************************
 * (C) Copyright 1992-2016 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
