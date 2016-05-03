/*
 * List.cpp
 *
 *  Created on: Apr 28, 2016
 *      Author: abdelrahman
 */

#include "Node.cpp"

#include <stdlib.h>
#include <iostream>


template<class T> class List {

private:
	Node<T>* head;
	Node<T>* tail;

public:
	List() {
		this->head = NULL;
		this->tail = NULL;
	}

	void addHead(T data) {
		// allocate new node with the given data
		Node<T>* newNode = new Node<T>(data);

		// the new node points to the (previously) first
		// node in the list
		newNode->setNext(head);

		// make head point to the new node
		this->head = newNode;

		// if list was originally empty
		if (this->tail == NULL) {
			this->tail = newNode;
		}
	}

	void addTail(T data) {
		Node<T>* node = new Node<T>(data);

		// if list is originally empty
		if (tail == NULL) {
			this->tail = node;
			this->head = node;
		} else {
			this->tail->setNext(node);
			this->tail = node;
		}
	}

	void deleteHead()
	{
	    // if list is empty or has one node
	    if(tail == head)
	    {
	        // if not empty
	        if(head != NULL)
	            free(head);
	        head = tail = NULL;
	    }
	    else
	    {
	        Node<T>* temp = head;
	        head = head->getNext();
	        free(temp);
	    }

	}

	void deleteTail()
	{
	    // check if list is empty
	    if(tail == NULL)
	        return;

	    // check if there is only one node in the list
	    if(tail == head)
	    {
	        // only one node in the list
	        free(head);
	        head = tail = NULL;
	        return;
	    }

	    // else there are more than one node in the list
	    // loop the list and keep a pointer on the node before the last
	    Node<T>* prev;
	    Node<T>* traversal = head;

	    while(traversal != NULL)
	    {
	        prev = traversal;
	        traversal = traversal->next;
	    }
	    // free the last node
	    free(traversal);

	    // update the tail
	    tail = prev;

	    // update the last node's pointer
	    prev->next = NULL;
	}

	void traverse(){
		Node<T>* trav = head;

		while(trav != NULL){
			std::cout << trav->getData() << std::endl;
			trav = trav->getNext();
		}
	}

	bool isEmpty()
	{
	    return head == NULL ? true : false;
	}

};
