#include "../header/Dictionary.h"

const int WORD_SIZE = 4;

/*
dictInit()
Given a string, dict array, and the array's size, populates the dictionary.

void dictInit(const char* string, dict heap[], size_t size);
string    --> line of text to turn into a dictionary (linked list of dicts).
heap      --> preallocated memory for the linked list.
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
dict* dictInit(const char* string, dict heap[], size_t size) {
  // This ensures string isn't modified
  char sentence[strlen(string)+1];
  strcpy(sentence, string);
  char* sent = sentence;
  char* word;

  for(int i = 0; i < size; i++) {
    // Assumes size is also the word count (see Parser::countWords())
    word = strsep(&sent, " ");
    heap[i].length = strlen(word);
    strncpy(heap[i].word, word, WORD_SIZE);
    heap[i].word[4] = '\0';
    heap[i].next = &heap[i+1];
  }
  heap[size-1].next = NULL;

  dict* head = &heap[0];
  return head;
}

/*
dictClear()
Given a dict array and its size, NULLs all elements in the array.

void dictClear(dict heap[], size_t size);
heap      --> allocated memory for the linked list.
size      --> number of elemnets heap can store.

This function iterates through every element in heap and sets their contents to
0/NULL.

Returns nothing. Modifies heap.

Lucas Crockett
2022.11.03
*/
void dictClear(dict heap[], size_t size) {
  for(int i = 0; i < size; i++) {
    heap[i].length = 0;
    heap[i].word[0] = '\0';
    heap[i].next = NULL;
  }
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
  int len = strlen(string);
  char comp[WORD_SIZE+1];
  strncpy(comp, string, WORD_SIZE+1);
  
  dict* node = head;
  while( node != NULL ) {
    // If the same length
    if( (node->length == len) &&
      // and first WORD_SIZE characters match, case sensitive
      ( (caseSensitive && !strcmp(node->word, comp)) ||
      // or first WORD_SIZE characters match, case INsensitive
        (!caseSensitive && !strcasecmp(node->word, comp)) ) ) {
      return node;
    }
    node = node->next;
  }

  return NULL;
}

/*
dictAppend()
Given the heads of 2 dictionaries, links them into one list.

dict* dictAppend(dict* head1, dict* head2);
head1    --> pointer to the start of the first dictionary.
head2    --> pointer to the start of the second dictionary.

This function iterates through the first dictionary until it finds the last element,
then it links said element to head2. Returns the head of the combined list.

Returns a pointer to a dict struct, namely the head of the combined linked list.

Lucas Crockett
2022.11.02
*/
dict* dictAppend(dict* head1, dict* head2) {
  // Shortcuts for NULL pointers
  if( head1 == NULL ) { return head2; }
  if( head2 == NULL ) { return head1; }
  
  dict* node = head1;
  // Traverse up to the final node in the first dictionary
  while( node->next != NULL ) {
    node = node->next;
  }
  // Link final node to start of second dictionary.
  node->next = head2;

  return head1;
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
  if( entry1 == NULL ) { return 1; }
  if( entry2 == NULL ) { return -1; }
  
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
        // node == head
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

This function displays the contents of entry with printf(). If the passed 
pointer isn't valid, prints "NULL".

Returns nothing.

Lucas Crockett
2022.11.02
*/
void dictPrint(dict* entry) {
  if(entry) {
    printf("---Entry---\nlength -> %d\nword   -> %s\nnext   -> %p\n", entry->length, entry->word, entry->next);
    return;
  }
  printf("NULL\n");
}