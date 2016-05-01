void stringLinkedListInitialize(stringLinkedList* stringList)
{
    stringList->head=NULL;
    stringList->tail=NULL;
}

int stringLinkedListIsEmpty(stringLinkedList* stringList)
{
    return stringList->head == NULL ? 1:0;

}

void stringLinkedListAddTail(stringLinkedList* stringList, string value)
{

    stringNode* node = newStringLinkedListNode(value);
    stringNode* last = stringList->tail;
    stringList->tail = node;

    if (last != NULL)
        last->next=node;
    else
        stringList->head=node;
}

stringNode* newStringLinkedListNode(string newValue)
{
    stringNode* node = new stringNode();

    node->next = NULL;

    node->value=newValue;

    return node;
}

void DisplayStringLinkedList(stringLinkedList* stringList)
{
    stringNode *temp = stringList->head;
    while(temp!=NULL)
    {
        if(temp->next!=NULL)
        {
            cout << temp->value << " ";
        }
        else
            cout << temp->value << " "; //Displays last element

        temp=temp->next;
    }
}

int SizeOfStringLinkedList(stringLinkedList* stringList)
{
    stringNode *temp = stringList->head;
    int counter=0;
    while(temp!=NULL)
    {
        if(temp->next!=NULL)
        {
            counter++;
        }
        else
            counter++; //Counts last element

        temp=temp->next;
    }
    return counter;
}
