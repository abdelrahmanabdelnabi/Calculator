#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
using namespace std;
#endif

#ifndef CHARSTACK_H
#define CHARSTACK_H
#include "charStack.h"
#endif


void charStackInitialize(charStack *s)
{
    s->top=0;
}

int charStackIsEmpty(charStack *s)
{
    if (s->top==0)
        return 1;
    else
        return 0;
}

int charStackIIsFull(charStack *s)
{
    if(s->top==MAXSIZE)
        return 1;
    else
        return 0;
}

char charStackTop(charStack *s)
{
    char x=charStackPop(s);
    charStackPush(s,x);
    return x;
}

void charStackPush(charStack *s, char value)
{
    s->items[s->top]=value;
    s->top++;
}

char charStackPop(charStack *s)
{
    char value;
    s->top--;
    value=s->items[s->top];
    return value;
}
