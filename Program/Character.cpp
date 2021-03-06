#pragma once
#include "Character.h"

/**
 * Constructor that takes an arguments for everything but the inventory
 * Using the initializer syntax demonstrated by Kate Gregory in pluralsight 5 - user defined types
 */
Character::Character(CharacterType r, string charName, int lvl, CombatStats charStats,
	double m, int ew, int ea) :
	role(r), name(charName), level(lvl), stats(charStats), money(m), 
	inventory(new Equipment*[STARTING_INV_SIZE]), equipedWeapon(ew), equipedArmor(ea)
{
	for (int i = 0; i < STARTING_INV_SIZE; ++i)
	{
		inventory[i] = new EmptySlot();
	}
}

/**
 * Constructor that takes an existing combat stats argument, along with money
 * and inventory, intended to allow for loading an existing character, however loading
 * the inventory was never implemented
 * Using the initializer syntax demonstrated by Kate Gregory in pluralsight 5 - user defined types
 */
Character::Character(CharacterType r, string charName, int lvl, CombatStats charStats, double m, int ew, int ea, int invSize, Equipment **e) :
	role(r), name(charName), level(lvl), stats(charStats), money(m), equipedWeapon(ew), equipedArmor(ea)
{
	inventory = new Equipment*[invSize];
	for (int i = 0; i < invSize; ++i)
	{
		inventory[i] = e[i];
	}
}
/*
 * Destructor removes inventory
 */
Character::~Character()
{
	delete[] this->inventory;
}

//this is a fake getter - I didn't want to return the memory location of a private
// member allowing it to be incorrectly manipulated, and there wasn't much value
// to creating a deep copy for what I needed. This string is mainly used for saving
// returns space delimited string starting with the inventory size - this will be
// useful if the inventory becomes resizable
string Character::getInventoryString()
{
	int size = STARTING_INV_SIZE; // if the inventory becomes resizable fix this
	string itemString = std::to_string(size) + " ";
	for (int i = 0; i < STARTING_INV_SIZE; ++i)
	{
		itemString += inventory[i]->getName() + " ";
	}

	return itemString;
}

// public methods
/**
 * Used to make purchases from the commisary. Handles the spedning of money,
 * and adds items to inventory.
 */
void Character::purchase(Equipment *e)
{
	double itemCost = e->getCost();
	// Check that the player has enough money for the purchase - if not stop
	if (itemCost > money)
	{
		std::cout << "Bob : You don't have enough money to buy that!\n";
		std::cout << "Item cost: " << itemCost << " Current money: " << money << std::endl;
		return;
	}
	// Check if there is room in the inventory - if not, stop
	bool found = false;
	int foundAt;
	for (int i = 0; i < STARTING_INV_SIZE; ++i)
	{
		if (inventory[i]->eType() == EmptyType)
		{
			found = true;
			foundAt = i;
			break;
		}
	}
	if (!found)
	{
		std::cout << "Your inventory is full and you cannot carry any more items!\n";
		return;
	}
	// Subtact the cost of the item from the character's money
	money -= itemCost;
	// add the item to the inventory at the first EmptySlot
	delete inventory[foundAt];
	inventory[foundAt] = e;
	std::cout << "You successfully purchased " << e->getName() << "!\n";
}

void Character::useItem(Equipment *e, int i)
{
	string itemName = e->getName();
	switch (e->eType())
	{
	case WeaponType:
		equipedWeapon = i;
		break;
	case ArmorType:
		equipedArmor = i;
		break;
	case PowerUpType: //TODO make this better
		std::runtime_error("PowerUp sent to wrong function!");
		break;
	case EmptyType:
		std::runtime_error("Cannot use EmptySlot!");
		break;
	}
}

void Character::useItem(PowerUp *p, int invPos)
{
	int effect = 0;
	p->use(&effect);
	affectedStat efStat = p->getWhich();
	switch (efStat)
	{
	case HP:
		stats.health += effect;
		break;
	case STR:
		stats.strength += effect;
		break;
	case DEF:
		stats.defense += effect;
		break;
	case SPD:
		stats.speed += effect;
		break;
	case IQ:
		stats.intellect += effect;
		break;
	case ACC:
		stats.accuracy += effect;
		break;
	}
	// remove powerup from inventory
	delete p;
	inventory[invPos] = new EmptySlot();
}

void Character::receiveMoney(double m)
{
	money += m;
}

//acts like a setter that sets weapon to the none-equiped value
void Character::removeWeapon()
{
	equipedWeapon = -1;
}
//acts like a setter that sets armor to the none-equiped value
void Character::removeArmor()
{
	equipedArmor = -1;
}

void Character::levelUp()
{
	int points;
	// lower level players improve stats faster
	if (level <= 5)
		points = 4;
	else
		points = 2;
	increaseStats(points);
	++level;
}

void Character::displayStats()
{
	std::cout << "1: Strength : " << getStrength() << std::endl;
	std::cout << "2: Defense  : " << getDefense() << std::endl;
	std::cout << "3:  Speed   : " << getSpeed() << std::endl;
	std::cout << "4: Intellect: " << getIntellect() << std::endl;
	std::cout << "5: Accuracy : " << getAccuracy() << std::endl;
}

//TODO finish this
// displays the character's info and allows inventory management
void Character::displayCharSheet()
{
	int selection;
	bool loop = true;
	string charRole;
	switch (role)
	{
	case BigGun:
		charRole = "Big Gun";
		break;
	case Engineer:
		charRole = "Engineer";
		break;
	case Sniper:
		charRole = "Sniper";
		break;
	}

	while (loop)
	{
		system("cls"); // clears the screen
		std::cout << std::setw(10) << std::left << getName() << "lvl: " << std::setw(4) << getLevel() << std::endl;
		std::cout << charRole << std::endl;
		std::cout << std::endl;
		std::cout << "Money: " << getMoney() << std::endl;
		//string armor = (equipedArmor >= 0) ? inventory[equipedArmor]->getName() : "No Armor Equiped"; //receiving strange out-of-bounds behavior
		string armor = "No Armor Equiped";
		if (equipedArmor >= 0)
		{
			armor = inventory[equipedArmor]->getName();
		}
		std::cout << armor << std::endl;
		//string weapon = (equipedWeapon >= 0) ? inventory[equipedWeapon]->getName() : "No Weapon Equiped"; receiving strange out-of-bounds behavior
		string weapon = "No Weapon Equiped";
		if (equipedWeapon >= 0)
		{
			weapon = inventory[equipedWeapon]->getName();
		}
		std::cout << weapon << std::endl;
		displayStats();
		// show inventory
		std::cout << std::endl;
		std::cout << "Inventory\n";
		// TODO: if inventory is allowed to be expanded, ensure this reflects the current size, not starting size
		string item = "";
		for (int i = 0; i < STARTING_INV_SIZE; ++i)
		{
			item = inventory[i]->getName();
			std::cout << i + 1 << ": " << item << std::endl;
		}
		// allow items from inventory to be used
		std::cout << "Select an item to investigate or use. Enter 0 to return to the main menu: ";
		//TODO - validate this
		std::cin >> selection;
		if (selection == 0)
		{
			//end loop
			loop = false;
		}
		else
		{
			// because 1 was added to the index in the display, decrement the user's selection to be the correct index
			--selection;
			// check what the player wants to do with the item
			int select;
			if (inventory[selection]->eType() == EmptyType)
			{
				std::cout << "There's no item to use!\n";
				system("pause");
			}
			else
			{
				std::cout << "Enter 1 to Examine, 2 to Use/Equip, 3 to Discard, or 4 to go back: ";
				// TODO validate
				std::cin >> select;
				switch (select)
				{
				case 1:
				{	// creating a code block for this case allows variables to be declared in this scope
					string itemName = inventory[selection]->getName();
					string itemDescrip = inventory[selection]->getDescription();
					int itemBonus = inventory[selection]->getBonus();
					std::cout << itemName << std::endl;
					std::cout << itemDescrip << " Bonus: " << itemBonus;
					std::cout << std::endl;
					system("pause");
					break;
				}
				case 2:
					if (inventory[selection]->eType() == PowerUpType)
					{
						affectedStat effect = inventory[selection]->getWhich();
						PowerUp *p = new PowerUp(inventory[selection]);
						p->setWhich(effect);
						useItem(p, selection);
					}
					else
					{
						useItem(inventory[selection], selection);
					}
					break;
				case 3:
					//discard item
					// deletes the existing pointer
					delete inventory[selection];
					// dynamically create a new empty slot here to prevent bad pointer exceptions
					// and display nicely
					inventory[selection] = new EmptySlot();
					break;
				case 4:
					break;
				}
			}
		}
	}
}

Character& Character::operator++()
{
	this->levelUp();
	return *this;
}

Character Character::operator++(int)
{
	Character c(*this);
	operator++();
	return c;
}

/**
 * Determines the power of an attack. This power is used both to determine if
 * the attack successfully landed, as well as calculate damge. Or it would have
 * been used for that if battlw was implemented
 * The idea was the game would randomly choose an attack type based on different
 * character stats, but each character would favore a particular stat
 */
int Character::attack()
{
	// declare vars
	int power = 0;
	// RNG in range 1-100
	int randNum = (rand() % 100) + 1;
	/*8% chance of special attack, after that, each role should have twice the
	  chance of using their favored attack than the other two. To handle this,
	  I've divided the remaining 92% by 4, to give one 'section' of probability
	  to each attack type, and a switch statement in one column that will add a
	  second section of probability for the favored attack type*/
	if (randNum > 92)
	{
		power = specialAttack();
	}
	else if (randNum > 69)
	{
		power = strongAttack();
	}
	else if (randNum > 46)
	{
		power = cleverAttack();
	}
	else if (randNum > 23)
	{
		power = accurateAttack();
	}
	else
	{
		switch (role)
		{
		case BigGun:
			power = strongAttack();
			break;
		case Engineer:
			power = cleverAttack();
			break;
		case Sniper:
			power = accurateAttack();
			break;
		}
	}
	return power;
}

/**
 * Used when attacked to determine if the attack landed and the character should
 * take damage. Not implemented
 */
bool Character::defend()
{
	return false;
}


// private methods
/*
 * Purpose Allows a player to increase certain combat stat scores with a provided number of points
 * @param spendablePoints The number of times the player can increment a stat by 1
 */
void Character::increaseStats(int spendablePoints)
{
	int selection;
	while (spendablePoints > 0)
	{
		std::cout << "You have " << spendablePoints << " to spend. Your current stats are:\n";
		this->displayStats();

		// TODO: Validate - is there a way to use makeSelection here? Maybe a static utility class?
		std::cin >> selection;
		switch (selection)
		{
		case 1:
			++(stats.strength);
			break;
		case 2:
			++(stats.defense);
			break;
		case 3:
			++(stats.speed);
			break;
		case 4:
			++(stats.intellect);
			break;
		case 5:
			++(stats.accuracy);
			break;
		}
		--spendablePoints;
	}
}


	//All the following methods relate to combat and were not implemented
/**
 * An attack which is more powerful for accurate characters
 */
int Character::accurateAttack()
{
	return 0;
}

/**
 * An attack which is more powerful for strong characters
 */
int Character::strongAttack()
{
	return 0;
}

/**
 * An attack which is more powerful for intelligent characters
 */
int Character::cleverAttack()
{
	return 0;
}

int Character::specialAttack()
{
	return 0;
}

bool Character::takeDamage(int)
{
	return false;
}