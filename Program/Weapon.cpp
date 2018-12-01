#pragma once
#include "Weapon.h"


Weapon::Weapon(Equipment *e)
{
	if (e->type() != WeaponType)
	{
		// throw an exception of some sort
		exit(99);
	}
	name = e->getName();
	cost = e->getCost();
	description = e->getDescription();
	bonus = e->getBonus();
}

Weapon::Weapon(int i)
{
	bonus = i;
}

Weapon::~Weapon()
{
}

void Weapon::use(int *i)
{
	// using a weapon increases the strength stat
	*i += attackBonus;
}

equipmentType Weapon::type()
{
	return WeaponType;
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