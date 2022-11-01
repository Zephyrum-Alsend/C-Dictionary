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