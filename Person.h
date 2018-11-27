#pragma once
#include <string>
#include "Birthday.h"

class Person {
private:
	std::string fullName;
	Birthday birthday;
public:
	Person();
	Person(std::string name, Birthday add);
	~Person() {}
	std::string getName() { return fullName; }
	Birthday getBirthday() { return birthday; }
	void setName(std::string in) { fullName = in; }
	void setBirthday(Birthday in) { birthday = in; }
};