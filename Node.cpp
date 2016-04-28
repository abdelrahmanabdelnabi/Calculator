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
		this->data = data;
		this->next = NULL;
	}

	T getData(){
		return data;
	}

	void setData(T data) {
		this->data = data;
	}

	const Node*& getNext() const {
		return next;
	}

	void setNext(const Node*& next) {
		this->next = next;
	}
};
