#pragma once
#include "Weapon.h"


Weapon::Weapon(Equipment *e)
{
	if (e->eType() != WeaponType)
	{
		// throw an exception of some sort
		exit(99);
	}
	name = e->getName();
	cost = e->getCost();
	description = e->getDescription();
	bonus = e->getBonus();
}

Weapon::Weapon(string n, double c, string d, int b) : Equipment(n, c, d, b)
{
}

Weapon::~Weapon()
{
}

void Weapon::use(int *i)
{
	// using a weapon increases the strength stat
	*i += bonus;
}

equipmentType Weapon::eType()
{
	return WeaponType;
}

affectedStat Weapon::getWhich()
{
	return STR;
}

/*void use(Character *c)
{
	// raises character's `strength` stat
	int oldStr = c->getStrength();
	c->setStrength(oldStr + 1);
}*/

/*void Weapon::armYourself(Character *c)
{
	
}*/