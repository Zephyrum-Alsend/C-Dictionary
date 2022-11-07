#include "../header/UserIO.h"

const int INTERNAL_BUFFER = LINE_MAX;

/*
scanLine()
Prompts the user for a line of text.

const char* scanLine(const char* prompt, int buffer);
prompt    --> string to display to the user before reading input.
buffer    --> size of string to read. Includes null terminator.

This function prompts the user to enter a line of text, stopping after
they hit enter. The text entered up to either the buffer limit -1 or \n
will be copied into input and returned; if the buffer limit was reached,
stdin is flushed. If fgets() returns NULL, this function returns NULL.

Returns a const char* of size buffer (aka string).

Lucas Crockett
2022.11.01
*/
const char* scanLine(const char* prompt, int buffer) {
  // Set buffer to the lesser of the two
  buffer = (buffer > INTERNAL_BUFFER) ? INTERNAL_BUFFER : buffer;

  // Print prompt
  printf("%s", prompt);
  
  // Read user input
  char inputBuffer[INTERNAL_BUFFER];
  if( fgets(inputBuffer, buffer, stdin) != NULL ) {
    int lastChar = strlen(inputBuffer) - 1;
    char input[lastChar+1];
    
    // If the user entered more than the buffer allowed, stdin needs cleaning
    if ( strlen(inputBuffer) >= (buffer-1) &&
         inputBuffer[buffer-2] != '\n' ) {
      flushStdin();
    }
    
    // Check if the last character is \n, toss it if so
    if(inputBuffer[lastChar] == '\n') {
      inputBuffer[lastChar] = '\0';
    }
    
    strcpy(input, inputBuffer);
    return input;
  }
  // If fgets() returns NULL, set input to NULL
  return NULL;
}

/*
scanInt()
Prompts the user for an integer.

void scanInt(const char* prompt);
prompt    --> string to display to the user before reading input.

This function prompts the user to enter an integer, stopping after
they hit enter. Uses scanf() to parse the integer. If parsing fails,
the return value is set to PARSE_FAIL. Stdin is flushed, as we do 
not read the whole line. The parsed integer is returned.

Returns an integer. Returns PARSE_FAIL if scanf() failed to parse.

Lucas Crockett
2022.11.01
*/
int scanInt(const char* prompt) {
  int input = PARSE_FAIL;
  
  printf("%s", prompt);

  // If fails to parse an integer, set input to PARSE_FAIL
  char inputBuffer[INTERNAL_BUFFER];
  if( fgets(inputBuffer, INTERNAL_BUFFER, stdin) != NULL ) {
    // input is left as PARSE_FAIL if no integer is parsed
    sscanf(inputBuffer, "%i", &input);

    // If the user entered more than the buffer allowed, stdin needs cleaning
    if ( strlen(inputBuffer) >= (INTERNAL_BUFFER-1) &&
         inputBuffer[INTERNAL_BUFFER-2] != '\n' ) {
      flushStdin();
    }
  }
  return input;
}

/*
flushStdin()
Clears stdin.

void flushStdin();

This function uses getchar() to read and toss the remaining text in stdin.

Returns nothing.

Lucas Crockett
2022.11.01
*/
void flushStdin() {
  printf("Buffer reached, input may be partially ignored.\n");
  // Read and throw out everything in stdin
  int ch;
  while( ((ch = getchar()) != '\n') && (ch != EOF) );
}