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

// /*
// scanLine()
// Prompts the user for a line of text.
//
// void scanLine(char* input, const char* prompt, int buffer);
// input     --> string that will hold the return value.
// prompt    --> string to display to the user before reading input.
// buffer    --> size of string to read. Includes null terminator.
//
// This function prompts the user to enter a line of text, stopping after
// they hit enter. The text entered up to either the buffer limit -1 or \n
// will be copied into input. If fgets() returns NULL, this function changes
// input to NULL. Stdin is flushed, incase the user entered text beyond the 
// buffer limit.
//
// Returns nothing. Modifies input to hold a return value.
//
// Lucas Crockett
// 2022.11.01
// */
void scanLine(char* input, const char* prompt, int buffer) {
  const int INTERNAL_BUFFER = LINE_MAX;
  // Set buffer to the lesser of the two
  buffer = (buffer > INTERNAL_BUFFER) ? INTERNAL_BUFFER : buffer;

  // Print prompt
  printf("%s", prompt);
  
  // Read user input
  char inputBuffer[INTERNAL_BUFFER];
  if( fgets(inputBuffer, buffer, stdin) != NULL ) {
    // Check if the last character is \n, toss it if so
    int lastChar = strlen(inputBuffer) - 1;
    if(inputBuffer[lastChar] == '\n') {
      inputBuffer[lastChar] = '\0';
    }
    // If the user entered more than the buffer allowed, stdin needs cleaning
    else {
      flushStdin();
    }
    
    strcpy(input, inputBuffer);
  }
  // If fgets() returns NULL, set input to NULL
  else {
    input = NULL;
  }
}

/*
scanInt()
Prompts the user for an integer.

void scanInt(const char* prompt);
prompt    --> string to display to the user before reading input.

This function prompts the user to enter an integer, stopping after
they hit enter. Uses scanf() so incorrect inputs will generate garbage
numbers. Stdin is flushed, incase the user entered text beyond what was 
asked. The integer parsed is returned.

Returns an integer.

Lucas Crockett
2022.11.01
*/
int scanInt(const char* prompt) {
  int input;
  printf("%s", prompt);
  scanf("%d", &input);
  flushStdin();
  return input;
}

/*
flushStdin()
Clears stdin.

void flushStdin();

This function uses scanf() to read and toss the remaining text in stdin.

Returns nothing.

Lucas Crockett
2022.11.01
*/
void flushStdin() {
  // Read and throw out everything in stdin
  scanf("%*[^\n]");
}