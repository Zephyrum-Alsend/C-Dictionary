#pragma once
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

// ****PARSE_FAIL must be defined by the file including UserIO.****
extern const int PARSE_FAIL;

// Prompts the user for a line of text, up to size buffer. Returns the line of
// text.
const char *scanLine(const char *prompt, int buffer);

// Prompts the user for a single integer. Returns the value.
int scanInt(const char *prompt);

// Clears leftover data in stdin.
void flushStdin();