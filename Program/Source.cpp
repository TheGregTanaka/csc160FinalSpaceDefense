// Gregory Tanaka
#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Character.h"
#include "Source.h"

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::ofstream;
using std::ifstream;

// constants
//string GAME_DATA_FILE = "./SaveData.csv";
string GAME_DATA_FILE = "./SaveData.txt";

// func prototypes
void rules();
CombatStats characterCreation(string*, CharacterType*);
int displayMainMenu();
void chatacterSheet(Character*);
void shop(Character*, Equipment**, int);
void saveGame(Character*);
CombatStats loadGame(string*, CharacterType*, int*, double*, int*, int*);
bool yesOrNo(string const prompt, string const options = "Y/N");
int makeSelection(string const, int, int);

int main()
{
	// create items in game scope - this must be done prior to loading game data so the inventory can be loaded
	int stockSize = 12;
	// create some objects for shop inventory. Ideally, this should expand as the character levels up
	Equipment **shopStock = new Equipment*[stockSize];
	Weapon w1("Laser", 10.0, "A beam gun", 3);
	Weapon w2("Blaster", 15.0, "A powerful energy gun", 5);
	Weapon w3("BeamSword", 15.0, "A sword made of energy", 5);
	Weapon w4("PAL", 100.0, "Planetary Anihilation Laser", 20);
	Armor a1("FlakJacket", 5.0, "Offers mild protection", 2);
	Armor a2("PowerSuit", 20.0, "Offers medium protection", 7);
	Armor a3("MechSuit", 120.0, "A giant robot you can pilot", 25);
	PowerUp p1("MedKit", 5.0, "Restores 5 health", 5, HP);
	PowerUp p2("AdvancedMedKit", 10.0, "Restores 10 health", 10, HP);
	PowerUp p3("Steroids", 15.0, "Increases Strength by 2", 2, STR);
	PowerUp p4("NueralEnhancer", 15.0, "Increases Accuracy by 2", 2, ACC);
	PowerUp p5("Coffee", 15.0, "Increases Intellect by 2", 2, IQ);

	shopStock[0] = &w1;
	shopStock[1] = &w2;
	shopStock[2] = &w3;
	shopStock[3] = &w4;
	shopStock[4] = &a1;
	shopStock[5] = &a2;
	shopStock[6] = &a3;
	shopStock[7] = &p1;
	shopStock[8] = &p2;
	shopStock[9] = &p3;
	shopStock[10] = &p4;
	shopStock[11] = &p5;

	// this is where the fun begins
	//welcome the player to the game
	cout << "SPAAAAAACE\n";
	cout << "DEFENSE!!!\n\n";

	// declare some vars to get character data
	CombatStats charStats;
	CharacterType role;
	string charName;
	int lvl;
	double mon;
	int equipWeap, equipArm;

	bool isNewGame = yesOrNo("Press N for a New Game, or L to load", "N/L");
	if (isNewGame)
	{
		// Display how to play
		rules();
		system("cls"); // esentailly runs the clear screen command to reduce visual clutter - not a portable solution, only works on windows
		// create character
		charStats = characterCreation(&charName, &role);
		// set default starting values
		lvl = 0;
		mon = STARTING_MONEY;
		equipWeap = -1;
		equipArm = -1;
	}
	else
	{
		charStats = loadGame(&charName, &role, &lvl, &mon, &equipWeap, &equipArm);
	}


	// create the Player's Character
	Character pc = Character(role, charName, lvl, charStats, mon, equipWeap, equipArm);
	Character *pcPtr = &pc;
	// new characters are created at level 0 then immediately leveled up
	// to allow the player to spend some stat points for character custimization
	if (isNewGame)
	{
		pc.levelUp();
	}


	// create the "game loop"
	bool play = true;
	int selection;
	while (play)
	{
		// Display Menu to player
		selection = displayMainMenu();
		//based on player selection run other portions of the game
		switch (selection)
		{
		case 1:
			//Battle - not implemented so instead I've just demonstrated the operator overload to level up
			cout << "You won the battle and leveled up!\n";
			++pc;
			break;
		case 2:
			//Shop
			shop(pcPtr, shopStock, stockSize);
			break;
		case 3:
			//Character Sheet
			try
			{
				pc.displayCharSheet();
			}
			// the most common errors would come from the dynamic inventory array. I believe these are fixed, but try catch just in case
			catch (std::bad_alloc &e)
			{
				cout << "Bad allocation! Probably due to inventory mismanagement.\n" << endl;
				system("pause");
			}
			catch (...)
			{
				cout << "An unknown error occured! Returning to main menu.\n";
				system("pause");
			}
			break;
		case 4:
			play = false;
			break;
		//TODO REMOVE - FOR TESTING/DEBUGGING
		case 5:
			pc.receiveMoney(20);
			break;
		}
		
	}

	// save the game if the player wants
	bool save = yesOrNo("Would you like to save your game?");
	if (save)
	{
		saveGame(pcPtr);
	}

	// remove the dynamic array
	delete[] shopStock;

	cout << "Goodbye\n";
	system("pause");
	return 0;
}

/*
 * Purpose: Displays the exposition of the game and rules.
 *		Allows the player to skip rules if they wish
 */
void rules()
{
	// exposition
	cout << "??? : .... ! Hello there! You must be the new recruit! Welcome to" <<
		"\n\tthe CPP Enterprise, a space station conducting vital research to better" <<
		"\n\tthe lives of everyone in the galaxy. Really amazing stuff! Of course, you" <<
		"\n\twon't be seeing any of that. You and I are just up here to make sure the" <<
		"\n\tstation is safe and taken care of. Heck, those scientists keep the doors" <<
		"\n\tsealed, so you won't even be seeing them. Just you and me. Not a whole" <<
		"\n\tlot to do up here other than Battle Aliens, or buy stuff from the "
		"\n\tcommisary. By the way, I'm Bob, and I run the commisary.\n";
	// let players skip the rules if they already know how to play
	// this is in a loop, so if the player wishes, they can see the rules again,
	// additionally, the yesOrNo at the bottom will "stall" for the player, giving
	// them a chance to read the rules in case they get cleared off the screen
	// after this runs (which they do).
	// for efficiency reasons, string dialogue is declared outside the loop, and then
	// assigned values within.
	string dialogue = "";
	while (true)
	{
		// Rules about battling aliens
		dialogue = "Bob : Come see me if you need anything between battles. Would you\n\tlike to know more about battleing aliens?";
		if (yesOrNo(dialogue))
		{
			cout << "Bob: It's pretty simple. An alien will show up, and you're gonna fight it." <<
				"\n\tOf course, everyone has their own style of fighting aliens. BIG GUNs are going" <<
				"\n\tto favor strong attacks, and will utilize their strength stat the most. On" <<
				"\n\tthe other hand, ENGINEERs use brain over brawn. They utilize their intellect" <<
				"\n\tto set cunning traps. SNIPERs like to keep their distance. They utilize their" <<
				"\n\taccuracy for their attacks, and are also usually the quickest.\n";
		}
		// Rules about combat stats
		dialogue = "Bob : Would you like to know more about the character stats?";
		if (yesOrNo(dialogue))
		{
			cout << "Bob : There are six core stats to keep track of.\n" <<
				"\tStrength - this is your character's physical prowess and combat capability.\n" <<
				"\tIt is the primary stat for strong attacks.\n" <<
				"\tDefense - this is your character's ability to protect themselves from harm\n" <<
				"\twhen an unfriendly alien attacks.\n" <<
				"\tSpeed - this is how quick your character is. It determines who goes first\n" <<
				"\tin a combat, and also contributes to defending against attacks.\n" <<
				"\tIntellect - this is your character's relative intellegence. It is the\n" <<
				"\tclever attacks.\n" <<
				"\tAccuracy - this is your character's ability to aim. Is is the primary stat" <<
				"\tfor accurate attacks.\n" <<
				"\tAnd possibly most importantly, Health - This is your character's well being.\n" <<
				"\t\tIf this stat hits 0, your character dies and the game is over. Certain items\n" <<
				"\t\tcan increase this stat (there is no cap), and leveling up will increase it\n" <<
				"\t\tas well.\n";
		}
		// Rules about equipment
		dialogue = "Bob : Would you like to know about equipment and the inventory?";
		if (yesOrNo(dialogue))
		{
			cout << "Bob: You have an inventory, which can hold up to 6 items at the start of the game.\n" <<
				"\tThere are 3 main types of equipment; Armor, Weapons, and PowerUps. For Armor\n" <<
				"\tand weapons, you may only have one of each equiped at any given time.\n" <<
				"\tEquipping an item does not remove it from your inventory. Your equiped Armor\n" <<
				"\twill give a bonus to your defense, while your equiped Weapon will boost\n" <<
				"\tattack power. PowerUps, are one time use items which will provide an effect\n" <<
				"\tand then be comsumed (removed from your inventory). These effects mostly will\n" <<
				"\tincrease certain stats.\n";
			cout << "Bob: In the commisary, there will be items available for sale with a price.\n" <<
				"\tEnter the number of the item you are interested in, and you will be given\n" <<
				"\toptions to inspect the item (see details about it and it's effect) or to buy.\n" <<
				"\tOf course, you'll need enough money to make the purchase!\n";
		}
		// Offer to repeat
		dialogue = "Bob : Would you like to hear any of that again?";
		if (!yesOrNo(dialogue))
			break;
	}
}

/*
 * Purpose: Allows the player to create their character. The player can give
 *		the character a name, determine what type of character which sets base
 *		stats, then is able to assign a few stat points.
 * @param charName An out parameter, the name that will be used for the character
 * @param role An out parameter, the type of character
 * @returns CombatStats A collection of stats determined by the CharacterType
 *		with some modifications from the player
 */
CombatStats characterCreation(string *charName, CharacterType *role)
{
	// declare vars
	CombatStats cs;
	int selection;
	cout << "Enter a name for your character: ";
	// TODO: Validate this
	cin >> *charName;

	// Select character Role
	cout << "What type of character would you like to play?\n" <<
		"1: BIG GUN: Big, strong, and militant; this hardened vetran is here to kick \n" <<
		"\tass and... Well that's pretty much all he's here for.\n" <<
		"2: ENGINEER: Smart. And maybe a little crazy. And frighteningly fond of explosives \n"
		<< "\tand traps.\n" <<
		"3: SNIPER: This sneaky S.O.B. isn't as tough, but has eyes like a hawk and a \n" <<
		"\thell of a shot.\n";
	selection = makeSelection("Enter the number of your seletion: ", 1, 3);

	// based on selection set base values for stats
	switch (selection)
	{
	case 1:
		cs.strength = 7;
		cs.defense = 6;
		cs.speed = 3;
		cs.intellect = 3;
		cs.accuracy = 4;
		*role = BigGun;
		break;
	case 2:
		cs.strength = 4;
		cs.defense = 5;
		cs.speed = 3;
		cs.intellect = 7;
		cs.accuracy = 4;
		*role = Engineer;
		break;
	case 3:
		cs.strength = 2;
		cs.defense = 3;
		cs.speed = 6;
		cs.intellect = 6;
		cs.accuracy = 8;
		*role = Sniper;
		break;
	}
	cs.health = STARTING_HP;
	cs.isTrained = true;
	cs.isAlive = true;

	return cs;
}

/*
 * Purpose: Displays the main menu to the player. Calls the makeSelection func
 *		which contains built in validation.
 * @returns int the number coresponding with the players selection
 */
int displayMainMenu()
{
	// clear the screen since this is a "new page"
	system("cls");
	int selection;
	cout << "Main Menu\n";
	cout << "1: Battle\n2: Shop\n3: View Character Sheet\n4: Exit\n";
	selection = makeSelection("Enter the number of your selection: ", 1, 5);
	return selection;
}

/*
 * Purpose: Allows the character to view and purchase items.
 * @param pc A pointer to the character visiting the shop. This allows the
 *		character to call their purchase method on items
 * @param shopStock an array of pointers to the equipment items to be displayed
 * @param stockSize The number of elements in shopStock
 */
void shop(Character  *pc, Equipment **shopStock, int stockSize)
{
	// declare vars
	bool loop = true;
	int selection;
	int doWhat;
	//loop to allow the player to keep making purchases
	while (loop)
	{
		// Clear the screen since this is a "new page"
		system("cls");
		// welcome character, display shop menu
		cout << "Bob : Hello, " << pc->getName() << "! Welcome to the commisary!\n";
		cout << "\tCome in, come in! Here's what I've got for sale:\n";
		cout << std::setfill('*') << std::left << setw(3) << "ID" << std::left <<
			setw(16) << "Item" << std::left << setw(7) << "Type" << setw(5) << 
			"Cost\n";
		cout << endl;
		// Display all the items in shopStock
		for (int i = 0; i < stockSize; ++i)
		{
			// put a space before the single digit rows
			string rowEqualizer = (i < 9) ? " " : "";
			cout << rowEqualizer;
			cout << i + 1 << " ";
			cout << std::left << std::setfill('-') << setw(16) << shopStock[i]->getName() <<
				std::setfill('-') << setw(7) << shopStock[i]->eType() << std::setfill('-') <<
				shopStock[i]->getCost() << endl;
		}
		cout << " 0 Back to Main Menu\n";
		cout << "Current money: " << pc->getMoney() << endl;

		cout << "\nBob : Anything catch your interest?\n";
		// prompt the player to select an item
		selection = makeSelection("Enter the ID of the item you're interested in: ", 0, 12);
		if (selection == 0)
		{
			loop = false;
			break;
		}
		// since the index had one added for the id display, decrement the selection by one to match the true index
		--selection;
		// prompt player to do something. They may see item details or buy the item.
		doWhat = makeSelection("Enter 1 to Examine, 2 to Purchase, or 3 to go back: ", 1, 3);
		switch (doWhat)
		{
		case 1:
			cout << shopStock[selection]->getName() << endl;
			cout << shopStock[selection]->getDescription() << " Bonus: " << shopStock[selection]->getBonus();
			cout << endl;
			system("pause");
			break;
		case 2:
			pc->purchase(shopStock[selection]);
			system("pause");
			break;
		case 3:
			break;
		}

	}
}

/*
 * Purpose: Writes character data to a file to allow load games later.
 * @param pc A pointer to the character whose data will be written
 */
void saveGame(Character *pc)
{
	// write all the data of the character to a game-save file
	ofstream save;
	//ofstream::app allows appending to the end of file so as to not wipe out previous game data
	save.open(GAME_DATA_FILE, ofstream::app);
	// verify file is open
	if (!save.is_open())
	{
		cout << "\nSome sort of error!\nGame not saved!\n";
		//some sort of error
	}
	else
	{
		save << pc->getName() << " " << pc->getLevel() << " " << pc->getRole() <<
			" " << pc->getHealth() << " " << pc->getStrength() << " " <<
			pc->getDefense() << " " << pc->getSpeed() << " " << pc->getIntellect() <<
			" " << pc->getAccuracy() << " " << pc->getMoney() << " " <<
			pc->getEquipedWeapon() << " " << pc->getEquipedArmor() << " " <<
			pc->getInventoryString() << endl;
		//close file
		save.close();
	}
}

// TODO figure out a way to load inventory that actally works... Or possibly just give character money for the items?
/*
 * Purpose: Reads from the game save file, and supplies all the data for character creation
 * @param charName The character's name
 * @param role The type of character
 * @param lvl The character's level
 * @param mon The character's money
 * @param equipWeap If the character had a weapon equiped, this was it's element in the inventory
 * @param equipArm If the character had armor equiped, this is it's element in the inventory
 */
CombatStats loadGame(string *charName, CharacterType *role, int *lvl, double *mon, int *equipWeap, int *equipArm)
{
	// declare vars
	string line;
	int fieldStart, fieldLen, fieldEnd;
	int lineCount = 1;
	CombatStats cs;
	int roleInt;
	ifstream load;
	string delim = " ";
	string tmp, tmpLvl;

	load.open(GAME_DATA_FILE);
	if (load.is_open())
	{
		int selection;
		while (getline(load, line))
		{
			fieldStart = 0;
			fieldEnd = line.find(delim);
			tmp = (line.substr(fieldStart, fieldEnd));
			// advance to the next "field" - data between two spaces - field
			// starts after the previous fieldEnd space
			fieldStart = fieldEnd + 1;
			fieldEnd = (line.find(delim, fieldStart)); // finds the next space
			fieldLen = fieldEnd - fieldStart;
			// starting from one character after the second space, return up until the next space
			tmpLvl = line.substr(fieldStart, fieldLen);
			// output the first two fields of each line - character name and lvl
			// lineCount utilizes the post-increment operator to output current
			// value then increment for the next loop
			cout << lineCount++ << " " << tmp << " - lvl: " << tmpLvl << endl;
		}
		selection = makeSelection("Enter the number of the character you would like to load.", 1, lineCount);

		// Go back to begining of file
		load.clear();
		load.seekg(0, ifstream::beg);


		lineCount = 1;
		// loop to selected line, and read all the data from that line, then break the loop
		while (!load.eof())
		{
			if (lineCount == selection)
			{
				load >> *charName >> *lvl >> roleInt >> cs.health >>
					cs.strength >> cs.defense >> cs.speed >> cs.intellect >>
					cs.accuracy >> *mon >> *equipWeap >> *equipArm;
				break;
			}
			++lineCount;
		}
		load.close();

		
		cs.isTrained = true;
		cs.isAlive = true;
		
		//remove dynamic array of pointers
		// because it's not just an array of objects, delete[] did not work
		/*for (int i = 0; i < STARTING_INV_SIZE; ++i)
		{
			delete tmpInv[i];
		}*/
	}
	else
	{
		throw std::runtime_error("Unabnle to open file! Game could not load!\n");
	}
	return cs;
}

/*
 * Purpose: Adapted from my code from challenge 4, this will prompt the user
 *		to select from one of two options, by default, Yes or No
 * @param prompt The prompt which is displayed to the user
 * @param options The two choices the user is to select from. These SHOULD
 *		NOT include spaces and colon, but MUST be separated by a single character. They
 *		MUST be provided upercase however, as the function will run toupper
 *		on the user's entry, and it will be compared against the provided options.
 *		Each option MUST be a single letter.
 *		These default to "Y/N". Formatting will be added.
 * @returns boolean True if the user indicates the first option (yes),
 *		false for the second option (no).
 */
bool yesOrNo(string const prompt, string const options)
{
	char opt1 = options.at(0);
	char opt2 = options.at(2);
	char entry;
	while (true)
	{
		cout << prompt + " " + options + ": ";
		cin >> entry;
		entry = toupper(entry);
		if ((entry != opt1 && entry != opt2) || cin.fail())
		{
			cout << "Must enter " << opt1 << " or " << opt2 << "!\n";
			cin.clear();
			cin.ignore(100, '\n');
		}
		else
		{
			if (entry == opt1)
				return true;
			else
				return false;
		}
	}
}

/*
 * Purpose: repromts user to make a number selection in a certain range until a
 *		valid selection is made.
 * @param prompt The promt displayed to the user
 * @param lower The lowest valid number that may be entered
 * @param upper The highest valid number that may be entered
 */
int makeSelection(string const prompt, int lower, int upper)
{
	int selection;
	// loop is broken by the return of a valid value
	while (true)
	{
		// display prompt
		cout << prompt;
		cin >> selection;
		// validate selection
		if (cin.fail() || selection < lower || selection > upper)
		{
			cout << "Must enter an integer between " << lower << " and " << upper << "!\n";
			cin.clear();
			cin.ignore(100, '\n');
		}
		else
		{
			// return breaks the loop 
			return selection;
		}
	}
}