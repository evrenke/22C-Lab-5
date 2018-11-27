#pragma once
#include "BinaryNode.h"
#include "Person.h"
class PersonBST {
private:
	//Returns the left/rightmost node below a certain root (inclusive of the root itself)
	BinaryNode<Person>* getRightmost(BinaryNode<Person>*);
	BinaryNode<Person>* getLeftmost(BinaryNode<Person>*);
public:
	BinaryNode<Person>* root;
	PersonBST() { root = NULL; }
	PersonBST(Person *head) { root = new BinaryNode<Person>(head); }
	//Don't worry the children are deleted in the BinaryNode destructor
	~PersonBST() 
	{ 
		delete root; 
		root = nullptr;
	}

	//Overloads using Person are a wrapper for the BinaryNode version so you don't need to manually define the node.
	//Other one may still be called with no issue if there is a Node that must be added.
	void addByName(Person*);
	void addByName(BinaryNode<Person>*);

	void addByBirthday(Person*);
	void addByBirthday(BinaryNode<Person>*);

	//Returns NULL if none is found. Beware of carelessly dereferencing it
	Person* searchByName(std::string);
	Person* searchByBirthday(std::string);

	void PersonBST::remove(Person* toRemove);
	void remove(BinaryNode<Person>**);
};