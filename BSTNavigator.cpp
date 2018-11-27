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

void updateOutputFiles(std::ofstream *namesFile, BinaryNode<Person> *nRootNode, std::ofstream *birthdaysFile, BinaryNode<Person> *bRootNode);

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
	std::string birthdayStr = "birthdays";
	Birthday birthday;
	while (inputFile)
	{
		if (inputFile.eof()) break;
		getline(inputFile, name, '\n');
		getline(inputFile, birthdayStr, '\n');
		Person *newNamePerson = new Person(name, birthday.stoBirthday(birthdayStr));
		Person *newBirthdayPerson = new Person(name, birthday.stoBirthday(birthdayStr));
		
		nameDataBase.addByName(newNamePerson);
		birthdayDataBase.addByBirthday(newBirthdayPerson);
	}
	inputFile.close();

	//USER INTERACTION WITH DATABASE
	int mainLength = 7;
	std::string options[] =
	{
		"Enter a new person", // option 1
		"Search for a person in database",// option 2
		"Modify a persons data",// option 3
		"Remove a person from the database",// option 4
		"Display database in name-based sequence",// option 5
		"Display database in birthday-based sequence",// option 6
		"Exit program"// option 7
	};
	Menu menu = Menu(options, mainLength);
	
	int orderLength = 4;
	std::string BSTorderOptions[] =
	{
		"Display in preorder",
		"Display in inorder",
		"Display in postorder",
		"Return to main menu"
	};
	Menu BSTorderMenu = Menu(BSTorderOptions, orderLength);
	std::ofstream outputPerson;
	int option = 0;
	std::string inputStr;
	int inputInt;
	Person *newNamePerson = nullptr, *newBirthdayPerson = nullptr, *found = nullptr;
	BinaryNode<Person> *rootNode;
	bool willPause;
	while (option != mainLength)
	{
		option = menu.printOptionsList();
		switch (option)
		{
		case 1://enter new person to database
			outputPerson.open("InputData.txt", std::fstream::app);
			std::cout << "Enter the new persons name:" << std::endl;
			name = menu.takeStringInput();
			birthdayStr = "";
			std::cout << "Enter the new persons birthday year (1900-2018):" << std::endl;
			inputInt = menu.takeRangedIntInput(1900, 2018);
			birthdayStr += std::to_string(inputInt) + "-";
			std::cout << "Enter the new persons birthday month (1-12):" << std::endl;
			inputInt = menu.takeRangedIntInput(1, 12);
			if (inputInt < 10)
				birthdayStr += '0';
			birthdayStr += std::to_string(inputInt) + "-";
			std::cout << "Enter the new persons birthday date (1-31):" << std::endl;
			inputInt = menu.takeRangedIntInput(1, 31);
			if (inputInt < 10)
				birthdayStr += '0';
			birthdayStr += std::to_string(inputInt);

			newNamePerson = new Person(name, birthday.stoBirthday(birthdayStr));
			newBirthdayPerson = new Person(name, birthday.stoBirthday(birthdayStr));

			nameDataBase.addByName(newNamePerson);
			birthdayDataBase.addByBirthday(newBirthdayPerson);

			outputPerson << std::endl << name << std::endl << birthdayStr;
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
				std::cout << found->getName() << " was found with birthday " << found->getBirthday().to_string() << " ." << std::endl;
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
				std::cout << found->getName() << " was found with birthday " << found->getBirthday().to_string() << " ." << std::endl;
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
					birthdayDataBase.searchByBirthday(found->getBirthday())->setName(inputStr);
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
					birthdayStr = "";
					std::cout << "Enter the new persons birthday year (1900-2018):" << std::endl;
					inputInt = menu.takeRangedIntInput(1900, 2018);
					birthdayStr += std::to_string(inputInt) + "-";
					std::cout << "Enter the new persons birthday month (1-12):" << std::endl;
					inputInt = menu.takeRangedIntInput(1, 12);
					if (inputInt < 10)
						birthdayStr += '0';
					birthdayStr += std::to_string(inputInt) + "-";
					std::cout << "Enter the new persons birthday date (1-31):" << std::endl;
					inputInt = menu.takeRangedIntInput(1, 31);
					if (inputInt < 10)
						birthdayStr += '0';
					birthdayStr += std::to_string(inputInt);
					birthdayDataBase.searchByBirthday(found->getBirthday())->setBirthday(birthday.stoBirthday(birthdayStr));
					found->setBirthday(birthday.stoBirthday(birthdayStr));
					inputStr = "n";
				}
			}
			
			outputPerson.open("InputData.txt");//deletes previous data
			//now the database will be inorder traversed to add modified into back into the file
			displayPreOrder(nameDataBase.root, &outputPerson, false);
			//update InputData.txt with new data
			outputPerson.close();
			system("CLS");
			
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
				std::cout << found->getName() << " was found with birthday " << found->getBirthday().to_string() << "." << std::endl;
				nameDataBase.remove(found);

				outputPerson.open("InputData.txt");//deletes previous data
												   //now the database will be inorder traversed to add modified into back into the file
				displayPreOrder(nameDataBase.root, &outputPerson, false);
				outputPerson.close();

				std::cout << "They have been removed from the database" << std::endl;
			}
			pause();
			break;
		case 5://Display database in name-based sequence
			std::cout << "The name-based database will be displayed" << std::endl;
			inputInt = BSTorderMenu.printOptionsList();
			willPause = true;
			switch (inputInt)
			{
			case 1:
				std::cout << "Now to show a PREORDER traversal of the name based binary search tree" << std::endl;
				rootNode = nameDataBase.root;
				displayPreOrder(rootNode, nullptr, true);
				break;
			case 2:
				std::cout << "Now to show a INORDER traversal of the name based binary search tree" << std::endl;
				rootNode = nameDataBase.root;
				displayInOrder(rootNode, nullptr, true);
				break;
			case 3:
				std::cout << "Now to show a POSTORDER traversal of the name based binary search tree" << std::endl;
				rootNode = nameDataBase.root;
				displayPostOrder(rootNode, nullptr, true);
				break;
			case 4:
				willPause = false;
			default:
				break;
			}
			if(willPause)
				pause();
			break;
		case 6://Display database in birthday-based sequence
			std::cout << "The birthday-based database will be displayed" << std::endl;
			inputInt = BSTorderMenu.printOptionsList();
			willPause = true;
			switch (inputInt)
			{
			case 1:
				std::cout << "Now to show a PREORDER traversal of the birthday based binary search tree" << std::endl;
				rootNode = birthdayDataBase.root;
				displayPreOrder(rootNode, nullptr, true);
				break;
			case 2:
				std::cout << "Now to show a INORDER traversal of the birthday based binary search tree" << std::endl;
				rootNode = birthdayDataBase.root;
				displayInOrder(rootNode, nullptr, true);
				break;
			case 3:
				std::cout << "Now to show a POSTORDER traversal of the birthday based binary search tree" << std::endl;
				rootNode = birthdayDataBase.root;
				displayPostOrder(rootNode, nullptr, true);
				break;
			case 4:
				willPause = false;
			default:
				break;
			}
			if (willPause)
				pause();
			break;
		default:
			break;
		}
		updateOutputFiles(&namesFile, nameDataBase.root, &birthdaysFile, birthdayDataBase.root);
	}

	nameDataBase.~PersonBST();
	birthdayDataBase.~PersonBST();

	return 0;
}

void updateOutputFiles(std::ofstream *namesFile, BinaryNode<Person> *nRootNode, std::ofstream *birthdaysFile, BinaryNode<Person> *bRootNode)
{
	//AFTER THE USER INTERACTION IS COMPLETE THE TWO DATABASES ARE USED
	//TO WRITE TO NamesOutput.txt AND BirthdaysOutput.txt
	//OUTPUT FILE CONTAIN NAMES AND BIRTHDAYS ON A SINGLE LINE SEPERATED BY TABS
	//EACH SECTION IDENTIFIED BY A HEADER
	namesFile->open("NamesOutput.txt");
	writeOutput(namesFile, "Preorder List of People by Names BST\n");
	displayPreOrder(nRootNode, namesFile, true);
	writeOutput(namesFile, "\nPostorder List of People by Names BST\n");
	displayPostOrder(nRootNode, namesFile, true);
	namesFile->close();
	birthdaysFile->open("BirthdaysOutput.txt");
	writeOutput(birthdaysFile, "Inorder List of People by Birthdays BST\n");
	displayInOrder(bRootNode, birthdaysFile, true);
	birthdaysFile->close();
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
	writeOutput(outfile, rootNode->getData()->getBirthday().to_string());

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
		displayInOrder(leftNode, outfile, isOnSameLine);
		writeOutput(outfile, '\n');
	}

	writeOutput(outfile, rootNode->getData()->getName());
	writeOutput(outfile, NBseperator);
	writeOutput(outfile, rootNode->getData()->getBirthday().to_string());

	if (rightNode != nullptr)
	{
		writeOutput(outfile, '\n');
		displayInOrder(rightNode, outfile, isOnSameLine);
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
		displayPostOrder(leftNode, outfile, isOnSameLine);
		writeOutput(outfile, '\n');
	}
	if (rightNode != nullptr)
	{
		
		displayPostOrder(rightNode, outfile, isOnSameLine);
		writeOutput(outfile, '\n');
	}

	writeOutput(outfile, rootNode->getData()->getName());
	writeOutput(outfile, NBseperator);
	writeOutput(outfile, rootNode->getData()->getBirthday().to_string());
}

template <class ObjectType>
void writeOutput(std::ofstream *outfile, ObjectType output)
{
	if(outfile != nullptr)
		*outfile << output;
	else//outfile is nullptr
		std::cout << output;
}