#include "Person.h"
Person::Person() {
	fullName = "";
	birthday.day = 1;
	birthday.month = 1;
	birthday.year = 1900;
}
Person::Person(std::string name, Birthday add) {
	fullName = name;
	birthday = add;
}