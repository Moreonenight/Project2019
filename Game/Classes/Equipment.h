#pragma once
#include "cocos2d.h"

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