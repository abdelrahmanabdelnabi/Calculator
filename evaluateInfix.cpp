#include "evaluateInfix.h"

enum TYPES
{
    REJECT = 0 ,
    INTEGER,
    REAL,
    NEGATIVE,
    OPERATOR,
    UNKNOWN,
    SPACE
};

/*                         INTEGER,  REAL, NEGATIVE, OPERATOR,  UNKNOWN,  SPACE */
int stateTable[][7] = {{0, INTEGER,  REAL, NEGATIVE, OPERATOR,  UNKNOWN,  SPACE},
/*  ROW 1  */   {INTEGER,  INTEGER,  REAL,   REJECT,  REJECT,   REJECT,  REJECT},
/*  ROW 2  */   {REAL,       REAL,  REJECT,  REJECT,  REJECT,   REJECT,  REJECT},
/*  ROW 3  */   {NEGATIVE, INTEGER,  REAL,   REJECT,  REJECT,   REJECT,  REJECT},
/*  ROW 4  */   {OPERATOR,  REJECT, REJECT,  REJECT,  REJECT,   REJECT,  REJECT},
/*  ROW 5  */   {UNKNOWN,   REJECT, REJECT,  REJECT,  REJECT,   UNKNOWN, REJECT},
/*  ROW 6  */   {SPACE,     REJECT, REJECT,  REJECT,  REJECT,   REJECT,  REJECT}};




double EvaluateInfix(string infix)
{
    // declare variables
    string postfix = "";
    double answer = 0;
    stringLinkedList tokens;

    postfix = ConvertInfixToPostfix(infix);

    /* handle multi digit numbers, negative, decimal, real ...etc */
    tokens = PostfixToList(postfix);

    cout <<"\nThe Infix expression = "<<infix;
    cout <<"\nThe Postfix expression = "<<postfix<<endl;

    answer = EvaluatePostfix(&tokens);

    cout<<"\nFinal answer = "<<answer<<endl;

    return answer;
}

void DisplayMenu() /* Displays Menu */
{
    cout << "*** Infix To Postfix Conversion & Evaluation ***\n"
        <<"Math Operators\n"
        <<"+ || Addition\n"
        <<"- || Subtraction\n"
        <<"* || Multiplication\n"
        <<"/ || Division\n"
        <<"% || Modulus\n"
        <<"^ || Power\n"
        <<"$ || Square Root\n"
        <<"s || Sin\n"
        <<"c || Cos\n"
        <<"t || Tan\n"
        <<"~ || Negative Number\n"
        <<"Sample Infix Equation: ((s(~4^5)*1.4)/($(23+2)-~2.8))*(c(1%2)/(7.28*.1987)^(t23))\n";
}

string ConvertInfixToPostfix(string infix) /* Converts Infix expression to Postfix expression */
{
    string postfix;
    charStack postfixStack;
    charStackInitialize(&postfixStack);
    int infixLength=infix.length();

    /* looping the infix string */
    for(int x = 0; x < infixLength; x++)
    {
        /* Adds the integers, decimals, and negative numbers to the postfix string */
        if((isdigit(infix[x])) || (infix[x] == '.') || (infix[x] == '~'))
        {
            postfix += infix[x];
        }
        /* Ignoring white spaces */
        else if(isspace(infix[x]))
        {
            continue;
        }
        else if(IsMathOperator(infix[x]))
        {
            postfix += " ";
            /* check the priority of math operators */
            while((!charStackIsEmpty(&postfixStack)) &&
                (OrderOfOperations(charStackTop(&postfixStack)) >= OrderOfOperations(infix[x])))
            {
                /* adds the top math operator from the stack to the Postfix String */
                postfix += charStackPop(&postfixStack);
            }
            /* push the current math operator into the Stack */
            charStackPush(&postfixStack, infix[x]);
        }
        /* pushes parentheses into Stack */
        else if(infix[x] == '(')
        {
            charStackPush(&postfixStack, infix[x]);
        }
        else if(infix[x] == ')')
        {
            /* pop the current math operator */
            while((!charStackIsEmpty(&postfixStack)) && (charStackTop(&postfixStack) != '('))
            {
                /* adds the math operator to the postfix string and continue till find '(' */
                postfix += charStackPop(&postfixStack);
            }

            if(!charStackIsEmpty(&postfixStack)) /* pop '(' */
            {
                charStackPop(&postfixStack);
            }
            else /* '(' not found */
            {
                cout<<"\nMISSING PARENTHESES\n";
                exit(1);
            }
        }
        else
        {
            cout<<"\nINVALID INPUT\n";
            exit(1);
        }
    }

    /* Adds the remaining math operators to the postfix string */
    while(!charStackIsEmpty(&postfixStack))
    {
        postfix += charStackPop(&postfixStack);
    }

    return postfix;
}

bool IsMathOperator(char token) /* Checks if the char is math operator or not */
{
    switch(tolower(token))
    {
        case '+': case '-': case '*': case '/': case '%': case '^': case '$': case 'c': case 's': case 't':
            return true;
            break;
        default:
           return false;
           break;
    }
}

int OrderOfOperations(char operation) /* returns the priority of the math operator */
{
    int priority = 0;
    switch(tolower(operation)) /* Handles capital letters */
    {
        case 'c': case 's': case 't':
           priority = 5;
           break;
        case '^': case '$':
           priority = 4;
           break;
        case '*': case '/': case '%':
           priority = 3;
           break;
        case '-':
           priority = 2;
           break;
        case '+':
           priority = 1;
           break;
    }
    return priority;
}

stringLinkedList PostfixToList(string postfix) /* Converts the postfix string into a linked list */
{
    stringLinkedList tokens;
    stringLinkedListInitialize(&tokens);

    char currentChar = ' ';
    int column = REJECT;
    int currentState = REJECT;
    string currentToken = "";

    /* Check the input and Parsing multi digit numbers */
    for(int x = 0; x < postfix.length(); )
    {
        currentChar = postfix[x];

        /* get the type of the current char */
        column = GetTypeColumn(currentChar);

        /* Checks if there's more than '.' in the same number ex 4.44.3 */
        if((currentState == REAL) && (column == REAL))
        {
            cout<<"\nINVALID INPUT\n";
            exit(1);
        }

        /* get the current state of the number to make sure it's valid or not */
        currentState = stateTable[currentState][column];

        if(currentState == REJECT) /* if true that means we successfully parsed a token */
        {
            if(currentToken != " ")
            {
                stringLinkedListAddTail(&tokens, currentToken);
            }
            currentToken = "";
        }
        else /* continue trying a sucessfull token */
        {
            currentToken += currentChar;
            x++;
        }

    }
    /* adds the last token */
    if(currentToken != " ")
    {
        stringLinkedListAddTail(&tokens, currentToken);
    }
    return tokens;
}

int GetTypeColumn(char& currentChar) /* Determines the nature of the char */
{
    /* check for white space */
    if(isspace(currentChar))
    {
        return SPACE;
    }

    /* check for integer numbers */
    else if(isdigit(currentChar))
    {
        return INTEGER;
    }

    /* check for real numbers */
    else if(currentChar == '.')
    {
        return REAL;
    }

    /* check for negative numbers */
    else if(currentChar == '~')
    {
        currentChar = '-';
        return NEGATIVE;
    }

    /* check for math operators */
    else if(IsMathOperator(currentChar))
    {
        return OPERATOR;
    }
    /* if anything else */
    return UNKNOWN;
}

double EvaluatePostfix(stringLinkedList* postfix) /* evaluate the postfix expression and returns the result */
{
    double firstNumber = 0;
    double secondNumber = 0;
    double result = 0;

    int postfixSize=SizeOfStringLinkedList(postfix);
    doubleStack resultStack;
    doubleStackInitialize(&resultStack);

    stringNode *temp = postfix->head;

    cout<<"\nCalculations\n";

    /* loops on the postfix expression till the end */
    for(int x = 0; x < postfixSize; x++)
    {
        /* push numbers into the stack */
        if((isdigit(temp->value[0]) || (temp->value[0] == '.')))
        {
           doubleStackPush(&resultStack, atof(temp->value.c_str()));
        }
        /* push negative numbers into the stack */
        else if((temp->value.length() > 1) && ((temp->value[0] == '-') &&
            (isdigit(temp->value[1]) || (temp->value[1] == '.'))))
        {
           doubleStackPush(&resultStack, atof(temp->value.c_str()));
        }
        /* if math operator, pop numbers from stack */
        else if(IsMathOperator(temp->value[0]) && (!doubleStackIsEmpty(&resultStack)))
        {
            char operattion = tolower(temp->value[0]); /* Handles Capital letters */

            /*  pop only once if the operation was something like Sin, Cos, Tan, Sqrt */
            if(operattion == '$' || operattion == 's' || operattion == 'c' || operattion == 't')
            {
                secondNumber = 0;
                firstNumber = doubleStackPop(&resultStack);
                result = Calculate(operattion, firstNumber, secondNumber);
                doubleStackPush(&resultStack, result);
            }
            else if(doubleStackSize(&resultStack) > 1)
            {
                secondNumber = doubleStackPop(&resultStack);
                firstNumber = doubleStackPop(&resultStack);
                result = Calculate(operattion, firstNumber, secondNumber);
                doubleStackPush(&resultStack,result);
            }
        }
        else /* If the input was wrong */
        {
           cout<<"\nINVALID INPUT\n";
           exit(1);
        }

        temp=temp->next;
    }
    /* pop the final result from the stack, and return it */
    if(!doubleStackIsEmpty(&resultStack))
    {
        result = doubleStackTop(&resultStack);
    }
    return result;
}

double Calculate(char operation, double firstNumber, double secondNumber) /* Make the operation and prints it on the screen */
{
    double result = 0;
    switch(tolower(operation)) /* to handle capital letters like 'S' instead of 's' for Sin */
    {
        case '+':
           cout << firstNumber << operation << secondNumber << " = ";
           result = firstNumber + secondNumber;
           break;
        case '-':
           cout << firstNumber << operation << secondNumber << " = ";
           result = firstNumber - secondNumber;
           break;
        case '*':
           cout << firstNumber << operation << secondNumber << " = ";
           result = firstNumber * secondNumber;
           break;
        case '/':
           cout << firstNumber << operation << secondNumber << " = ";
           result = firstNumber / secondNumber;
           break;
        case '%':
           cout << firstNumber << operation << secondNumber << " = ";
           result = ((int)firstNumber%(int)secondNumber)+modf(firstNumber , &secondNumber);
           break;
        case '^':
           cout << firstNumber << operation << secondNumber << " = ";
           result = pow(firstNumber, secondNumber);
           break;
        case '$':
           cout << "Sqrt(" << firstNumber << ") = ";
           result = sqrt(firstNumber);
           break;
        case 'c':
            cout << "Cos(" << firstNumber << ") = ";
            result = cos(firstNumber);
            break;
        case 's':
            cout << "Sin(" << firstNumber << ") = ";
            result = sin(firstNumber);
            break;
        case 't':
            cout << "Tan(" << firstNumber << ") = ";
            result = tan(firstNumber);
            break;
        default:
           result = 0;
           break;
    }
    cout << result << endl;
    return result;
}
