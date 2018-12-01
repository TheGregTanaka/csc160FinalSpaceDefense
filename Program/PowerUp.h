#pragma once
#include "Equipment.h"

enum affectedStat
{
	HP,
	STR,
	DEF,
	SPD,
	IQ,
	ACC
};

// PowerUps represent one time use items that will permanantly change a stat, like MedKits and Steroids
class PowerUp :
	public Equipment
{
public:
	affectedStat which;
	PowerUp(int);
	PowerUp(PowerUp*);
	PowerUp(Equipment*);
	~PowerUp();
	void use(int*) override;
	equipmentType eType() override;
};
