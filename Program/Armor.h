#pragma once
#include "Equipment.h"
class Armor :
	public Equipment
{
private:
public:
	Armor(int);
	Armor(Equipment*);
	~Armor();
	void use(int*) override;
	equipmentType eType() override;
};

