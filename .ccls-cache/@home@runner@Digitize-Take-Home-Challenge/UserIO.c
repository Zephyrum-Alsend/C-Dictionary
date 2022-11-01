#include "UserIO.h"

/*
char* readLine(const int BUFFER, FILE* stream, bool enforceLimit, const char* repeatPrompt){
  char inputBuffer[BUFFER];
  size_t LEN = 0;

  while(true){
    if( fget(inputBuffer, BUFFER, stream) != NULL ) {
      LEN = strlen(inputBuffer);

      // Prompt for shorter input if too long
      if(enforceLimit && LEN >= BUFFER){
        printf("%s", repeatPrompt);
        continue;
      }
      
      char outputString[LEN];

      // Truncate the \n token
      inputBuffer[LEN-1] = '\0';
      strcpy(outputString, inputBuffer);
    
      return outputString;
    }
    // If fget() returns NULL, we return NULL.
    return NULL;
  }
}
*/

/*
scanLine(char*, const char*, int)
Prompts the user for a line of text.

void scanLine(char* input, const char* prompt, int buffer);
input     --> string that will hold the return value.
prompt    --> string to display to the user before reading input.
buffer    --> size of string to read. Includes null terminator.

This function prompts the user to enter a line of text, stopping after
they hit enter. The text entered up to either the buffer limit -1 
*/
void scanLine(char* input, const char* prompt, int buffer) {
  const int INTERNAL_BUFFER = LINE_MAX;
  // Set buffer to the lesser of the two
  buffer = (buffer > INTERNAL_BUFFER) ? INTERNAL_BUFFER : buffer;

  // Print prompt
  printf("%s", prompt);
  
  //scanf("%[^\n]%*c", input);

  // Read user input
  char inputBuffer[INTERNAL_BUFFER];
  if( fgets(inputBuffer, buffer, stdin) != NULL ) {
    // Check if the last character is \n, toss it if so
    int lastChar = strlen(inputBuffer) - 1;
    if(inputBuffer[lastChar] == '\n') {
      inputBuffer[lastChar] = '\0';
    }
    
    strcpy(input, inputBuffer);
  }
  // If fgets() returns NULL, set input to NULL
  else {
    input = NULL;
  }

  // If the user entered more than the buffer allowed, stdin needs cleaning
  flushStdin();
}

int scanInt(const char* prompt) {
  int input;
  printf("%s", prompt);
  scanf("%d", &input);
  flushStdin();
  return input;
}

void flushStdin() {
  // Read and throw out everything in stdin
  scanf("%*[^\n]");
}