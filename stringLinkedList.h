
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
