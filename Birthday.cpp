#include "Birthday.h"

bool Birthday::operator>(const Birthday &other) const
{
	return (year > other.year) || (year == other.year && month > other.month)
		|| (year == other.year && month == other.month && day > other.day);
}
bool Birthday::operator>=(const Birthday  &other) const
{
	return (year >= other.year) || (year == other.year && month >= other.month)
		|| (year == other.year && month == other.month && day >= other.day);
}
bool Birthday::operator==(const Birthday  &other) const
{
	return (year == other.year && month == other.month && day == other.day);
}
bool Birthday::operator<=(const Birthday  &other) const
{
	return (year <= other.year) || (year == other.year && month <= other.month)
		|| (year == other.year && month == other.month && day <= other.day);
}
bool Birthday::operator< (const Birthday  &other) const
{
	return (year < other.year) || (year == other.year && month < other.month)
		|| (year == other.year && month == other.month && day < other.day);
}

Birthday Birthday::stoBirthday(std::string date)
{
	// using format: yyyy-mm-dd
	Birthday birthday;
	birthday.year = std::stoi(date.substr(0, date.find('-')));
	date = date.substr(date.find('-') + 1, date.length());
	birthday.month = std::stoi(date.substr(0, date.find('-')));
	date = date.substr(date.find('-') + 1, date.length());
	birthday.day = std::stoi(date);
	return birthday;
}

std::string Birthday::to_string()
{
	// using format: yyyy-mm-dd
	std::string result = "";
	result += std::to_string(year);
	result += '-';
	if (month < 10)
		result += '0';
	result += std::to_string(month);
	result += '-';
	if (day < 10)
		result += '0';
	result += std::to_string(day);
	return result;
}