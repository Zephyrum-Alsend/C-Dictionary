#include "Parser.h"

/*
countWords()
Counts the words in a provided string.

unsigned int countWords(const char* string);
string    --> String to count the words of.

This function counts the words in a string, delimited by " ". Strsep()
is used to determine the word count, string being copied into a char array
to prevent changes to the argument. Returns an unsigned integer containing
the number of words in the passed string.

Returns an unsigned integer.

Lucas Crockett
2022.11.02
*/
unsigned int countWords(const char* string) {
  unsigned int wordCount = 0;

  // This ensures string isn't modified
  char sentence[strlen(string)+1];
  strcpy(sentence, string);
  char* sent = sentence;

  // Get the word count so we can allocate space
  char* word;
  while( (word = strsep(&sent, " ")) != NULL) {
    wordCount++;
  }
  
  return wordCount;
}