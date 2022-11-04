# C-Dictionary
Console Application


On startup, the program will greet the user with 

"Enter a line of text:"

, waiting for user input terminated by a newline (hitting Enter on standard keyboards).
The program will then use this line of text to initialize a dictionary, a linked list of dict structs. Each dict contains the first four characters of a word, its
total length, and a pointer to the next dict struct in the list. A dictionary can contain duplicate dicts.
Dictionaries are automatically sorted alphabetically.


After initializing the dictionary, the program prompts the user for input again, but with the following message:

"Enter a corresponding number to perform the following:
1. Search (case sensitive)
2. Search (case insensitive)
3. Add Text
4. Clear Data
5. Display Dictionary
6. Exit"

Entering a number from this list will execute the stated option. All other inputs are ignored, causing the message to be restated.
When an option finishes execution, this prompt is displayed again and the user may once again enter a number to choose an option.


Search will prompt the user with the message 

"Search: "

and await user input terminated by a newline. It will then search the dictionary for a match to the entered string. Note that due to dict structs only storing up to 
the first four characters of any word, a false positive may occur if two words have matching lengths and starting characters. NULL is returned if no matches were 
found.
Both case sensitive and case insensitive searches use the same algorithm, simply ignoring differences in case for the latter.
As dictionaries define words as whitespace separated strings, this search will fail to find anything if a whitespace inclusive term is entered.
Search result is displayed in the format:

"---Entry---
length -> %d
word   -> %s
next   -> %p"

or

"NULL"

if no match.


Add Text will prompt the user with

"Enter a line of text:"

and await a newline terminated string from the user. After reading the string, it is used to initialize a second dictionary which is then appended to the first.
Ultimately, there is still just one dictionary in practice.
If there is not enough memory to store the second dictionary, its elements are truncated to fit in the space remaining. This will result in a loss of new data.
If there is no memory remaining, the program tells the user so with the following message:

"Unable to add new entries.
Out of memory."

Add Text will not ask for user input while no free memory remains.


Clear Data is used to reinitialize the dictionary, effectively deleting all entries. This will free up memory for Add Text.

"Clearing data..."

is displayed before beginning to clear the dictionary. After the clear is complete,

"Data cleared!"

is displayed.


Display Dictionary will iterate through the nodes of the dictionary and display them in the following format:

"Dictionary:
---Entry---
length -> %d
word   -> %s
next   -> %p
..."

No entries are displayed if no data exists in the dictionary (such as after Clear Data). "Dictionary:" is always displayed, regardless.


Exit exits the program.



Of note, this program uses fgets() to read user input, thereby limiting the amount of characters read from input. You may enter more characters than fgets() will
read, but all input after the limit is truncated. If the buffer limit is reached

"Buffer reached, input may be partially ignored.\n"

will be printed. Do note the wording "reached", as this can be triggered by inputting exactly enough to fill the buffer. Hence the warning states "May".
