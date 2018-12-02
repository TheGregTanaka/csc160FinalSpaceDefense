#pragma once
#include <string>
#include <iostream>

using std::string;

enum equipmentType
{
	WeaponType,
	ArmorType,
	PowerUpType,
	EmptyType
};

class Equipment
{
protected:
	string name;
	double cost;
	string description;
	int bonus;
public:
	Equipment();
	Equipment(string n, double c, string d, int b) : name(n), cost(c), description(d), bonus(b) {};
	~Equipment();
	virtual void use(int*) = 0;
	virtual equipmentType eType() = 0;
	string getName() { return name; };
	double getCost() { return cost; };
	string getDescription() { return description; };
	int getBonus() { return bonus; };
};
