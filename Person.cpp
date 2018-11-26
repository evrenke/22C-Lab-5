#include "Person.h"
Person::Person() {
	fullName = "";
	birthday = "";
}
Person::Person(std::string name, std::string add) {
	fullName = name;
	birthday = add;
}