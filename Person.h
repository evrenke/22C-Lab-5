#pragma once
#include <string>
class Person {
private:
	std::string firstName, lastName, birthday;
public:
	Person();
	Person(std::string first, std::string last, std::string add);
	~Person() {}
	std::string getName() { return firstName + " " + lastName; }
	std::string getBirthday() { return birthday; }
	void setFirstName(std::string in) { firstName = in; }
	void setLastName(std::string in) { lastName = in; }
	void setBirthday(std::string in) { birthday = in; }
};