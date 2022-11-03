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

// Given a string, converts it into a dict struct and returns the new struct.
dict dictCreate(const char* string);

// Given a string, dict array, and the array's size, populates the array with 
// data from string.
void dictInit(const char* string, dict heap[], size_t size);

// Given a string and dictionary head, will return a pointer to the matching 
// dictionary entry. Can be case insensitive by setting caseSensitive to false.
dict* dictSearch(const char* string, dict* head, bool caseSensitive);

// Given 2 dict arrays and their sizes, copies their data into a third dict array.
void dictAppend(dict heap1[], size_t size1, dict heap2[], size_t size2, dict heap3[]);

// Given the head of a dictionary, sorts it alphabetically. Returns the new head.
dict dictSort(dict heap[]);

// Given a dictionary entry, prints its contents.
void dictPrint(dict* entry);