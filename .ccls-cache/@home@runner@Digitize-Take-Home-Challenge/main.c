#include <stdio.h>
#include <string.h>

int main(void) {
  printf("Hello World\n");
  char* string = strdup("Hello Wrold");
  char* found;

  while( (found = strsep(&string, " ")) != NULL){
    printf("%s\n%s\n", string, found);
  }
  return 0;
}