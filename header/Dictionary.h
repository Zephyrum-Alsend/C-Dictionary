#pragma once
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Contains information pertaining to a word.
typedef struct dict {
  int length;
  char word[5]; // WORD_SIZE in Dictionary.c must be set to this value -1.
  struct dict* next;
} dict;

// Given a string, dict array, and the array's size, populates the array with 
// data from string and returns a pointer to the head.
dict* dictInit(const char* string, dict heap[], size_t size);

// Given a dict aray and its size, clears the data inside.
void dictClear(dict heap[], size_t size);

// Nulls the passed dict struct.
void dictNodeDel(dict* node);

// Given a string and dictionary head, will return a pointer to the matching 
// dictionary entry. Can be case insensitive by setting caseSensitive to false.
dict* dictSearch(const char* string, dict* head, bool caseSensitive);

// Compares 2 dict structs. Returns negative if entry1 < entry2, positive if 
// entry1 > entry2, and 0 if entry1 == entry2.
int dictCompare(dict* entry1, dict* entry2);

// Given the heads of 2 dictionaries, links them into one list and returns the head.
dict* dictAppend(dict* head1, dict* head2);

// Given the head of a dictionary, sorts it alphabetically. Returns the new head.
dict* dictBubbleSort(dict* head);

// Removes duplicates from a sorted dictionary.
void dictRmvDup(dict* head);

// Reconstructs the heap so all entries are contiguous in memory.
unsigned int dictDefrag(dict* head, dict heap[], size_t size);

// Given a dictionary entry, prints its contents.
void dictPrint(dict* entry);