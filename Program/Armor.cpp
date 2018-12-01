#include "Armor.h"



Armor::Armor(int i)
{
	bonus = i;
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
