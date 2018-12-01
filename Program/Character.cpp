#pragma once
#include "Character.h"

/** 
 * Constructor to be used for a new character. Level is set to 0 and Money is the default starting value
 * Using the initializer syntax demonstrated by Kate Gregory in pluralsight 5 - user defined type
 */
Character::Character(CharacterType r, string charName, CombatStats charStats) :
	role(r), name(charName), level(0), stats(charStats), money(STARTING_MONEY),
	inventory(new Equipment*[STARTING_INV_SIZE]), equipedArmor(-1), equipedWeapon(-1)
{}

/**
 * Constructor that takes an existing combat stats argument, along with money
 * and inventory, to allow for loading an existing character.
 * Using the initializer syntax demonstrated by Kate Gregory in pluralsight 5 - user defined types
 */
Character::Character(CharacterType r, string charName, int lvl, CombatStats charStats, double m, Equipment** e) :
	role(r), name(charName), level(lvl), stats(charStats), money(m), inventory(e) 
{}

Character::~Character()
{
	delete[] inventory;
}

// public methods

/**
 * Determines the power of an attack. This power is used both to determine if
 * the attack successfully landed, as well as calculate damge.
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
 * take damage.
 */
bool Character::defend()
{
	return false;
}

/**
 * Used to make purchases from the commisary. Handles the spedning of money,
 * and adds items to inventory.
 */
void Character::purchase()
{
}

/**
 * Allows any equipment item to be used
 */
/*template <class Type>
void Character::useItem(Type *e)
{
	int *stat;
	std::cout << typeid(e).name();


	if (typeid(e).name() == "Weapon")
		stat = &(this->stats.strength);
	std::cout << *str << "useItem\n";
	e->use(str);
}*/
void Character::useItem(Weapon *e)
{

}

void Character::useItem(Armor *)
{
}

void Character::useItem(PowerUp *)
{
}

void Character::removeWeapon()
{
}

void Character::removeArmor()
{
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

// displays the character's info and allows inventory management
void Character::displayCharSheet()
{
	int selection;
	while (true)
	{
		system("cls"); // clears the screen
		std::cout << std::setw(10) << getName() << std::setw(4) << getLevel() << std::endl;
		std::cout << std::endl;
		std::cout << "Money: " << getMoney() << std::endl;
		std::cout << (equipedArmor >= 0) ? inventory[equipedArmor]->getName() : "No Armor Equiped";
		std::cout << std::endl;
		std::cout << (equipedWeapon >= 0) ? inventory[equipedWeapon]->getName() : "No Weapon Equiped";
		std::cout << std::endl;
		displayStats();
		// show inventory
		std::cout << std::endl;
		std::cout << "Inventory\n";
		// TODO: if inventory is allowed to be expanded, ensure this reflects the current size, not starting size
		for (int i = 0; i < STARTING_INV_SIZE; ++i)
		{
			std::cout << i + 1 << ": " << inventory[i]->getName() << std::endl;
		}
		// allow items from inventory to be used
		std::cout << "Select an item to investigate or use. Enter 0 to return to the main menu: ";
		//TODO - validate this
		std::cin >> selection;
		if (selection = 0)
		{
			// end loop 
			break;
		}
		else
		{
			// check what the player wants to do with the item
			int select;
			std::cout << "Enter 1 to Examine, 2 to Use/Equip, 3 to Discard, or 4 to go back: ";
			// TODO validate
			std::cin >> select;
			switch (select)
			{
			case 1:
				std::cout << inventory[selection]->getName() << std::endl;
				std::cout << inventory[selection]->getDescription() << " Bonus: " << inventory[selection]->getBonus();
				break;
			case 2:
				
			}

			/*if (inventory[selection]->type() == WeaponType)
			{
				Weapon tmp = Weapon(inventory[selection]);
			    
			}
			else if (inventory[selection]->type() == ArmorType)
			{
				//a
			}
			else if (inventory[selection]->type() == PowerUpType)
			{
				//p
			}
			else 
			{
				//error handling
			}*/
		}
	}
}

// private methods

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

void Character::spendMoney(double)
{
}

void Character::addItemToInventory(Equipment*)
{
}

void Character::increaseStats(int spendablePoints)
{
	int selection;
	while (spendablePoints > 0)
	{
		std::cout << "You have " << spendablePoints << " to spend. Your current stats are:\n";
		this->displayStats();

		// TODO: Validate
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
