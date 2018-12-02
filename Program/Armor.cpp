#include "Armor.h"



Armor::Armor(string n, double c, string d, int b) : Equipment(n, c, d, b)
{
}


Armor::Armor(Equipment *e)
{
	if (e->eType() != ArmorType)
	{
		// throw an exception of some sort
		exit(99);
	}
	name = e->getName();
	cost = e->getCost();
	description = e->getDescription();
	bonus = e->getBonus();
}


Armor::~Armor()
{
}

void Armor::use(int *i)
{
	*i += getBonus();
}

equipmentType Armor::eType()
{
	return ArmorType;
}
