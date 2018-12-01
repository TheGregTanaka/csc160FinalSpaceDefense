#pragma once
#include "Equipment.h"
class EmptySlot :
	public Equipment
{
public:
	EmptySlot();
	~EmptySlot();
	void use(int*) override;
	equipmentType eType() override;
};

