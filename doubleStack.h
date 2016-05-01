#define MAXSIZE 100

/* double Stack implementation */
typedef struct
{
    double items[MAXSIZE];
    int top;
}doubleStack;


/* double Stack prototypes */
void doubleStackInitialize(doubleStack *s); /* Initializing the Stack */
int doubleStackIsEmpty(doubleStack *s); /* Checks if the stack is empty or not */
int doubleStackIIsFull(doubleStack *s); /* Checks if the stack is full or not */
double doubleStackTop(doubleStack *s); /* Returns the top element from the Stack */
void doubleStackPush(doubleStack *s, double value); /* Push element into the Stack */
double doubleStackPop(doubleStack *s); /* Pops the last element from the Stack */
int doubleStackSize(doubleStack *s); /* Number of elements in the Stack */
