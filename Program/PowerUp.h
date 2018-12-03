#pragma once
#include "Equipment.h"

// PowerUps represent one time use items that will permanantly change a stat, like MedKits and Steroids
class PowerUp :
	public Equipment
{
public:
	affectedStat which;
	PowerUp(string, double, string, int, affectedStat);
	PowerUp(PowerUp*);
	PowerUp(Equipment*);
	~PowerUp();
	void use(int*) override;
	equipmentType eType() override;
	affectedStat getWhich() { return which; };
	void setWhich(affectedStat w) { which = w; };
};
