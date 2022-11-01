#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "UserIO.h"

const int PARSE_FAIL = 0;

// Prints out the character tokens in a string, to show if \0 is present.
void testString(char* string, int length);

const char* getString() {
  printf("This is a prompt:\n");
  const int INTERNAL_BUFFER = 4;
  
  char inputBuffer[INTERNAL_BUFFER];
  if( fgets(inputBuffer, INTERNAL_BUFFER, stdin) != NULL ) {
    // Check if the last character is \n, toss it if so
    int lastChar = strlen(inputBuffer) - 1;
    char input[lastChar+1];
    
    if(inputBuffer[lastChar] == '\n') {
      inputBuffer[lastChar] = '\0';
    }
    // If the user entered more than the buffer allowed, stdin needs cleaning
    else {
      flushStdin();
    }
    
    strcpy(input, inputBuffer);
    return input;
  }
  // If fgets() returns NULL, set input to NULL
  else {
    return NULL;
  }
}

int main(void) {
  // printf("Hello World\n");
  // char* string = strdup("Hello Wrold");
  // char* found;

  // while( (found = strsep(&string, " ")) != NULL){
  //   printf("%s\n%s\n", string, found);
  // }

  // char userBuffer[LINE_MAX];
  // //char* userInput;

  // if( fgets(userBuffer, LINE_MAX, stdin) != NULL ) {
  //   size_t LEN = strlen(userBuffer);
  //   userBuffer[LEN-1] = '\0';
  //   char userInput[LEN];
  //   //userInput = strdup(userBuffer);
  //   //userInput = strsep(&userInput, "\n");
  //   //sscanf(userBuffer, "%[^\n]%*c", userInput);
  //   // strncpy(userInput, userBuffer, LEN);
  //   // userInput[LEN-1] = '\0';
  //   strcpy(userInput, userBuffer);
  //   printf("%sEND", userInput);
  //   for(int i = 0; i < LEN; i++){
  //     char c = userInput[i];
  //     c ? printf("'%c' ", c) : printf("'\\0' ");
  //   }
  // }

  // char string[100];
  // int inpLen = 10;
  // int number;

  // //string = readLine(4*sizeof(char));
  // scanLine(string, "Enter:\n", inpLen);
  // printf("Result: %s\n", string);
  // testString(string, inpLen);

  // number = scanInt("Enter:\n");
  // printf("%d", number);

  // char* test = getString();
  // printf("%s", test);
  printf("%i", scanInt("Enter number:\n"));
  
  return 0;
}

void testString(char* string, int length){
  for(int i = 0; i < length; i++){
    char c = string[i];
    // If \0, prints '\0', otherwise prints character as is
    c ? printf("'%c' ", c) : printf("'\\0' ");
  }
  printf("\n");
}