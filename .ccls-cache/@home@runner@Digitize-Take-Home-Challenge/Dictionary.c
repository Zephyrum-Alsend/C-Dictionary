#include "Dictionary.h"

const int WORD_SIZE = 4;

/*
dictCreate()
Given a string, creates and populates a dict struct.

dict dictCreate(const char* string);
string    --> word to turn into a dict struct.

This function extracts the first WORD_SIZE characters and total length from
string and usese these values to initialize a dict struct. dict.next is left NULL.
Returns the newly created dict struct.

Returns a dict struct.

Lucas Crockett
2022.11.02
*/
dict dictCreate(const char* string) {
  dict d;
  d.length = strlen(string);
  strncpy(d.word, string, WORD_SIZE);
  d.next = NULL;
  
  //dictPrint(&d);
  return d;
}

/*
dictInit()
Given a string, dict array, and the array's size, populates the dictionary.

void dictInit(const char* string, dict heap[], size_t size);
string    --> line of text to turn into a dictionary (linked list of dicts).
heap      --> preallocated and initialized memory for the linked list.
size      --> number of elemnets heap can store.

This function uses strsep() to parse the individual words from string and then
translates them into the fields for each dict in the linked list. Counts 
punctuation as part of the word. Properly links the list elements. String is 
copied to prevent strsep() from altering it. The function leaves heap populated 
with data from string.

Returns nothing. Modifies heap.

Lucas Crockett
2022.11.02
*/
void dictInit(const char* string, dict heap[], size_t size) {
  // This ensures string isn't modified
  char sentence[strlen(string)+1];
  strcpy(sentence, string);
  char* sent = sentence;
  char* word;

  for(int i = 0; i < size; i++) {
    word = strsep(&sent, " ");
    heap[i].length = strlen(word);
    strncpy(heap[i].word, word, WORD_SIZE);
    heap[i].word[4] = '\0';
    heap[i].next = &heap[i+1];
  }
  heap[size-1].next = NULL;
}

/*
dictSearch()
Given a string and dictionary head, returns the entry matching string.
Can search case insensitively if caseSensitive is set to false.

dict* dictSearch(const char* string, dict* head, bool caseSensitive);
string        --> word to look for in the dictionary.
head          --> starting node of the dictionary.
casSensitive  --> flag to determine if comparisons are case sensitive.

This function searches linearly through the dictionary for a match with string.
Due to the limitations of the dict struct, false matches may occur if two words
start with the same WORD_SIZE characters and have identical lengths.

Returns a dict struct.

Lucas Crockett
2022.11.02
*/
dict* dictSearch(const char* string, dict* head, bool caseSensitive) {
  dict* node = head;
  int len = strlen(string);
  char comp[WORD_SIZE+1];
  strncpy(comp, string, WORD_SIZE);
  
  while( node != NULL ) {
    if( (node->length == len) && 
      ( (caseSensitive && !strcmp(node->word, comp)) ||
        (!caseSensitive && !strcasecmp(node->word, comp)) ) ) {
      return node;
    }
    node = node->next;
  }

  return NULL;
}

void dictAppend(dict heap1[], size_t size1, dict heap2[], size_t size2, dict heap3[]) {
  //dict heap3[size1+size2];
  for(int i = 0; i < size1; i++) {
    heap3[i] = heap1[i];
    heap3[i].next = &heap3[i+1];
  }
  for(int i = 0; i < size2; i++) {
    heap3[i+size1] = heap2[i];
    heap3[i+size1].next = &heap3[i+size1+1];
  }
  heap3[size1+size2-1].next = NULL;
}

void dictPrint(dict* entry) {
  if(entry) {
    printf("Entry:\nlength->%d\nword->%s\nnext->%p\n", entry->length, entry->word, entry->next);
    return;
  }
  printf("NULL\n");
}