#include "Soldier.h"

#define CENTERX origin.x+visibleSize.width/2
#define CENTERY origin.y+visibleSize.height/2
USING_NS_CC;

bool Soldier::Soldierinit(string Soldiername,int number,cocos2d::TMXTiledMap* Map, Vector<unit*>* mapUnits,Layer* ammoLayer)
{
	_ammolayer = ammoLayer;
	auto data = new(unitdata);
	data->initial(Soldiername);
	initial(data, Map, mapUnits, ammoLayer);
	auto Act = Animate::create(AnimationCache::getInstance()->getAnimation(Soldiername +"up_stand"));
	setScale(0.6);
	runAction(Act);
	if (getid()[1] == 'r'&&getid()[2] == '1'&&number == 1)
	{
		setPosition(1700, 1350);
		this->changeGold(32);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '2'&&number == 1)
	{
		setPosition(1850, 1300);
		this->changeGold(32);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '3'&&number == 1)
	{
		setPosition(1950, 1250);
		this->changeGold(45);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '1'&&number == 2)
	{
		setPosition(1750, 1300);
    this->changeGold(32);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '2'&&number == 2)
	{
		setPosition(1800, 1250);
    this->changeGold(32);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '3'&&number == 2)
	{
		setPosition(1850, 1200);
    this->changeGold(45);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '1'&&number == 1)
	{
		setPosition(490, 410);
    this->changeGold(32);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '2'&&number == 1)
	{
		setPosition(630, 340);
    this->changeGold(32);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '3'&&number == 1)
	{
		setPosition(700, 270);
    this->changeGold(45);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '1'&&number == 2)
	{
		setPosition(390, 340);
    this->changeGold(32);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '2'&&number == 2)
	{
		setPosition(460, 270);
    this->changeGold(32);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '3'&&number == 2)
	{
		setPosition(530, 200);
		this->changeGold(45);
	}
	scheduleUpdate();
	return true;
}


bool Soldier::AttackingJudgeAI()
{
	stopAllActions();
	if (getAttackingTarget() == nullptr&&GetAlreadydead()==false)
	{
		if (getid()[1] == 'r')
		{
			moveDirectionByKey(getDir(getPosition(), Vec2(300, 180)), Vec2(300, 180));
		}
		else if (getid()[1] == 'b')
		{
			moveDirectionByKey(getDir(getPosition(), Vec2(1930, 1430)), Vec2(1930, 1430));
		}

	}
	else if(getAttackingTarget() != nullptr&&GetAlreadydead() == false) {
		attackTo(getAttackingTarget());
	
		}
	return true;
}
