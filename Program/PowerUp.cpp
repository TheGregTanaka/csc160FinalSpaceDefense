#include "PowerUp.h"


PowerUp::PowerUp(string n, double c, string d, int b, affectedStat w) : Equipment(n, c, d, b), which(w)
{
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

void PowerUp::use(int *i)
{
	*i += bonus;
}

equipmentType PowerUp::eType()
{
	return PowerUpType;
}
