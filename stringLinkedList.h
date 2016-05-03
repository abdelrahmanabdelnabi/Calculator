#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
using namespace std;
#endif

#ifndef MAX_SIZE
#define MAX_SIZE
#define MAXSIZE 100
#endif




/* Node of String Linked List */

typedef struct stringNode
{
    string value;
    struct stringNode *next;
} stringNode;

/* String Linked List Implementation */
typedef struct
{
    stringNode *head;
    stringNode *tail;
} stringLinkedList;


void stringLinkedListInitialize(stringLinkedList* stringList);
int stringLinkedListIsEmpty(stringLinkedList* stringList);
void stringLinkedListAddTail(stringLinkedList stringList, string value);
stringNode* newStringLinkedListNode(string value);
void DisplayStringLinkedList(stringLinkedList* stringList);
int SizeOfStringLinkedList(stringLinkedList* stringList);
