#pragma once
#include "BinaryNode.h"
#include "Person.h"
class PersonBST {
private:
	BinaryNode<Person>* root;
	int size;
	//Returns the left/rightmost node below a certain root (inclusive of the root itself)
	BinaryNode<Person>* getRightmost(BinaryNode<Person>*);
	BinaryNode<Person>* getLeftmost(BinaryNode<Person>*);
	//Copies the contents of the tree to an array. Used for re-sorting as temporary storage
	BinaryNode<Person>** copyToArr();
	void copyToArr(BinaryNode<Person>**, BinaryNode<Person>*);
public:
	PersonBST() { root = NULL; }
	PersonBST(Person head) { root = new BinaryNode<Person>(head); }
	//Don't worry the children are deleted in the BinaryNode destructor
	~PersonBST() { delete root; }

	//Overloads using Person are a wrapper for the BinaryNode version so you don't need to manually define the node.
	//Other one may still be called with no issue if there is a Node that must be added.
	void addByName(Person);
	void addByName(BinaryNode<Person>*);

	void addByBirthday(Person);
	void addByBirthday(BinaryNode<Person>*);

	void sortByName();
	void sortByBirthday();

	//Returns NULL if none is found. Beware of carelessly dereferencing it
	Person* searchByName(std::string);
	Person* searchByBirthday(std::string);

	void remove(BinaryNode<Person>*);
};