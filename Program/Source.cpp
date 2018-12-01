// Gregory Tanaka
#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "Character.h"
#include "Weapon.h"
#include "Source.h"

using std::cout;
using std::cin;
using std::endl;
using std::setw;

bool yesOrNo(string const prompt, string const options = "Y/N");
void rules();
CombatStats characterCreation(string*, CharacterType*);
int displayMainMenu();
void chatacterSheet(Character *);

// TODO: Clean up unused/dead code
// TODO: Comment
// TODO: Document functions
// TODO: Create requirement file - README would be ideal for this
int main()
{
	//welcome the player to the game
	cout << "SPAAAAAACE\n";
	cout << "DEFENSE!!!\n\n";
	bool isNewGame = yesOrNo("Press N for a New Game, or L to load", "N/L");
	// declare some vars to get character data
	CombatStats charStats;
	CharacterType role;
	string charName;

	if (isNewGame)
	{
		// Display how to play
		rules();
		system("cls"); // esentailly runs the clear screen command to reduce visual clutter - not a portable solution, only works on windows
		// create character
		charStats = characterCreation(&charName, &role);
	}
	else
	{
		//TODO
		// load game data from file
	}

	// create the Player's Character
	Character pc = Character(role, charName, charStats);
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
			shop();
			break;
		case 3:
			//Character Sheet
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
		//saveGame();
	}
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
				"\t\tIt is the primary stat for strong attacks.\n" <<
				"\tDefense - this is your character's ability to protect themselves from harm\n" <<
				"\t\twhen an unfriendly alien attacks.\n" <<
				"\tSpeed - this is how quick your character is. It determines who goes first\n" <<
				"\t\tin a combat, and also contributes to defending against attacks.\n" <<
				"\tIntellect - this is your character's relative intellegence. It is the\n" <<
				"\t\tclever attacks.\n" <<
				"\tAccuracy - this is your character's ability to aim. Is is the primary stat" <<
				"\t\tfor accurate attacks.\n" <<
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
	int selection;
	cout << "Main Menu\n";
	cout << "1: Battle\n2: Shop\n3: View Character Sheet\n4: Exit";
	cout << "Enter the number of your selection: ";
	//TODO validate
	cin >> selection;
	return selection;
}

void shop()
{

}