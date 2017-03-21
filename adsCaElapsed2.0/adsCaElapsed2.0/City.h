#ifndef CITY_H
#define CITY_H
#include <iostream>
#include <map>
#include <string>
using namespace std;

class City {
public:
	string getName();
	double getLong();
	double getLat();
	City();
	City(string, double, double);
	friend ostream& operator<<(ostream& os, const City &c1);
	bool operator<(const City & c1)const;
	bool operator>(const City & c1)const;
private:
	pair<double, double> GPS; //pair of x/y co-ords
	string name;
};
#endif