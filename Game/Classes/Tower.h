#pragma once
#include "cocos2d.h"
#include "unit.h"
USING_NS_CC;
class Tower:public unit
{
private:
	unit* Soldier_1;
	unitdata* Soldier_2;
public:
	virtual bool init();
	
	//void Soldier_1_AI(Layer* EntityLayer);
	
	CREATE_FUNC(Tower);
};

