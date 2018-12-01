#pragma once
#include "Equipment.h"

// PowerUps represent one time use items that will permanantly change a stat, like MedKits and Steroids
class PowerUp :
	public Equipment
{
public:
	PowerUp(int);
	PowerUp(Equipment*);
	~PowerUp();
	void use(int*) override;
	equipmentType type() override;
};

