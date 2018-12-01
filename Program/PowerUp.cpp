#include "PowerUp.h"


PowerUp::PowerUp(int i)
{
	bonus = i;
}

PowerUp::PowerUp(PowerUp *e)
{
	which = e->which;
	name = e->getName();
	cost = e->getCost();
	description = e->getDescription();
	bonus = e->getBonus();
}

//DELETE THIS
PowerUp::PowerUp(Equipment *e)
{
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

equipmentType PowerUp::eType()
{
	return PowerUpType;
}
