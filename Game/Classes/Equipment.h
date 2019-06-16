#pragma once
#include "cocos2d.h"
#define HAT_PLUSMAXHP 10000
#define SHOE_PLUSMOVESPEED 100
#define SWORD_PLUSDAMAGE 400

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