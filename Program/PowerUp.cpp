#include "PowerUp.h"



PowerUp::PowerUp(int i)
{
	bonus = i;
}

PowerUp::PowerUp(Equipment *e)
{
	if (e->type() != ArmorType)
	{
		// throw an exception of some sort
		exit(99);
	}
	name = e->getName();
	cost = e->getCost();
	description = e->getDescription();
	bonus = e->getBonus();
}


PowerUp::~PowerUp()
{
}

void PowerUp::use(int *)
{
}

equipmentType PowerUp::type()
{
	return PowerUpType;
}
