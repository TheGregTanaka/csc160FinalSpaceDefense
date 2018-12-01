#pragma once
#include "Equipment.h"
class Weapon :
	public Equipment
{
private:
	
public:
	Weapon(Equipment*);
	Weapon(int);
	~Weapon();
	void use(int*) override;
	equipmentType type() override;
	//void armYourself(Character*);
};

