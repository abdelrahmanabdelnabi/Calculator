void DisplayMenu();
double EvaluateInfix(string infix);
string ConvertInfixToPostfix(string infix);
bool IsMathOperator(char token);
int OrderOfOperations(char token);
stringLinkedList PostfixToList(string postfix);
int GetTypeColumn(char& currentChar);
double EvaluatePostfix(stringLinkedList* postfix);
double Calculate(char token, double op1, double op2);
