#include "Tower.h"
USING_NS_CC;
bool Tower::InitWithRole(string Towername, cocos2d::TMXTiledMap* Map, Vector<unit*>* mapUnits,Layer* ammoLayer)
{
	auto data = new(unitdata);
	ChangeAlreadydead(false);
	data->initial(Towername);
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(Towername+"/stand.plist");
	this->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Towername+".png"));
	initial(data, Map, mapUnits, ammoLayer);
	if (getid()[1] == 'r'&&getid()[2] == '1')
	{
		setScale(0.5);
		setPosition(1450, 1050);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '2')
	{
		setScale(0.5);
		setPosition(1700, 1350);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '3')
	{
		setPosition(1930, 1430);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '1')
	{
		setScale(0.5);
		setPosition(900, 650);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '2')
	{
		setScale(0.5);
		setPosition(550, 350);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '3')
	{
		setPosition(300, 180);
	}
	scheduleUpdate();
	return true;
}
bool Tower::AttackingJudgeAI() {

	if (getAttackingTarget() != nullptr)
	{
		if (LastAttackingTarget == nullptr)
		{
			attackTo(getAttackingTarget());
			LastAttackingTarget = getAttackingTarget();
		}
		else if(LastAttackingTarget != getAttackingTarget())
		{
			attackTo(getAttackingTarget());
			LastAttackingTarget = getAttackingTarget();
		}
		else if(LastAttackingTarget == getAttackingTarget())
		{
			changeDamage(10);
			attackTo(getAttackingTarget());
			LastAttackingTarget = getAttackingTarget();
		}
		
	}
	else
	{
		setDamage(getInitDamage());
	}
	return true;
}






