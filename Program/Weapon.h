#pragma once
#include "Equipment.h"
class Weapon :
	public Equipment
{
private:
	
public:
	Weapon(Equipment*);
	Weapon(string, double, string, int);
	~Weapon();
	void use(int*) override;
	equipmentType eType() override;
	//void armYourself(Character*);
};

