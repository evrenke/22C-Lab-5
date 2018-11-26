#include "PersonBST.h"
BinaryNode<Person>* PersonBST::getRightmost(BinaryNode<Person>* head) {
	BinaryNode<Person>* temp = head;
	while (temp->getRightChild() != NULL) {
		temp = temp->getRightChild();
	}
	return temp;
}
BinaryNode<Person>* PersonBST::getLeftmost(BinaryNode<Person>* head) {
	BinaryNode<Person>* temp = head;
	while (temp->getLeftChild() != NULL) {
		temp = temp->getLeftChild();
	}
	return temp;
}
/*
//Copies the tree to an array of pointers to a node and returns said array.
BinaryNode<Person>** PersonBST::copyToArr() {
	BinaryNode<Person>** arr = new BinaryNode<Person>*[size];
	copyToArr(arr, root);
	return arr;
}
void PersonBST::copyToArr(BinaryNode<Person>** arr, BinaryNode<Person>* start) {
	static int i = 0;
	if (start == NULL) return;
	arr[i] = start;
	copyToArr(arr, start->getLeftChild());
	copyToArr(arr, start->getRightChild());
}
*/
void PersonBST::addByName(Person *toAdd) {
	BinaryNode<Person>* pNode = new BinaryNode<Person>(toAdd);
	addByName(pNode);
}
void PersonBST::addByName(BinaryNode<Person>* pNode) {
	if (root == NULL) {
		root = pNode;
		return;
	}
	BinaryNode<Person>* temp = root;
	while (true) {
		if (pNode->getData()->getName() <  temp->getData()->getName()){
			if (temp->getLeftChild() == NULL) {
				temp->setLeftChild(pNode);
				return;
			}
			temp = temp->getLeftChild();
		}
		else {
			if (temp->getRightChild() == NULL) {
				temp->setRightChild(pNode);
				return;
			}
			temp = temp->getRightChild();
		}
	}
	size++;
}
void PersonBST::addByBirthday(Person *toAdd) {
	BinaryNode<Person>* pNode = new BinaryNode<Person>(toAdd);
	addByBirthday(pNode);
}
void PersonBST::addByBirthday(BinaryNode<Person>* pNode) {
	if (root == NULL) {
		root = pNode;
		return;
	}
	BinaryNode<Person>* temp = root;
	while (true) {
		if (pNode->getData()->getBirthday() < temp->getData()->getBirthday()) {
			if (temp->getLeftChild() == NULL) {
				temp->setLeftChild(pNode);
				return;
			}
			temp = temp->getLeftChild();
		}
		else {
			if (temp->getRightChild() == NULL) {
				temp->setRightChild(pNode);
				return;
			}
			temp = temp->getRightChild();
		}
	}
	size++;
}
/*
void PersonBST::sortByName() {
	BinaryNode<Person>** arr = copyToArr();
	for (int i = 0; i < size; i++) {
		addByName(arr[i]);
	}
}
void PersonBST::sortByBirthday() {
	BinaryNode<Person>** arr = copyToArr();
	for (int i = 0; i < size; i++) {
		addByBirthday(arr[i]);
	}
}
*/
Person* PersonBST::searchByBirthday(std::string bday) {
	BinaryNode<Person>* pSearch = root;
	while (true) {
		if (pSearch->getData()->getBirthday() == bday) {
			return pSearch->getData();
		}
		else if (pSearch->getData()->getBirthday() < bday) {
			if (pSearch->getLeftChild() == NULL) return NULL;
			pSearch = pSearch->getLeftChild();
		}
		else {
			if (pSearch->getRightChild() == NULL) return NULL;
			pSearch = pSearch->getRightChild();
		}
	}
}
Person* PersonBST::searchByName(std::string name) {
	BinaryNode<Person>* pSearch = root;
	while (true) {
		if (pSearch->getData()->getName() == name) {
			return pSearch->getData();
		}
		else if (pSearch->getData()->getName() < name) {
			if (pSearch->getLeftChild() == NULL) return NULL;
			pSearch = pSearch->getLeftChild();
		}
		else {
			if (pSearch->getRightChild() == NULL) return NULL;
			pSearch = pSearch->getRightChild();
		}
	}
}
void PersonBST::remove(BinaryNode<Person>* toRemove) {
	if (toRemove->getLeftChild() == NULL && toRemove->getRightChild() == NULL) {
		delete toRemove;
		return;
	}
	if (toRemove->getLeftChild() != NULL) {
		BinaryNode<Person>* pNode = getRightmost(toRemove->getLeftChild());
		toRemove->setInfo(pNode->getData());
		remove(pNode);
	}
	else {
		BinaryNode<Person>* pNode = getLeftmost(toRemove->getRightChild());
		toRemove->setInfo(pNode->getData());
		remove(pNode);
	}
}