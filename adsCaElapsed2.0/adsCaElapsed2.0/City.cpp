#include <iostream>
#include <map>
#include <string>
#include "City.h"
using namespace std;

City::City()
{
	name = "";
	GPS.first = 0;
	GPS.second = 0;
}

City::City(string n, double lat, double lon)
{
	name = n;
	GPS.first = lon;
	GPS.second = lat;
}

string City::getName()
{
	return name;
}

double City::getLong()
{
	return GPS.first;
}

double City::getLat()
{
	return GPS.second;
}

ostream& operator<<(ostream& os, const City &c1) //overload output to allow city obj to print out
{
	os << "city: " << c1.name << endl; //outputs name
	os << "longitude: " << c1.GPS.first << endl; //outputs longitude
	os << "latitude: " << c1.GPS.second << endl; //outputs latitude
	
	return os;
}

bool City::operator<(const City &c1)const
{

	if (this->name.compare(c1.name) < 0)
	{
		return true;
	}
	return false;
}
bool City::operator>(const City &c1)const
{

	if (this->name.compare(c1.name) > 0)
	{
		return true;
	}
	return false;
}