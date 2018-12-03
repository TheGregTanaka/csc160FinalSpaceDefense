#include "EmptySlot.h"



EmptySlot::EmptySlot()
{
	name = "Empty Slot";
	description = "There is no item in this slot";
	bonus = 0;
}


EmptySlot::~EmptySlot()
{
}

void EmptySlot::use(int *)
{// do nothing - must be defined so this class is not virtual
}

equipmentType EmptySlot::eType()
{
	return EmptyType;
}

affectedStat EmptySlot::getWhich()
{
	throw std::runtime_error("Calling getWhich() on EmptySlot!");
}
