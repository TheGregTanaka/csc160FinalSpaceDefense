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
string GAME_DATA_FILE = "./SaveData.csv";

// func prototypes
bool yesOrNo(string const prompt, string const options = "Y/N");
void rules();
CombatStats characterCreation(string*, CharacterType*);
int displayMainMenu();
void chatacterSheet(Character*);
void shop(Character*, Equipment**, int);
void saveGame(Character*);
CombatStats loadGame(string*, CharacterType*, int*, double*, int*, int*);
void instantiateCharacter(bool, Equipment**, Character*);

// TODO: Clean up unused/dead code
// TODO: Comment
// TODO: Document functions
// TODO: Create requirement file - README would be ideal for this
int main()
{
	// create items in game scope - this must be done prior to loading game data so the inventory can be loaded
	int stockSize = 12;
	// create some objects for shop inventory. Ideally, this should expand as the character levels up
	Equipment **shopStock = new Equipment*[stockSize];
	Weapon w1("Laser", 10.0, "A beam gun", 3);
	Weapon w2("Blaster", 15.0, "A powerful energy gun", 5);
	Weapon w3("Beam Sword", 15.0, "A sword made of energy", 5);
	Weapon w4("PAL", 100.0, "Planetary Anihilation Laser", 20);
	Armor a1("Flak Jacket", 5.0, "Offers mild protection", 2);
	Armor a2("Power Suit", 20.0, "Offers medium protection", 7);
	Armor a3("Mech Suit", 120.0, "A giant robot you can pilot", 25);
	PowerUp p1("MedKit", 5.0, "Restores 5 health", 5);
	PowerUp p2("Advanced MedKit", 10.0, "Restores 10 health", 10);
	PowerUp p3("Steroids", 15.0, "Increases Strength by 2", 2);
	PowerUp p4("Nueral Enhancer", 15.0, "Increases Accuracy by 2", 2);
	PowerUp p5("Coffee", 15.0, "Increases Intellect by 2", 2);

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
	bool isNewGame = yesOrNo("Press N for a New Game, or L to load", "N/L");

	// declare some vars to get character data
	CombatStats charStats;
	CharacterType role;
	string charName;
	int lvl;
	double mon;
	int equipWeap, equipArm;
	int invCount;
	Equipment** tmpInv;

	if (isNewGame)
	{
		// Display how to play
		rules();
		system("cls"); // esentailly runs the clear screen command to reduce visual clutter - not a portable solution, only works on windows
		// create character
		charStats = characterCreation(&charName, &role);
		// use constants to set certain things to defaults
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
	//instantiateCharacter(isNewGame, shopStock, pcPtr);
	//pc.invDebug();
	pcPtr->invDebug();
	system("pause");
	// new characters are created at level 0 then immediately leveled up
	// to allow the player to spend some stat points for character custimization
	if (isNewGame)
	{
		pc.levelUp();
	}
	cout << pc.getName() << endl;
	pc.displayStats();


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
			//Battle
			break;
		case 2:
			//Shop
			shop(pcPtr, shopStock, stockSize);
			break;
		case 3:
			//Character Sheet
			pc.invDebug();
			system("pause");
			pc.displayCharSheet();
			break;
		case 4:
			play = false;
			break;
		}
		
	}

	bool save = yesOrNo("Would you like to save your game?");
	if (save)
	{
		//TODO make this functionality
		saveGame(pcPtr);
	}

	// remove the dynamic array
	delete[] shopStock;

	cout << "Goodbye\n";
	system("pause");
	return 0;
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
			cout << "Must enter y or n!\n";
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

// outputs how to play
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
		dialogue = "Bob : Would you like to hear any of that again?";
		if (!yesOrNo(dialogue))
			break;
	}
}

// I created this as a way of calling the constructor dynamically. I suspect
// this is not a standard practice, but was my work around for this issue.
// The need for separate constructors comes from the dynamic allocation of the
// inventory array, and filling it with Empty slots. I considered creating the
// inventory in the main, and passing it to the Character constructor, but that
// didn't feel like the correct solution
void instantiateCharacter(bool newGame, Equipment** items, Character* pcPtr)
{/*
	// declare some vars to get character data
	CombatStats charStats;
	CharacterType role;
	string charName;

	if (newGame)
	{
		// Display how to play
		rules();
		system("cls"); // esentailly runs the clear screen command to reduce visual clutter - not a portable solution, only works on windows
		// create character
		charStats = characterCreation(&charName, &role);
		*pcPtr = Character(role, charName, charStats);
	}
	else
	{
		loadGame(items, pcPtr);
	}*/
}

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
	cout << "Enter the number of your seletion: ";
	// TODO: validate
	cin >> selection;

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

int displayMainMenu()
{
	// clear the screen since this is a "new page"
	system("cls");
	int selection;
	cout << "Main Menu\n";
	cout << "1: Battle\n2: Shop\n3: View Character Sheet\n4: Exit\n";
	cout << "Enter the number of your selection: ";
	//TODO validate
	cin >> selection;
	return selection;
}

void shop(Character  *pc, Equipment **shopStock, int stockSize)
{
	//loop to allow the player to keep making purchases
	bool loop = true;
	int selection;
	int doWhat;
	while (loop)
	{
		// Clear the screen since this is a "new page"
		system("cls");
		cout << "Bob : Hello, " << pc->getName() << "! Welcome to the commisary!\n";
		cout << "\tCome in, come in! Here's what I've got for sale:\n";
		cout << std::setfill('*') << std::left << setw(3) << "ID" << std::left <<
			setw(16) << "Item" << std::left << setw(7) << "Type" << setw(5) << 
			"Cost\n";
		cout << endl;
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

		cout << "\nBob : Anything catch your interest?\n" <<
			"Enter the ID of the item you're interested in: ";
		// TODO validate
		cin >> selection;
		if (selection == 0)
		{
			loop = false;
			break;
		}
		// since the index had one added for the id display, decrement the selection by one to match the true index
		--selection;
		cout << "Enter 1 to Examine, 2 to Purchase, or 3 to go back: ";
		cin >> doWhat;
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

//writes character data to a file
void saveGame(Character *pc)
{
	// write all the data of the character to a game-save csv
	// because the inventory set up is a little wonky with an array of pointers... TODO : Finish this thought
	ofstream save;
	save.open(GAME_DATA_FILE);
	if (!save.is_open())
	{
		cout << "\nSome sort of error!\nGame not saved!\n";
		//some sort of error
	}
	else
	{

		save << pc->getName() << "," << pc->getLevel() << "," << pc->getRole() <<
			"," << pc->getHealth() << "," << pc->getStrength() << "," << 
			pc->getDefense() << "," << pc->getSpeed() << "," << pc->getIntellect() <<
			"," << pc->getAccuracy() << "," << pc->getMoney() << "," << 
			pc->getEquipedWeapon() << "," << pc->getEquipedArmor() << "," <<
			pc->getInventoryString() << endl;
		//close file
		save.close();
	}
}

// TODO super inefficient.. fix this
// reads data from the save file, and creates a character.
CombatStats loadGame(string *charName, CharacterType *role, int *lvl, double *mon, int *equipWeap, int *equipArm)
{
	string line;
	int fieldStart, fieldLen, fieldEnd;
	int lineCount = 1;
	/*string name;
	int lvl;
	int roleInt;
	double mon;
	int equipWeap, equipArm;
	int invCount;
	Equipment** tmpInv;*/
	CombatStats cs;
	int roleInt;
	int hp, str, def, spd, iq, acc;
	ifstream load;
	string delim = ","; // since game file is a csv, split on commas
	string tmp;
	

	load.open(GAME_DATA_FILE);
	if (load.is_open())
	{
		int selection;
		while (getline(load, line))
		{
			fieldStart = 0;
			fieldEnd = line.find(delim);
			*charName = (line.substr(fieldStart, fieldEnd));
			// advance to the next "field" - data between two commas - field
			// starts after the previous fieldEnd comma
			fieldStart = fieldEnd + 1;
			fieldEnd = (line.find(delim, fieldStart)); // finds the next comma
			fieldLen = fieldEnd - fieldStart;
			// starting from one character after the second comma, return up until the next comma
			tmp = line.substr(fieldStart, fieldLen);
			*lvl = stoi(tmp);
			// output the first two fields of each line - character name and lvl
			// lineCount utilizes the post-increment operator to output current
			// value then increment for the next loop
			cout << lineCount++ << " " << *charName << " lvl: " << *lvl << endl;
		}
		cout << "Enter the number of the character you would like to load.";
		// TODO validate
		cin >> selection;

		/*tmpInv = new Equipment*[STARTING_INV_SIZE];
		for (int i = 0; i < STARTING_INV_SIZE; ++i)
		{
			tmpInv[i] = new EmptySlot();
		}*/

		// Go back to begining of file
		load.clear();
		load.seekg(0, ifstream::beg);

		lineCount = 1;
		// loop to selected line, and read all the data from that line
		while (getline(load, line))
		{
			// this is super WET and I don't like it, but I couldn't find a good way to parse a csv that
			// wouldn't have required pretty extensive copying from stackoverflow or using lots of tools not covered in class
			if (lineCount == selection)
			{
				fieldStart = 0;
				fieldEnd = line.find(delim);
				*charName = (line.substr(fieldStart, fieldEnd));

				// advance to next field
				fieldStart = fieldEnd + 1;
				fieldEnd = (line.find(delim, fieldStart));
				fieldLen = fieldEnd - fieldStart;
				tmp = line.substr(fieldStart, fieldLen);
				*lvl = stoi(tmp);

				// advance to next field
				fieldStart = fieldEnd + 1;
				fieldEnd = (line.find(delim, fieldStart));
				fieldLen = fieldEnd - fieldStart;
				tmp = line.substr(fieldStart, fieldLen);
				roleInt = stoi(line.substr(fieldStart, fieldLen));
				*role = (CharacterType)roleInt;

				// advance to next field
				fieldStart = fieldEnd + 1;
				fieldEnd = (line.find(delim, fieldStart));
				fieldLen = fieldEnd - fieldStart;
				tmp = line.substr(fieldStart, fieldLen);
				hp = stoi(tmp);

				// advance to next field
				fieldStart = fieldEnd + 1;
				fieldEnd = (line.find(delim, fieldStart));
				fieldLen = fieldEnd - fieldStart;
				tmp = line.substr(fieldStart, fieldLen);
				str = stoi(tmp);

				// advance to next field
				fieldStart = fieldEnd + 1;
				fieldEnd = (line.find(delim, fieldStart));
				fieldLen = fieldEnd - fieldStart;
				tmp = line.substr(fieldStart, fieldLen);
				def = stoi(tmp);

				// advance to next field
				fieldStart = fieldEnd + 1;
				fieldEnd = (line.find(delim, fieldStart));
				fieldLen = fieldEnd - fieldStart;
				tmp = line.substr(fieldStart, fieldLen);
				spd = stoi(tmp);

				// advance to next field
				fieldStart = fieldEnd + 1;
				fieldEnd = (line.find(delim, fieldStart));
				fieldLen = fieldEnd - fieldStart;
				tmp = line.substr(fieldStart, fieldLen);
				iq = stoi(tmp);

				// advance to next field
				fieldStart = fieldEnd + 1;
				fieldEnd = (line.find(delim, fieldStart));
				fieldLen = fieldEnd - fieldStart;
				tmp = line.substr(fieldStart, fieldLen);
				acc = stoi(tmp);

				// advance to next field
				fieldStart = fieldEnd + 1;
				fieldEnd = (line.find(delim, fieldStart));
				fieldLen = fieldEnd - fieldStart;
				tmp = line.substr(fieldStart, fieldLen);
				*mon = stod(tmp);

				// advance to next field
				fieldStart = fieldEnd + 1;
				fieldEnd = (line.find(delim, fieldStart));
				fieldLen = fieldEnd - fieldStart;
				tmp = line.substr(fieldStart, fieldLen);
				*equipWeap = stoi(tmp);

				// advance to next field
				fieldStart = fieldEnd + 1;
				fieldEnd = (line.find(delim, fieldStart));
				fieldLen = fieldEnd - fieldStart;
				tmp = line.substr(fieldStart, fieldLen);
				*equipArm = stoi(tmp);

				// advance to next field
				/*fieldStart = fieldEnd + 1;
				fieldEnd = (line.find(delim, fieldStart));
				fieldLen = fieldEnd - fieldStart;
				tmp = line.substr(fieldStart, fieldLen);
				invCount = stoi(tmp);

				// build the inventory dynamically
				//tmpInv = new Equipment*[invCount]; already created in this scope
				string itemName;
				for (int i = 0; i < invCount; ++i)
				{
					// advance to next field
					fieldStart = fieldEnd + 1;
					fieldEnd = (line.find(delim, fieldStart));
					fieldLen = fieldEnd - fieldStart;
					itemName = line.substr(fieldStart, fieldLen);
					// another highly inelegant solution, but again couldn't find a better way that wasn't someone else's algorithm
					if (itemName == "Laser")
					{ 
						delete tmpInv[i];
						tmpInv[i] = items[0];
					}
					else if (itemName == "Blaster")
					{
						delete tmpInv[i];
						tmpInv[i] = items[1];
					}
					else if (itemName == "Beam Sword")
					{
						delete tmpInv[i];
						tmpInv[i] = items[2];
					}
					else if (itemName == "PAL")
					{
						delete tmpInv[i];
						tmpInv[i] = items[3];
					}
					else if (itemName == "Flak Jacket")
					{
						delete tmpInv[i];
						tmpInv[i] = items[4];
					}
					else if (itemName == "Power Suit")
					{
						delete tmpInv[i];
						tmpInv[i] = items[5];
					}
					else if (itemName == "Mech Suit")
					{
						delete tmpInv[i];
						tmpInv[i] = items[6];
					}
					else if (itemName == "MedKit")
					{
						delete tmpInv[i];
						tmpInv[i] = items[7];
					}
					else if (itemName == "Advanced MedKit")
					{
						delete tmpInv[i];
						tmpInv[i] = items[8];
					}
					else if (itemName == "Steroids")
					{
						delete tmpInv[i];
						tmpInv[i] = items[9];
					}
					else if (itemName == "Nueral Enhancer")
					{
						delete tmpInv[i];
						tmpInv[i] = items[10];
					}
					else if (itemName == "Coffee")
					{
						delete tmpInv[i];
						tmpInv[i] = items[11];
					}
					else
					{
						delete tmpInv[i];
						tmpInv[i] = new EmptySlot();
					}
				}*/
			}
			else
			{
				hp = 0;
				str = 0;
				def = 0;
				spd = 0;
				iq = 0;
				acc = 0;
			}
		}
		load.close();

		
		cs.health = hp;
		cs.strength = str;
		cs.defense = def;
		cs.speed = spd;
		cs.intellect = iq;
		cs.accuracy = acc;
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

