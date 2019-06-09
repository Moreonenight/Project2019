#include "Soldier.h"

#define CENTERX origin.x+visibleSize.width/2
#define CENTERY origin.y+visibleSize.height/2
USING_NS_CC;

bool Soldier::Soldierinit(string Soldiername,int number,cocos2d::TMXTiledMap* Map, Vector<unit*>* mapUnits)
{
	auto data = new(unitdata);
	data->initial(Soldiername);
	auto Act = Animate::create(AnimationCache::getInstance()->getAnimation(Soldiername +"up_stand"));
	setScale(0.6);
	runAction(Act);
	initial(data, Map, mapUnits);
	if (getid()[1] == 'r'&&getid()[2] == '1'&&number == 1)
	{
		setPosition(1000, 1000);
		this->changeGold(32);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '2'&&number == 1)
	{
		setPosition(1000, 1000);
		this->changeGold(32);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '3'&&number == 1)
	{
		setPosition(1000, 1000);
		this->changeGold(45);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '1'&&number == 2)
	{
		setPosition(1000, 1000);
    this->changeGold(32);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '2'&&number == 2)
	{
		setPosition(1000, 1000);
    this->changeGold(32);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '3'&&number == 2)
	{
		setPosition(1000, 1000);
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

	
	if (getAttackingTarget() == nullptr)
	{
		stopAllActions();
		moveDirectionByKey(getDir(getPosition(), Vec2(1930, 1430)), Vec2(1930, 1430));
	}
	else {
		attackTo(getAttackingTarget());
	
		}
	return true;
}


