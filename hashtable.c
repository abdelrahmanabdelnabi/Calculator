/*
 * hashtable.c
 *
 *  Created on: May 15, 2016
 *      Author: abdelrahman
 */


/*
 * includes structures and functions for
 * Variable
 * List
 * HashTable
 */

/*********************************************************************************************/
/*************************************** INCLUDES ********************************************/
/*********************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>

/*********************************************************************************************/
/********************************* STRUCTURE DEFINITIONS *************************************/
/*********************************************************************************************/

// structure of a variable
typedef struct Variable {
	char name[15];
	double value;
} Variable;

// structure of a node variable

typedef struct Node {
	Variable variable;
	struct Node* next;
} Node;

// structure of a list

typedef struct List {
	Node* head;
	Node* tail;

} List;

#define HTSIZE 26

typedef struct HashTable {
	List* table[HTSIZE];
} HashTable;

/***************************************************************************************/
/****************************** FUNCTION PROTOTYPES ************************************/
/***************************************************************************************/
// fuctions for Variable
char* VariableToString(Node* n);

// fuctions for Node

Node* newNode(char* name, double value);

char* getName(Node* n);

double getValue(Node* n);

void setName(Node* n, char* value);

// functions for List

void initList(List* list);

void addHead(List* list, char* name, double value);

void addTail(List* list, char* name, double value);

void deleteHead(List* list);

void deleteTail(List* list);

Node* searchList(List* l, char* name);

int isEmpty(List* list);

char* listToString(List* list);

// functions for hash table

void initHashTable(HashTable* t);

int Hash(char* variableName);

void addToHash(HashTable* t, char* name, double value);

void addVariableToHash(HashTable* t, Variable v);

double getValueForName(HashTable* t, char* name);

char* tableToString(HashTable* t);

/*********************************************************************************************/
/******************************* FUNCTIONS IMPLEMENTATION ************************************/
/************************************ NODE FUNCTIONS *****************************************/
/*********************************************************************************************/

// create a new node with a given variable name and value
Node* newNode(char* name, double value) {
	Node* n = (Node*) malloc(sizeof(Node));

	strcpy(n->variable.name, name);
	n->variable.value = value;
	n->next = NULL;

	return n;
}

/***********************************************************/
char* getName(Node* n) {
	if (n == NULL)
		return NULL;
	return n->variable.name;
}
/***********************************************************/
double getValue(Node* n) {
	if (n == NULL)
		return INT_MIN;

	return n->variable.value;
}
/***********************************************************/

void setName(Node* n, char* name) {
	if (n == NULL || name == NULL) {
		return;
	}

	// else
	strcpy(n->variable.name, name);
}
/***********************************************************/
void setValue(Node* n, double value) {
	n->variable.value = value;
}

/*********************************************************************************************/
/*********************************** VARIABLE FUCTIONS ***************************************/
/*********************************************************************************************/

char* VariableToString(Node* n) {
	if (n == NULL)
		return NULL;

	char* str = (char*) malloc(10 * sizeof(char));
	str[0] = '\0';

	sprintf(str, "%s = %.2lf", n->variable.name, n->variable.value);

	return str;
}
/*********************************************************************************************/
/************************************* LIST FUNCTIONS ****************************************/
/*********************************************************************************************/

// initialize the linked list
void initList(List* list) {
	list->head = NULL;
	list->tail = NULL;
}

int getListSize(List* list) {
	if (list == NULL)
		return 0;

	Node* traversal = list->head;

	int count = 0;

	while (traversal != NULL) {
		count++;
		traversal = traversal->next;
	}
	return count;

}

/***********************************************************/
/* checks if a given node exits in a given list
 * returns 1 if it exists
 * returns 0 if it doesnt
 */
int NodeExistsInList(List* list, Node* n) {
	if (list->head == NULL || n == NULL)
		return 0;

	// traversal pointer
	Node* trav = list->head;

	// loop the list looking for the node
	while (trav != NULL) {
		if (trav == n)
			return 1;
		trav = trav->next;
	}

	// node doesnt exist in list
	return 0;
}
/***********************************************************/
void addHead(List* list, char* name, double value) {
	Node* node = newNode(name, value);
	node->next = list->head;
	list->head = node;

	// if the list was originally empty
	// then set the tail to point at the node just created
	if (list->tail == NULL) {
		list->tail = node;
	}
}
/***********************************************************/
void addTail(List* list, char* name, double value) {
	Node* node = newNode(name, value);

	// special case: first node in list
	if (list->tail == NULL) {
		list->tail = node;
		list->head = node;
	} else {
		list->tail->next = node;
		list->tail = node;
	}
}
/***********************************************************/
void deleteHead(List* list) {
	// if list is empty or has one node
	if (list->tail == list->head) {
		// if not empty
		if (list->head != NULL)
			free(list->head);
		initList(list);
	} else {
		Node* temp = list->head;
		list->head = list->head->next;
		free(temp);
	}

}
/***********************************************************/
void deleteTail(List* list) {
	// check if list is empty
	if (list->tail == NULL)
		return;

	// check if there is only one node in the list
	if (list->tail == list->head) {
		// only one node in the list
		free(list->head);
		list->head = list->tail = NULL;
		return;
	}

	// else there are more than one node in the list
	// loop the list and keep a pointer on the node before the last
	Node* prev;
	Node* traversal = list->head;

	while (traversal != NULL) {
		prev = traversal;
		traversal = traversal->next;
	}
	// free the last node
	free(traversal);

	// update the tail
	list->tail = prev;

	// update the last node's pointer
	prev->next = NULL;
}
/***********************************************************/
// deletes a given node from a list
void deleteNode(List* list, Node* n) {

	if (list->head == NULL)
		return;

	if (n == NULL)
		return;

	// check if node given exists in the list
	if (!NodeExistsInList(list, n))
		return;

	// check if there is only one node in the list
	if (list->tail == list->head) {
		free(list->head);
		list->head = list->tail = NULL;
		return;
	}

	// loop the list and keep a pointer on the node before the node to be deleted
	Node* prev;
	Node* traversal = list->head;

	while (traversal != n) {
		prev = traversal;
		traversal = traversal->next;
	}

	// update the "next" of the node before the node to be deleted
	prev->next = traversal->next;

	// update the tail if the node to be deleted was the last node
	if (traversal == list->tail)
		list->tail = prev;

	//update the head if the node to be deleted was the first node in the list
	if (traversal == list->head)
		list->head = traversal->next;

	// delete the node
	free(traversal);
}
/***********************************************************/
int isEmpty(List* list) {
	return list->head == NULL ? 1 : 0;
}

/***********************************************************/

Node* searchList(List* list, char* name) {
	if (list == NULL || name == NULL)
		return NULL;

	// traversal pointer
	Node* trav = list->head;

	// loop the list looking for the node
	while (trav != NULL) {
		if (strcmp(trav->variable.name, name) == 0)
			return trav;

		trav = trav->next;
	}

	return NULL;

}

char* listToString(List* list) {
	if (list == NULL)
		return NULL;

	// allocate memory for string
	// assuming each variable will require 20 characters to represent it
	int size = getListSize(list);
	char* str = (char*) malloc(20 * size * sizeof(char));

	// empty the string
	str[0] = '\0';

	if (isEmpty(list))
		return NULL;

	// loop through the list and add each term to the string
	Node* n = list->head;
	while (n != NULL) {
		char* variable = VariableToString(n);

		// concatenate the "variable" string to the polynomial string
		strcat(str, variable);

		// add a space to separate terms
		strcat(str, " ");

		// go to the next node
		n = n->next;
	}

	return str;

}

/*********************************************************************************************/
/********************************* HASH TABLE FUNCTIONS **************************************/
/*********************************************************************************************/

void initHashTable(HashTable* t) {
	int i;
	for (i = 0; i < HTSIZE; i++) {
		t->table[i] = NULL;
	}
}

int Hash(char* variableName) {
	if (variableName == NULL)
		return -1;
	if (!isalpha(variableName[0]))
		return -1;

	return tolower(variableName[0]) - 'a';
}

void addToHash(HashTable* t, char* name, double value) {
	int hash = Hash(name);

	if (t->table[hash] == NULL) {
		t->table[hash] = (List*) malloc(sizeof(List));
	}

	List* l = t->table[hash];

	Node* result = searchList(l, name);

	if (result != NULL) {
		// replace original variable's value with new value
		result->variable.value = value;
	} else {
		addTail(l, name, value);
	}
}

void addVariableToHash(HashTable* t, Variable v) {
	addToHash(t, v.name, v.value);
}

double getValueForName(HashTable* t, char* name) {
	if (t == NULL || name == NULL)
		return INT_MIN;

	int hash = Hash(name);

	if (hash == -1) {
		return INT_MIN;

	}

	List* l = t->table[hash];

	Node* result = searchList(l, name);

	if (result == NULL)
		return INT_MIN;

	return result->variable.value;
}

char* tableToString(HashTable* t) {

	// get the total number of variable in the hashtable
	int i, numOfVariable = 0;

	for (i = 0; i < HTSIZE; i++) {
		numOfVariable += getListSize(t->table[i]);
	}

	// allocate memory for string representation of hashtable
	// assuming each variable will require 20 characters
	char* str = (char*) malloc(20 * numOfVariable * sizeof(char));

	// empty the string
	str[0] = '\0';

	// loop through the hashtable and add each list to the string
	for (i = 0; i < HTSIZE; i++) {
		char* list = listToString(t->table[i]);

		// concatenate the "list" string to the string
		if (list == NULL) {
			strcat(str, "EMPTY LIST");
		} else {
			strcat(str, list);
		}

		// insert a newline to separate terms
		strcat(str, "\n");
	}

	return str;
}

int main(void) {

	HashTable t;

	initHashTable(&t);

	char a1[5] = "X";
	char a2[5] = "xy";
	char a3[5] = "xx";
	char a4[5] = "a";
	char a5[5] = "b";
	char a6[5] = "A";
	char a7[5] = "Z";
	char a8[5] = "inc";
	char a9[5] = "lsj";
	char a10[5] = "sdf";
	char a11[5] = "grx";
	char a12[5] = "yfg";
	char a13[5] = "dsf";
	char a14[5] = "inc"; // notice a variable already exits with this name,
						 // the variable with this name in the list will have the
						 // newest value, i.e. old values are overwritten
	addToHash(&t, a1, 5.0);
	addToHash(&t, a2, 6.0);
	addToHash(&t, a3, 7.0);
	addToHash(&t, a4, 8.0);
	addToHash(&t, a5, 9.0);
	addToHash(&t, a6, 10.0);
	addToHash(&t, a7, 11.0);
	addToHash(&t, a8, 12.0);
	addToHash(&t, a9, 13.0);
	addToHash(&t, a10, 14.0);
	addToHash(&t, a11, 15.0);
	addToHash(&t, a12, 16.0);
	addToHash(&t, a13, 17.0);
	addToHash(&t, a14, 18.0);

	printf("HashTable:\n%s", tableToString(&t));

	return 0;
}
