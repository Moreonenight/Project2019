#include "Equipment.h"


Equipment::Equipment(std::string name) {
	if (name == "Shoe") {
		plusDamage = 0;
		plusMaxHp = 0;
		plusMoveSpeed = SHOE_PLUSMOVESPEED;
	}
	else if (name == "Hat") {
		plusDamage = 0;
		plusMaxHp = HAT_PLUSMAXHP;
		plusMoveSpeed = 0;
	}
	else if (name == "Sword") {
		plusDamage = SWORD_PLUSDAMAGE;
		plusMaxHp = 0;
		plusMoveSpeed = 0;
	}
	isOccupied = true;
	Price = 200;
	Name = name;
}