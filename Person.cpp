#include "Person.h"
Person::Person() {
	firstName = "";
	lastName = "";
	birthday = "";
}
Person::Person(std::string first, std::string last, std::string add) {
	firstName = first;
	lastName = last;
	birthday = add;
}