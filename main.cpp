/*
 * main.cpp
 *
 *  Created on: Apr 28, 2016
 *      Author: abdelrahman
 */

#include "List.cpp"

int main(int argc, char **argv) {
	List<int>* l = new List<int>();

	l->addTail(5);
	l->addTail(6);
	l->addHead(4);
	l->traverse();

}
