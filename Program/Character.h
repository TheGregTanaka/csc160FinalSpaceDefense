#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include "CombatStats.h"
#include "Weapon.h"
#include "Armor.h"
#include "PowerUp.h"
#include "EmptySlot.h"
using std::string;

// define constants to avoid "magic numbers"
const int STARTING_HP = 10;
const double STARTING_MONEY = 15;
const int STARTING_INV_SIZE = 6;

enum CharacterType
{
	BigGun,
	Engineer,
	Sniper,
	Creature
};

class Character
{
private:
	string name;
	CharacterType role;
	CombatStats stats;
	int level;
	Equipment **inventory;
	double money;
	int equipedWeapon; // represents index of equiped weapon in inventory
	int equipedArmor; // represents index of equiped armor in inventory
	//methods
	int accurateAttack();
	int strongAttack();
	int cleverAttack();
	int specialAttack();
	bool takeDamage(int);
	void increaseStats(int);
public:
	Character(CharacterType, string, int, CombatStats, double, int, int);
	Character(CharacterType, string, int, CombatStats, double, int, int, int, Equipment**);
	~Character();
	// getters
	string getName() { return name; };
	CharacterType getRole() { return role; };
	int getHealth() { return stats.health; };
	int getStrength() {	return stats.strength; };
	int getDefense() { return stats.defense; };
	int getSpeed() { return stats.speed; };
	int getIntellect() { return stats.intellect; };
	int getAccuracy() { return stats.accuracy; };
	int getIsTrained() { return stats.isTrained; };
	bool getAlive() { return stats.isAlive; };
	CombatStats getStats() { return stats; };
	int getLevel() { return level; };
	double getMoney() { return money; };
	int getEquipedWeapon() { return equipedWeapon; };
	int getEquipedArmor() { return equipedArmor; };
	string getInventoryString();
	// setters
	void setName(string s) { name = s; };
	void setHealth(int h) { stats.health = h; };
	void setStrength(int s) { stats.strength = s; };
	void setDefense(int d) { stats.defense = d; };
	void setSpeed(int s) { stats.speed = s; };
	void setIntellect(int i) { stats.intellect = i; };
	void setAccuracy(int a) { stats.accuracy = a; };
	//methods
	int attack();
	bool defend();
	void purchase(Equipment*);
	void useItem(Equipment*, int);
	void useItem(PowerUp*, int);
	void receiveMoney(double m);
	void removeWeapon();
	void removeArmor();
	void levelUp();
	void displayStats();
	void displayCharSheet();
	Character& operator++();
	Character operator++(int);
};
