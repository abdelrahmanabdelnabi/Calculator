#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
using namespace std;
#endif

#ifndef MAX_SIZE
#define MAX_SIZE
#define MAXSIZE 100
#endif


/* char Stack implementation */
typedef struct
{
    char items[MAXSIZE];
    int top;
}charStack;

/* char Stack prototypes */
void charStackInitialize(charStack *s); /* Initializing the Stack */
int charStackIsEmpty(charStack *s); /* Checks if the stack is empty or not */
int charStackIIsFull(charStack *s); /* Checks if the stack is full or not */
char charStackTop(charStack *s); /* Returns the top element from the Stack */
void charStackPush(charStack *s, char value); /* Push element into the Stack */
char charStackPop(charStack *s); /* Pops the last element from the Stack */
