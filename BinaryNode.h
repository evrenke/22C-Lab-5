#pragma once
#include "Node.h"
template<class ot>
class BinaryNode : public Node<ot> {
private:
	BinaryNode<ot>* rightChild;
	BinaryNode<ot>* leftChild;
public:
	BinaryNode() {
		setData(nullptr);
		setLeftChild(nullptr);
		setRightChild(nullptr);
	}
	BinaryNode(ot *object) {
		this->setData(object);
	}

	BinaryNode<ot>* getLeftChild() { return leftChild; }
	void setLeftChild(BinaryNode<ot>* in) { leftChild = in; }
	BinaryNode<ot>* getRightChild() { return rightChild; }
	void setRightChild(BinaryNode<ot>* in) { rightChild = in; }
	ot* getInfo() { return this->getData(); }
	void setInfo(ot* in) { this->setData(in); }

	//Deletes all nodes below to prevent memory leaks. Deleting the root will delete the entire tree.
	//If removing a single node from the tree is desired, use the remove function within the BST class instead.
	~BinaryNode() {
		delete this->getData();
		delete rightChild;
		delete leftChild;
	}
};