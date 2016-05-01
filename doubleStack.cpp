void doubleStackInitialize(doubleStack *s)
{
    s->top=0;
}

int doubleStackIsEmpty(doubleStack *s)
{
    if (s->top==0)
        return 1;
    else
        return 0;
}

int doubleStackIIsFull(doubleStack *s)
{
    if(s->top==MAXSIZE)
        return 1;
    else
        return 0;
}

double doubleStackTop(doubleStack *s)
{
    double x=doubleStackPop(s);
    doubleStackPush(s,x);
    return x;
}

void doubleStackPush(doubleStack *s, double value)
{
    s->items[s->top]=value;
    s->top++;
}

double doubleStackPop(doubleStack *s)
{
    double value;
    s->top--;
    value=s->items[s->top];
    return value;
}

int doubleStackSize(doubleStack *s)
{
    int counter=0;
    doubleStack newStack;
    doubleStackInitialize(&newStack);
    while(!doubleStackIsEmpty(s))
    {
        counter++;
        doubleStackPush(&newStack, doubleStackPop(s));
    }
    while(!doubleStackIsEmpty(&newStack))
    {
        doubleStackPush(s, doubleStackPop(&newStack));
    }
    return counter;
}
