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

  int idx = 0;
  for(int i = 0; i < size; i++) {
    // Assumes size is also the word count (see Parser::countWords())
    word = strsep(&sent, " ");
    
    if(strlen(word) == 0) { continue; } // Skip empty words
    
    heap[idx].length = strlen(word);
    strncpy(heap[idx].word, word, WORD_SIZE);
    heap[idx].word[4] = '\0';
    heap[idx].next = &heap[idx+1];
    idx++;
  }
  if(idx == 0) { return NULL; }
  heap[idx-1].next = NULL;

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
    dictNodeDel(&heap[i]);
  }
}

/*
dictNodeDel()
Given a pointer to the node of a dictionary, NULLs the entry.

void dictBubbleSort(dict* node);
node    --> pointer to a dict struct.

This function sets all elements of the given dict struct to 0 / '\0' / NULL.
Will return immediately if given a NULL pointer.

Returns nothing. Modifies node.

Lucas Crockett
2022.11.06
*/
void dictNodeDel(dict* node) {
  if( node == NULL ) { return; }
  node->length = 0;
  node->word[0] = '\0';
  node->next = NULL;
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
  if( head == NULL ) { return NULL; }
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
  if( head == NULL ) { return NULL; }
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
dictRmvDup()
Given the head of a sorted dictionary, removes duplicate entries.

void dictRmvDup(dict* head);
head    --> pointer to the start of the dictionary.

This function iterates over the dictionary, comparing adjacent elements and unlinking
duplicates by setting node->next to node->next->next, then deleting the unlinked
node. This will create gaps in the heap, so it is recommended to run dictDefrag() 
afterwards.

Returns nothing. Modifies linked list.

Lucas Crockett
2022.11.06
*/
void dictRmvDup(dict* head) {
  // If head == NULL, while() never runs
  dict* node = head;
  dict* next = NULL;
  
  while( node != NULL ) {
    next = node->next;
    if( dictCompare(node, next) == 0 ) {
      node->next = node->next->next;
      
      dictNodeDel(next);
      
      continue; // Don't increment node pointer
    }

    node = node->next;
  }
}

/*
dictDefrag()
Given the head of a dictionary and its heap, defragments the heap.

unsigned int dictDefrag(dict* head, dict heap[], size_t size);
head    --> pointer to the start of the dictionary.
heap    --> array containing the dictionary.
size    --> number of elements heap can contain.

This function returns early if there's nothing to defrag (NULL head or size 1 heap). 
Uses the head to iterate over the linked list, counting the nodes. If the nodes are
too many to fit into heap, will print an error message and return the size of heap.
The function then iterates over the linked list again, copying the nodes into a 
local array. This ensures the elements within the array are sorted according to the 
linked list's order. The heap is then overwritten with the contents of the local
array. The total node count is returned.

The address of the new head is at &heap[0], however this cannot be changed by the 
function. It is strongly recommended to if( heapIdx != 0 ) { head = &heap[0]; }
after calling this function.

Returns an unsigned integer indicating the total node count.

Lucas Crockett
2022.11.06
*/
unsigned int dictDefrag(dict* head, dict heap[], size_t size) {
  // Shortcuts: if nothing to defrag, don't
  if( head == NULL ) { return 0; }
  if( size < 2 ) { return size; }

  // Count how many elements are actually in the linked list
  int count = 0;
  dict* node = head;
  while( node != NULL ) {
    count++;
    node = node->next;
  }
  // Return w/ error if actual count won't fit in the specified heap size
  if( count > size ) {
    printf("\nERR: Heap size too small to fit dictionary. Defrag halted.\nSize: %i\tNodes: %i\n", size, count);
    return size;
  }

  // Copy linked list into temp array, in order
  dict temp[count];
  count = 0; // Reuse as index
  node = head;
  while( node != NULL ) {
    temp[count].length = node->length;
    strcpy(temp[count].word, node->word);
    temp[count].next = NULL;
    count++;
    
    node = node->next;
  }

  // Copy temp array into heap and relink
  for(int i = 0; i < count; i++) {
    heap[i].length = temp[i].length;
    strcpy(heap[i].word, temp[i].word);
    heap[i].next = &heap[i+1];
  }
  heap[count-1].next = NULL;
  // Why not update head here?
  // It gets assigned correctly here, but changes to the wrong index out there
  // So for now, the caller has to handle updating the head

  // Return true element count
  return count;
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