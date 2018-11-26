#pragma once
#include <string>
class Person {
private:
	std::string fullName, birthday;
public:
	Person();
	Person(std::string name, std::string add);
	~Person() {}
	std::string getName() { return fullName; }
	std::string getBirthday() { return birthday; }
	void setName(std::string in) { fullName = in; }
	void setBirthday(std::string in) { birthday = in; }
};