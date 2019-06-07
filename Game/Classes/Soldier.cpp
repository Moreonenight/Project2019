#include "Soldier.h"

#define CENTERX origin.x+visibleSize.width/2
#define CENTERY origin.y+visibleSize.height/2
USING_NS_CC;

bool Soldier::Soldierinit(string Soldiername,cocos2d::TMXTiledMap* Map)
{
	auto data = new(unitdata);
	data->initial(Soldiername);
	auto Act = Animate::create(AnimationCache::getInstance()->getAnimation(Soldiername +"up_stand"));
	setScale(0.6);
	runAction(Act);
	initial(data, Map);
	if (getid()[1] == 'r'&&getid()[2] == '2')
	{
		setPosition(350, 250);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '3')
	{
		setPosition(400, 200);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '2')
	{
		setPosition(550, 450);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '3')
	{
		setPosition(600, 300);
	}
	scheduleUpdate();
	return true;
}


bool Soldier::AttackingJudgeAI()
{

	auto actAttack1 = Animate::create(AnimationCache::getInstance()->getAnimation(getid() + "up_attack"));
	auto actAttack2 = Animate::create(AnimationCache::getInstance()->getAnimation(getid() + "down_attack"));
	auto actAttack3 = Animate::create(AnimationCache::getInstance()->getAnimation(getid() + "left_attack"));
	auto actAttack4 = Animate::create(AnimationCache::getInstance()->getAnimation(getid() + "right_attack"));
	if (getAttackingTarget() == nullptr)
	{
		moveDirectionByKey(getDir(getPosition(), Vec2(1000, 1000)), Vec2(1000, 1000));
	}
	else {
		attackTo(getAttackingTarget());
		auto Direction = getDir(getPosition(), getAttackingTarget()->getPosition());
		switch (Direction)
		{
		case unit::Direction::UP:
			runAction(actAttack1)->setTag(20);
			break;
		case unit::Direction::DOWN:
			runAction(actAttack2)->setTag(20);
			break;
		case unit::Direction::LEFT:
			runAction(actAttack3)->setTag(20);
			break;
		case unit::Direction::RIGHT:
			runAction(actAttack4)->setTag(20);
			break;
		case unit::Direction::NONE:
			break;
		default:
			break;
		}
	}
	return true;
}
