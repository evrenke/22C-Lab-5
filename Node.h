#pragma once

template <class ObjectType>
class Node
{
private:
	Node * ptr;
	ObjectType* objectPtr;
protected:
	void setData(ObjectType* ot) {
		objectPtr = ot;
	}
public:
	Node() {
		ptr = nullptr;
		objectPtr = nullptr;
	}
	Node(Node *nextPtr, ObjectType *ot)
	{
		ptr = nextPtr;
		objectPtr = ot;
	}
	Node(ObjectType *ot)
	{
		ptr = nullptr;
		objectPtr = ot;
	}

	//Returns the pointer to the next Node
	Node* getNext() {
		return ptr;
	}

	void setNext(Node* nextPtr) {
		ptr = nextPtr;
	}

	//Returns the pointer to the object within the Node
	ObjectType* getData() {
		return objectPtr;
	}

	~Node()
	{
		delete objectPtr;
	}
};