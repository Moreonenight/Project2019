#pragma once
#include "cocos2d.h"

class Equipment 
{
public:
	bool isOccupied;

	std::string Name;
	int Price;
	int plusMoveSpeed;
	int plusMaxHp;
	int plusDamage;

	Equipment() {
		isOccupied = false;
	}
	Equipment(std::string name);
	~Equipment(){}
};