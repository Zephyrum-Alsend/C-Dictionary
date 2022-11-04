/*
This is a header for testing code. It's not meant to be well documented or structured.
It's basically the equivalent of scratch paper.
void test() functions as main().
*/

#pragma once
#include "UserIO.h"
#include "Dictionary.h"
#include "Parser.h"

extern const int PARSE_FAIL;

void testString(char* string, int length);

void printArr(dict arr[], size_t size);

char* getString();

void test();