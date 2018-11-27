#include "PersonBST.h"
#include <iostream>
BinaryNode<Person>* PersonBST::getRightmost(BinaryNode<Person>* head)
{
	BinaryNode<Person>* temp = head;
	while (temp->getRightChild() != NULL)
	{
		temp = temp->getRightChild();
	}
	return temp;
}

BinaryNode<Person>* PersonBST::getLeftmost(BinaryNode<Person>* head)
{
	BinaryNode<Person>* temp = head;
	while (temp->getLeftChild() != NULL)
	{
		temp = temp->getLeftChild();
	}
	return temp;
}

void PersonBST::addByName(Person *toAdd)
{
	BinaryNode<Person>* pNode = new BinaryNode<Person>(toAdd);
	addByName(pNode);
}

void PersonBST::addByName(BinaryNode<Person>* pNode)
{
	if (root == NULL)
	{
		root = pNode;
		return;
	}
	BinaryNode<Person>* temp = root;
	while (true)
	{
		if (pNode->getData()->getName() <  temp->getData()->getName())
		{
			if (temp->getLeftChild() == NULL)
			{
				temp->setLeftChild(pNode);
				return;
			}
			temp = temp->getLeftChild();
		}
		else
		{
			if (temp->getRightChild() == NULL)
			{
				temp->setRightChild(pNode);
				return;
			}
			temp = temp->getRightChild();
		}
	}
}

void PersonBST::addByBirthday(Person *toAdd)
{
	BinaryNode<Person>* pNode = new BinaryNode<Person>(toAdd);
	addByBirthday(pNode);
}

void PersonBST::addByBirthday(BinaryNode<Person>* pNode)
{
	if (root == NULL)
	{
		root = pNode;
		return;
	}
	BinaryNode<Person>* temp = root;
	while (true)
	{
		if (pNode->getData()->getBirthday() < temp->getData()->getBirthday())
		{
			if (temp->getLeftChild() == NULL)
			{
				temp->setLeftChild(pNode);
				return;
			}
			temp = temp->getLeftChild();
		}
		else
		{
			if (temp->getRightChild() == NULL)
			{
				temp->setRightChild(pNode);
				return;
			}
			temp = temp->getRightChild();
		}
	}
}

Person* PersonBST::searchByBirthday(std::string bday)
{
	BinaryNode<Person>* pSearch = root;
	while (true)
	{
		if (pSearch->getData()->getBirthday() == bday)
		{
			return pSearch->getData();
		}
		else if (pSearch->getData()->getBirthday() > bday)
		{
			if (pSearch->getLeftChild() == NULL) return nullptr;
			pSearch = pSearch->getLeftChild();
		}
		else
		{
			if (pSearch->getRightChild() == NULL) return nullptr;
			pSearch = pSearch->getRightChild();
		}
	}
}

Person* PersonBST::searchByName(std::string name)
{
	BinaryNode<Person>* pSearch = root;
	while (true)
	{
		if (pSearch->getData()->getName() == name)
		{
			return pSearch->getData();
		}
		else if (pSearch->getData()->getName() > name)
		{
			if (pSearch->getLeftChild() == nullptr) return nullptr;
			pSearch = pSearch->getLeftChild();
		}
		else
		{
			if (pSearch->getRightChild() == nullptr) return nullptr;
			pSearch = pSearch->getRightChild();
		}
	}
}

void PersonBST::remove(Person* toRemove) {
	BinaryNode<Person>** pSearch = &root;
	while (toRemove->getName() != (*pSearch)->getData()->getName()) {
		if ((*pSearch)->getData()->getName() > toRemove->getName()) {
			if ((*pSearch)->getLeftChild() == NULL)
				break;
			*pSearch = (*pSearch)->getLeftChild();
		}
		else if ((*pSearch)->getData()->getName() < toRemove->getName()) {
			if ((*pSearch)->getRightChild() == NULL)
				break;
			*pSearch = (*pSearch)->getRightChild();
		}
	}
	remove(pSearch);
}

void PersonBST::remove(BinaryNode<Person>** toRemove)
{
	if ((*toRemove)->getLeftChild() == NULL && (*toRemove)->getRightChild() == NULL)
	{
		delete *toRemove;
		toRemove = nullptr;
		std::cout << "Removed" << std::endl;
		return;
	}
	if ((*toRemove)->getLeftChild() != NULL)
	{
		BinaryNode<Person>* pNode = getRightmost((*toRemove)->getLeftChild());
		(*toRemove)->setInfo(pNode->getData());
		toRemove = &pNode;
		remove(&pNode);
	}
	else
	{
		BinaryNode<Person>* pNode = getLeftmost((*toRemove)->getRightChild());
		(*toRemove)->setInfo(pNode->getData());
		toRemove = &pNode;
		remove(&pNode);
	}
}