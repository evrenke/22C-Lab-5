#pragma once
#include <string>
struct Birthday
{
	int day;
	int month;
	int year;
	bool operator> (const Birthday  &) const;
	bool operator>=(const Birthday &) const;
	bool operator==(const Birthday  &) const;
	bool operator<=(const Birthday  &) const;
	bool operator< (const Birthday  &) const;
	Birthday stoBirthday(std::string);
	std::string to_string(); // (format: yyyy - mm - dd)
};