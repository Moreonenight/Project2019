#pragma once
#include "cocos2d.h"
#define HAT_PLUSMAXHP 1000
#define SHOE_PLUSMOVESPEED 20
#define SWORD_PLUSDAMAGE 100

class Equipment {
public:
	bool isOccupied;
	std::string Name;
	int Price,
		plusDamage,
		plusMoveSpeed,
		plusMaxHp;
	Equipment() { isOccupied = false;}
	Equipment(std::string name);
};