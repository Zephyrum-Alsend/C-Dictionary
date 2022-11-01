#pragma once
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

/*
typedef struct{
  int BUFFER;
  FILE* stream;
  bool enfLim;
  char* repeatPrompt;
} RLstruct;

char* readLine(const int BUFFER, FILE* stream = stdin, bool enforceLimit = false, const char* repeatPrompt = "That entry was too long!\n");
*/

// Prompts the user for a line of text, up to size buffer. Puts the line in input.
void scanLine(char* input, const char* prompt, int buffer);

// Prompts the user for a single integer. Returns the value.
int scanInt(const char* prompt);

// Clears leftover data in stdin.
void flushStdin();