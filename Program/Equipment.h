#pragma once
#include <string>
#include <iostream>

using std::string;

class Equipment
{
protected:
	string name;
	double cost;
	string description;
	int bonus;
public:
	Equipment();
	~Equipment();
	virtual void use(int*) = 0;
	virtual equipmentType type() = 0;
	string getName() { return name; };
	double getCost() { return cost; };
	string getDescription() { return description; };
	int getBonus() { return bonus; };
};

enum equipmentType 
{
	WeaponType,
	ArmorType,
	PowerUpType
};