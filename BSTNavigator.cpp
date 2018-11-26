#include <iostream>
#include <fstream>

#include "BinaryNode.h"
#include "PersonBST.h"

template <class ObjectType>
void writeOutput(std::ofstream *outfile, ObjectType output);

void preOrderPrint(BinaryNode<Person> rootNode, std::ofstream *outfile);

int main()
{
	std::ifstream inputFile;
	inputFile.open("InputData.txt");

	std::ofstream namesFile;
	namesFile.open("NamesOutput.txt");
	std::ofstream birthdaysFile;
	birthdaysFile.open("NamesOutput.txt");

	//CREATE BST USING INPUTDATA.TXT
	PersonBST nameDataBase = PersonBST();
	PersonBST birthdayDataBase = PersonBST();
	std::string name = "names";
	std::string birthday = "birthdays";
	while (inputFile)
	{
		if (inputFile.eof()) break;
		getline(inputFile, name, '\n');
		getline(inputFile, birthday, '\n');
		
		Person *newPerson = new Person(name, birthday);
		
		std::cout << "NOT EMTPY " << name << " "  << birthday << std::endl;
		nameDataBase.addByName(newPerson);

		birthdayDataBase.addByBirthday(newPerson);
	}

	
	//WRITE OUT EVERYONE IN PREORDER (NODE-LEFT-RIGHT)
	//AND POST-ORDER (LEFT-RIGHT-NODE)
	//FROM THE NAME DATABASE INTO  NamesOutput.txt
	
	std::cout << std::endl << std::endl;
	std::cout << "Now to show a preorder traversal of the name based binary search tree" << std::endl;
	BinaryNode<Person> rootNode = *nameDataBase.root;
	preOrderPrint(rootNode, &namesFile);


	//WRITE OUT EVERYONE INORDER (LEFT-NODE-RIGHT)
	//breadth-first

	//output file contains names and birthdays on a single line separated by tabs
	//EACH SECTION IDENTIFIED BY A HEADER (NOT THOSE HEADERS YOU BAFOON)

	inputFile.close();
	namesFile.close();
	birthdaysFile.close();
	return 0;
}

void preOrderPrint(BinaryNode<Person> rootNode, std::ofstream *outfile)
{
	BinaryNode<Person> *leftNode = rootNode.getLeftChild();
	BinaryNode<Person> *rightNode = rootNode.getRightChild();

	std::cout << "NODE" << std::endl;
	writeOutput(outfile, rootNode.getData()->getName());
	writeOutput(outfile, '\t');
	writeOutput(outfile, rootNode.getData()->getBirthday());
	writeOutput(outfile, '\n');
	std::cout << "LEFT" << std::endl;
	if(leftNode != nullptr)
		preOrderPrint(*leftNode, outfile);
	std::cout << "RIGHT" << std::endl;
	if(rightNode != nullptr)
		preOrderPrint(*rightNode, outfile);
}


template <class ObjectType>
void writeOutput(std::ofstream *outfile, ObjectType output)
{
	std::cout << output;
	*outfile << output;
}