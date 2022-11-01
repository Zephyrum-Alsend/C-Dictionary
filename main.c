#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "UserIO.h"

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

  char string[4];

  string = readLine(4*sizeof(char));
  printf("Result: %s", string);
  
  return 0;
}