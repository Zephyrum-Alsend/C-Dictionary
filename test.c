/*
This is the equivalent of scratch paper. It's not meant to be neat.
void test() functions as main().
*/

#include "test.h"

void test() {
  // printf("Hello World\n");
  // char* string = strdup("Hello Wrold");
  // char* found;

  // while( (found = strsep(&string, " ")) != NULL){
  //   printf("%s\n%s\n", string, found);
  // }

  // char userBuffer[LINE_MAX];
  // //char* userInput;

  // if( fgets(userBuffer, LINE_MAX, stdin) != NULL ) {
  //   size_t LEN = strlen(userBuffer);
  //   userBuffer[LEN-1] = '\0';
  //   char userInput[LEN];
  //   //userInput = strdup(userBuffer);
  //   //userInput = strsep(&userInput, "\n");
  //   //sscanf(userBuffer, "%[^\n]%*c", userInput);
  //   // strncpy(userInput, userBuffer, LEN);
  //   // userInput[LEN-1] = '\0';
  //   strcpy(userInput, userBuffer);
  //   printf("%sEND", userInput);
  //   for(int i = 0; i < LEN; i++){
  //     char c = userInput[i];
  //     c ? printf("'%c' ", c) : printf("'\\0' ");
  //   }
  // }

  /////////////////////////////////////////////////////////////////////////////
  // char string[100];
  // int inpLen = 10;
  // int number;

  // //string = readLine(4*sizeof(char));
  // scanLine(string, "Enter:\n", inpLen);
  // printf("Result: %s\n", string);
  // testString(string, inpLen);

  // number = scanInt("Enter:\n");
  // printf("%d", number);
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // char* test = getString();
  // printf("%s\n", test);
  /////////////////////////////////////////////////////////////////////////////
  
  // char* test = scanLine("This is a prompt:\n", 100);
  // printf("%s\n", test);

  /////////////////////////////////////////////////////////////////////////////
  // char* test = "This is a prompt";
  // dict* head;
  // head = dictInit(test);
  // dict* nex = head;
  // while( nex != NULL ) {
  //   dictPrint(nex);
  //   nex = nex->next;
  // }
  //dictPrint(head->next->next);
  /////////////////////////////////////////////////////////////////////////////
  
  /////////////////////////////////////////////////////////////////////////////
  // char trunc[4];
  // strncpy(trunc, test, 2);
  // printf("%s\n", trunc);
  // testString(trunc, 10);
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // char test2[strlen(test)+1];
  // strcpy(test2, test);
  // testString(test2, strlen(test)+1);
  // char* test3 = test;
  
  // char* found;
  // while((found = strsep(&test3, " ")) != NULL){
  //   printf("%s\n", found);
  // }
  // printf("test: %s\ntest2: %s\ntest3: %s\n", test, test2, test3);
  /////////////////////////////////////////////////////////////////////////////
  
  /////////////////////////////////////////////////////////////////////////////
  // printf("%i", scanInt("Enter number:\n"));
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // char* test = "This is a sentence.";
  // size_t size = countWords(test);
  // dict heap[size];
  // dictInit(test, heap, size);

  // char* test2 = "Also a sentence.";
  // size_t size2 = countWords(test2);
  // dict heap2[size2];
  // dictInit(test2, heap2, size2);

  // dict heap3[size+size2];
  // dictAppend(heap, size, heap2, size2, heap3);
  
  // dict* search = dictSearch("sEntence.", heap3, true);
  // dictPrint(search);
  // search = dictSearch("SENTEnCE.", heap3, false);
  // dictPrint(search);
  /////////////////////////////////////////////////////////////////////////////
  
  char* sortest = "aaaa aaa aa a";
  // char* sortest = "a aa aaa aaaa";
  // char* sortest = "aa a aaaa aaa";
  // char* sortest = "aaaa aaa";
  // char* sortest = "a B c d E f g";
  // char* sortest = "B a c d E g f";
  // char* sortest = "Bb bB A a c d E g f";
  size_t sortize = countWords(sortest);
  dict sortheap[sortize];
  dictInit(sortest, sortheap, sortize);

  dict* head = dictBubbleSort(sortheap);
  printf("\n//////////////////////////////\n\n");
  
  dict* node = head;
  while(node != NULL) {
    dictPrint(node);
    node = node->next;
  }
  /////////////////////////////////////////////////////////////////////////////
}

char* getString() {
  printf("This is a prompt:\n");
  const int INTERNAL_BUFFER = 100;
  
  char inputBuffer[INTERNAL_BUFFER];
  if( fgets(inputBuffer, INTERNAL_BUFFER, stdin) != NULL ) {
    // Check if the last character is \n, toss it if so
    int lastChar = strlen(inputBuffer) - 1;
    char input[lastChar+1];
    
    if(inputBuffer[lastChar] == '\n') {
      inputBuffer[lastChar] = '\0';
    }
    // If the user entered more than the buffer allowed, stdin needs cleaning
    else {
      flushStdin();
    }
    
    strcpy(input, inputBuffer);
    return input;
  }
  // If fgets() returns NULL, set input to NULL
  else {
    return NULL;
  }
}

void testString(char* string, int length){
  for(int i = 0; i < length; i++){
    char c = string[i];
    // If \0, prints '\0', otherwise prints character as is
    c ? printf("'%c' ", c) : printf("'\\0' ");
  }
  printf("\n");
}