/*
 * Node.cpp
 *
 *  Created on: Apr 28, 2016
 *      Author: abdelrahman
 */
#include <stdlib.h>


template <class T> class Node {

private:
	T data;
	Node *next;

public:
	Node(T ndata){
		this->data = ndata;
		this->next = NULL;
	}

	T getData(){
		return this->data;
	}

	void setData(T data) {
		this->data = data;
	}

	 Node* getNext()  {
		return next;
	}

	void setNext(Node* next) {
		this->next = next;
	}
};
