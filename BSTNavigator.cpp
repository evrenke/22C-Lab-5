#include <iostream>
#include <fstream>

#include "BinaryNode.h"
#include "PersonBST.h"
#include "Menu.h"

template <class ObjectType>
void writeOutput(std::ofstream *outfile, ObjectType output);

void pause();

void displayPreOrder(BinaryNode<Person> *rootNode, std::ofstream *outfile, bool isOnSameLine);
void displayInOrder(BinaryNode<Person> *rootNode, std::ofstream *outfile, bool isOnSameLine);
void displayPostOrder(BinaryNode<Person> *rootNode, std::ofstream *outfile, bool isOnSameLine);

int main()
{
	std::ofstream namesFile;
	std::ofstream birthdaysFile;

	//CREATE BST USING INPUTDATA.TXT
	std::ifstream inputFile;
	inputFile.open("InputData.txt");
	PersonBST nameDataBase = PersonBST();
	PersonBST birthdayDataBase = PersonBST();
	std::string name = "names";
	std::string birthday = "birthdays";
	while (inputFile)
	{
		if (inputFile.eof()) break;
		getline(inputFile, name, '\n');
		getline(inputFile, birthday, '\n');
		
		Person *newNamePerson = new Person(name, birthday);
		Person *newBirthdayPerson = new Person(name, birthday);
		
		nameDataBase.addByName(newNamePerson);
		birthdayDataBase.addByBirthday(newBirthdayPerson);
	}
	inputFile.close();

	//USER INTERACTION WITH DATABASE
	int length = 8;
	std::string options[] =
	{
		"Enter a new person", // option 1
		"Search for a person in database",// option 2
		"Modify a persons data",// option 3
		"Remove a person from the database",// option 4
		"Display database in name-based preorder sequence",// option 5
		"Display database in name-based postorder sequence",// option 6
		"Display database in birthday-based inorder sequence",// option 7
		"Exit program"// option 8
	};
	Menu menu = Menu(options, length);

	std::ofstream outputPerson;
	int option = 0;
	std::string inputStr;
	int inputInt;
	Person *newNamePerson = nullptr, *newBirthdayPerson = nullptr, *found = nullptr;
	BinaryNode<Person> *rootNode;

	while (option != length)
	{
		option = menu.printOptionsList();
		switch (option)
		{
		case 1://enter new person to database
			outputPerson.open("InputData.txt", std::fstream::app);
			std::cout << "Enter the new persons name:" << std::endl;
			name = menu.takeStringInput();
			birthday = "";
			std::cout << "Enter the new persons birthday date (1-31):" << std::endl;
			inputInt = menu.takeRangedIntInput(1, 31);
			if (inputInt < 10)
				birthday += '0';
			birthday += std::to_string(inputInt) + "/";
			std::cout << "Enter the new persons birthday month (1-12):" << std::endl;
			inputInt = menu.takeRangedIntInput(1, 12);
			if (inputInt < 10)
				birthday += '0';
			birthday += std::to_string(inputInt) + "/";
			std::cout << "Enter the new persons birthday year (1900-2018):" << std::endl;
			inputInt = menu.takeRangedIntInput(1900, 2018);
			birthday += std::to_string(inputInt);

			newNamePerson = new Person(name, birthday);
			newBirthdayPerson = new Person(name, birthday);

			nameDataBase.addByName(newNamePerson);
			birthdayDataBase.addByBirthday(newBirthdayPerson);

			outputPerson << std::endl << name << std::endl << birthday;
			outputPerson.close();
			break;
		case 2://Search a person from the database
			std::cout << "What is the name of the person you would like to SEARCH?" << std::endl;
			name = menu.takeStringInput();
			found = nameDataBase.searchByName(name);
			if (found == nullptr)
			{
				std::cout << name << " was not found in the database." << std::endl;
			}
			else
			{
				std::cout << found->getName() << " was found with birthday " << found->getBirthday() << " ." << std::endl;
			}
			pause();
			break;
		case 3://Modify a persons data from the database
			std::cout << "What is the name of the person you would like to MODIFY the name or birthdays of?" << std::endl;
			name = menu.takeStringInput();
			found = nameDataBase.searchByName(name);
			if (found == nullptr)
			{
				std::cout << name << " was not found in the database." << std::endl;
			}
			else
			{
				std::cout << found->getName() << " was found with birthday " << found->getBirthday() << " ." << std::endl;
			}

			while (inputStr != "n" && inputStr != "N")
			{
				std::cout << "Are you going to be modifying their name? (y or n)" << std::endl;
				inputStr = menu.takeCharInput();
				if (inputStr == "y" || inputStr == "Y")
				{
					std::cout << "Enter the new name of " << found->getName() << std::endl;
					inputStr = menu.takeStringInput();
					found->setName(inputStr);
					if (birthdayDataBase.searchByBirthday(found->getBirthday()) == nullptr)
						std::cout << "Null" << std::endl;// ->setName(inputStr);
					inputStr = "n";
				}
			}
			inputStr = "y";
			while (inputStr != "n" && inputStr != "N")
			{
				std::cout << "Are you going to be modifying their birthday? (y or n)" << std::endl;
				inputStr = menu.takeCharInput();
				if (inputStr == "y" || inputStr == "Y")
				{
					birthday = "";
					std::cout << "Enter the new persons birthday date (1-31):" << std::endl;
					inputInt = menu.takeRangedIntInput(1, 31);
					birthday += std::to_string(inputInt) + "/";
					std::cout << "Enter the new persons birthday month (1-12):" << std::endl;
					inputInt = menu.takeRangedIntInput(1, 12);
					birthday += std::to_string(inputInt) + "/";
					std::cout << "Enter the new persons birthday year (1900-2018):" << std::endl;
					inputInt = menu.takeRangedIntInput(1900, 2018);
					birthday += std::to_string(inputInt);
					birthdayDataBase.searchByBirthday(found->getBirthday())->setBirthday(birthday);
					found->setBirthday(birthday);
					inputStr = "n";
				}
			}
			
			outputPerson.open("InputData.txt");//deletes previous data
			//now the database will be inorder traversed to add modified into back into the file
			displayPreOrder(nameDataBase.root, &outputPerson, false);
			//update InputData.txt with new data
			break;
		case 4://Remove a person from the database
			std::cout << "What is the name of the person you would like to REMOVE from the database ?" << std::endl;
			name = menu.takeStringInput();
			found = nameDataBase.searchByName(name);
			if (found == nullptr)
			{
				std::cout << name << " was not found in the database." << std::endl;
			}
			else
			{
				std::cout << found->getName() << " was found with birthday " << found->getBirthday() << "." << std::endl;
				nameDataBase.remove(found);

				outputPerson.open("InputData.txt");//deletes previous data
												   //now the database will be inorder traversed to add modified into back into the file
				displayPreOrder(nameDataBase.root, &outputPerson, false);
				outputPerson.close();

				std::cout << "They have been removed from the database" << std::endl;
			}
			pause();
			break;
		case 5:
			//WRITE OUT EVERYONE IN PREORDER (NODE-LEFT-RIGHT)
			//AND POST-ORDER (LEFT-RIGHT-NODE)
			//FROM THE NAME DATABASE INTO  NamesOutput.txt
			namesFile.open("NamesOutput.txt");
			std::cout << "Now to show a PREORDER traversal of the name based binary search tree" << std::endl;
			rootNode = nameDataBase.root;
			displayPreOrder(rootNode, &namesFile, true);
			namesFile.close();
			pause();
			break;
		case 6:
			namesFile.open("NamesOutput.txt");
			std::cout << "Now to show a POSTORDER traversal of the name based binary search tree" << std::endl;
			rootNode = nameDataBase.root;
			displayPostOrder(rootNode, &namesFile, true);
			namesFile.close();
			pause();
			break;
		case 7:
			birthdaysFile.open("BirthdaysOutput.txt");
			std::cout << "Now to show an INORDER traversal of the birthday based binary search tree" << std::endl;
			rootNode = birthdayDataBase.root;
			displayInOrder(rootNode, &birthdaysFile, true);
			birthdaysFile.close();
			pause();
			//WRITE OUT EVERYONE INORDER (LEFT-NODE-RIGHT)
			//breadth-first
			break;
		default:
			break;
		}
	}
	

	//output file contains names and birthdays on a single line separated by tabs
	//EACH SECTION IDENTIFIED BY A HEADER (NOT THOSE HEADERS YOU BAFOON)
	nameDataBase.~PersonBST();
	birthdayDataBase.~PersonBST();

	return 0;
}

void pause()
{
	std::cout << std::endl << "Press any key to go back to the menu...";
	std::cin.get();
	system("CLS");
}

void displayPreOrder(BinaryNode<Person> *rootNode, std::ofstream *outfile, bool isOnSameLine)
{
	// Preorder: NODE-LEFT-RIGHT
	BinaryNode<Person> *leftNode = rootNode->getLeftChild();
	BinaryNode<Person> *rightNode = rootNode->getRightChild();
	char NBseperator = '\n';
	if (isOnSameLine)
		NBseperator = '\t';
	
	writeOutput(outfile, rootNode->getData()->getName());
	writeOutput(outfile, NBseperator);
	writeOutput(outfile, rootNode->getData()->getBirthday());

	if (leftNode != nullptr)
	{
		writeOutput(outfile, '\n');
		displayPreOrder(leftNode, outfile, isOnSameLine);
	}
	if (rightNode != nullptr)
	{
		writeOutput(outfile, '\n');
		displayPreOrder(rightNode, outfile, isOnSameLine);
	}
}

void displayInOrder(BinaryNode<Person> *rootNode, std::ofstream *outfile, bool isOnSameLine)
{
	// Inorder: LEFT-NODE-RIGHT
	BinaryNode<Person> *leftNode = rootNode->getLeftChild();
	BinaryNode<Person> *rightNode = rootNode->getRightChild();
	char NBseperator = '\n';
	if (isOnSameLine)
		NBseperator = '\t';

	if (leftNode != nullptr)
	{
		writeOutput(outfile, '\n');
		displayPreOrder(leftNode, outfile, isOnSameLine);
	}

	writeOutput(outfile, rootNode->getData()->getName());
	writeOutput(outfile, NBseperator);
	writeOutput(outfile, rootNode->getData()->getBirthday());

	if (rightNode != nullptr)
	{
		writeOutput(outfile, '\n');
		displayPreOrder(rightNode, outfile, isOnSameLine);
	}
}

void displayPostOrder(BinaryNode<Person> *rootNode, std::ofstream *outfile, bool isOnSameLine)
{
	// Postorder: LEFT-RIGHT-NODE
	BinaryNode<Person> *leftNode = rootNode->getLeftChild();
	BinaryNode<Person> *rightNode = rootNode->getRightChild();
	char NBseperator = '\n';
	if (isOnSameLine)
		NBseperator = '\t';

	if (leftNode != nullptr)
	{
		writeOutput(outfile, '\n');
		displayPreOrder(leftNode, outfile, isOnSameLine);
	}
	if (rightNode != nullptr)
	{
		writeOutput(outfile, '\n');
		displayPreOrder(rightNode, outfile, isOnSameLine);
	}

	writeOutput(outfile, rootNode->getData()->getName());
	writeOutput(outfile, NBseperator);
	writeOutput(outfile, rootNode->getData()->getBirthday());
}


template <class ObjectType>
void writeOutput(std::ofstream *outfile, ObjectType output)
{
	std::cout << output;
	*outfile << output;
}