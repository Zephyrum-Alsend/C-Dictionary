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
start with the same WORD_SIZE characters and have identical lengths. If a match
is found, returns the pointer to said match. If no match is found, returns NULL.

Returns a pointer to a dict struct. Returns NULL if no match found.

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

/*
dictAppend()
Given the heaps for 2 dictionaries and their sizes, combines them into a third heap.

void dictAppend(dict heap1[], size_t size1, dict heap2[], size_t size2, dict heap3[]);
heap1    --> allocated memory of the first dictionary.
size1    --> number of elements in the first dictionary.
heap2    --> allocated memory of the second dictionary.
size2    --> number of elements in the second dictionary.
heap3    --> allocated memory of the third dictionary, assumed to be combined size of 
             first two.

This function copies the contents of heap1 and heap2 into heap3, correcting the links
in heap3 to point to their new addresses.

Returns nothing. Modifies heap3.

Lucas Crockett
2022.11.02
*/
void dictAppend(dict heap1[], size_t size1, dict heap2[], size_t size2, dict heap3[]) {
  // Copy heap1 into heap3
  for(int i = 0; i < size1; i++) {
    heap3[i] = heap1[i];
    heap3[i].next = &heap3[i+1];
  }
  // Copy heap2 into heap3, after heap1's data
  for(int i = 0; i < size2; i++) {
    heap3[i+size1] = heap2[i];
    heap3[i+size1].next = &heap3[i+size1+1];
  }
  // Set last element's .next to NULL
  heap3[size1+size2-1].next = NULL;
}

/*
dictCompare()
Compares 2 dict structs and returns which one is lesser/greater than the other.

int dictCompare(dict* entry1, dict* entry2);
entry1    --> dict struct to compare.
entry2    --> dict struct to compare.

This function first checks for NULL values and always sorts non-NULL before NULL.
Then the function compares dict.words case insensitively, to sort them 
alphabetically. If they match case insensitive, dict.words are compared case
sensitively, sorting upper before lower case within the same letter. If 
the dict.words are identical, dict.lengths are compared. If these, too, are
identical, the function declares the structs equal. Matching strcmp(), returns
a negative value if entry1 comes before entry2, 0 if matching, positive otherwise.

Returns an integer whose sign indicates sorting order.

Lucas Crockett
2022.11.02
*/
int dictCompare(dict* entry1, dict* entry2) {
  // NULL is greater than everything
  if( entry1 == NULL ) return 1;
  if( entry2 == NULL ) return -1;
  
  int comp = strcasecmp(entry1->word, entry2->word);
  
  // If case insensitive .word is the same, compare case
  if( !comp ) { comp = strcmp(entry1->word, entry2->word); }
  
  // If .word is identical, but .length is different
  if( (!comp) && (entry1->length != entry2->length) ) {
    comp = (entry1->length > entry2->length) ? 1 : -1;
  }
  
  return comp;
}

/*
dictBubbleSort()
Given the head of a dictionary, sorts it alphabetically, returning the new head.

dict* dictBubbleSort(dict* head);
head    --> pointer to the start of the dictionary.

This function iterates over the dictionary, swapping adjacent elements as
necessary, until all elements are sorted alphabetically. Returns the pointer
to the new head of the dictionary.

Returns a dict struct pointer.

Lucas Crockett
2022.11.02
*/
dict* dictBubbleSort(dict* head) {
  dict* node;
  dict* prev;
  bool swapped;

  // Go through the list at least once
  do {
    // Keep going through until nothing's been swapped
    node = head;
    prev = NULL;
    swapped = false;
    while( node != NULL )   {
      
      // If the current node should come after the next node
      if( dictCompare(node, node->next) > 0 ) {
        swapped = true;
        // Check if prev is not NULL
        if( prev != NULL ) {
          // Swap node and node->next
          prev->next = node->next;
          node->next = node->next->next;
          prev->next->next = node;
          node = prev;
        }
        else {
          // Swap node and node->next
          head = node->next;
          node->next = node->next->next;
          head->next = node;
          node = head;
          continue;
        }
      }

      // Increment indexes
      prev = node;
      node = node->next;
    }
    
  } while( swapped );
  
  return head;
}

/*
dictPrint()
Given the pointer to a dict struct, prints its contents.

void dictPrint(dict* entry);
entry    --> pointer to a dict struct.

This function displays the contents of entry with printf(). If the passed pointer isn't
valid, prints "NULL".

Returns nothing.

Lucas Crockett
2022.11.02
*/
void dictPrint(dict* entry) {
  if(entry) {
    printf("Entry:\nlength->%d\nword->%s\nnext->%p\n", entry->length, entry->word, entry->next);
    return;
  }
  printf("NULL\n");
}