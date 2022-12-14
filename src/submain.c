#include "../header/submain.h"

const int PARSE_FAIL = 0;

/*
run()
Main.

void run()

This functions serves as main(). After initializing reusable variables and 
pointers, prompts the user for a line of text. This line is used to initialize
a dictionary. The user is then prompted with the main menu, where integer inputs
lead to subroutines including: Search (case in/sensitive), Add Text, Clear Data,
Display Dictionary, and Exit. Depending on the option and available memory
(preallocated in heap), will ask for input or display data.

Returns nothing.

Lucas Crockett
2022.11.03
*/
void run() {
  // Text display variables
  char* startPrompt = "\nEnter a line of text:\n";
  char* menuPrompt =
  "\nEnter a corresponding number to perform the following:\n"
  "1. Search (case sensitive)\n"
  "2. Search (case insensitive)\n"
  "3. Add Text\n"
  "4. Clear Data\n"
  "5. Display Dictionary\n"
  "6. Exit\n";
  char* searchPrompt = "\nSearch: ";
  char* fullPrompt = "\nUnable to add new entries.\nOut of memory.\n";
  char* clearPrompt = "\nClearing data...";
  char* clearConfirm = "\nData cleared!\n";
  char* displayPrompt = "\nDictionary:\n";

  // User input variables
  char* userText;
  int userInt = 0;
  const size_t USER_BUFFER = 1024;

  // Dictionary variables
  const unsigned int HEAP_SIZE = 1024;
  dict heap[HEAP_SIZE];
  unsigned int elemCnt = 0; // Maintains count of initialized elements
  unsigned int heapIdx = 0; // Index of next uninitialized element
  unsigned int subElemCnt = 0; // Count of new elements to initialize
  dict* head;
  dict* node;

  // Initialize with user input
  userText = scanLine(startPrompt, USER_BUFFER);
  
  subElemCnt = countWords(userText);
  // If subElemCnt is larger than HEAP_SIZE, set it to HEAP_SIZE
  subElemCnt = (subElemCnt > HEAP_SIZE) ? HEAP_SIZE : subElemCnt;
  head = dictBubbleSort(dictInit(userText, &heap[heapIdx], subElemCnt));
  elemCnt += subElemCnt;
  heapIdx = elemCnt;

  // Main menu loop
  while( userInt != 6 ) {
    userInt = scanInt(menuPrompt);
    switch ( userInt ) {
      // Short circuit on PARSE_FAIL
      case PARSE_FAIL:
        break;
      
      // Search (case sensitive)
      case 1:
        dictPrint(dictSearch(scanLine(searchPrompt, USER_BUFFER), head, true));
        break;
      
      // Search (case insensitive)
      case 2:
        dictPrint(dictSearch(scanLine(searchPrompt, USER_BUFFER), head, false));
        break;
      
      // Add Text
      case 3:
        // Don't if heap's full
        if( elemCnt >= HEAP_SIZE ) {
          printf("%s", fullPrompt);
          break;
        }
        
        userText = scanLine(startPrompt, USER_BUFFER);
        subElemCnt = countWords(userText);
        subElemCnt = ( (heapIdx+subElemCnt) > HEAP_SIZE ) ? (HEAP_SIZE-heapIdx) : subElemCnt;
        head = dictBubbleSort(dictAppend(head, dictInit(userText, &heap[heapIdx], subElemCnt)));
        elemCnt += subElemCnt;
        heapIdx = elemCnt;
        break;
      
      // Clear Data
      case 4:
        printf(clearPrompt);
        dictClear(heap, HEAP_SIZE);
        elemCnt = 0;
        heapIdx = 0;
        head = NULL;
        printf(clearConfirm);
        break;
      
      // Display Dictionary
      case 5:
        printf("%s", displayPrompt);
        node = head;
        while( node != NULL ) {
          dictPrint(node);
          node = node->next;
        }
        break;
    }
  }
}