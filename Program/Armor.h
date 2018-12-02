#pragma once
#include "Equipment.h"
class Armor :
	public Equipment
{
private:
public:
	Armor(string, double, string, int);
	Armor(Equipment*);
	~Armor();
	void use(int*) override;
	equipmentType eType() override;
};

