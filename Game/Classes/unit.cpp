#include "unit.h"
#include "ammo.h"



unit::unit(unitdata &unitdata)
{
	data = &unitdata;
	hp->initial(this); addChild(hp, 0);
	Velocity = data->getVelocity();
	level = 1; damage = data->getDamage();
	gold = 0; ASPD = data->getASPD(); canAttack = true;
	id = data->getUnitid(); dpm = data->getDpm();
	createWithSpriteFrameName(id + "front_stand");
	setPosition(data->getPosition());
	Scheduler::schedule(schedule_selector(unit::freshCanAttack), 1.0f/ASPD);
}


unit::~unit()
{

}



void unit::stop()
{
}

void unit::moveTo(cocos2d::Vec2 destination)
{
	float angle = CC_RADIANS_TO_DEGREES((destination-this->getPosition()).getAngle());
	auto aniCache = AnimationCache::getInstance();
	if (angle <= 45.0&&angle > -45.0) runAction(Animate::create(aniCache->getAnimation(id + "right_walk")));
	else if(angle>45.0&&angle <=135.0) runAction(Animate::create(aniCache->getAnimation(id + "back_walk")));
	else if(angle>135.0||angle<=-135.0) runAction(Animate::create(aniCache->getAnimation(id + "left_walk")));
	else if (angle > -135.0&&angle <= -45.0)runAction(Animate::create(aniCache->getAnimation(id + "front_walk")));
	runAction(MoveTo::create((((destination - getPosition()).length()) / Velocity.length()),destination));
}

Sprite *unit::attack(unit * target)//返回攻击产生的弹道对象指针，可以把它加到layer中去。
{
	if (canAttack == false) return NULL;
	stop();
	auto aniCache = AnimationCache::getInstance();
	canAttack == false;
	float angle = CC_RADIANS_TO_DEGREES((target->getPosition() - getPosition()).getAngle());
	if (angle <= 45.0&&angle > -45.0) runAction(Animate::create(aniCache->getAnimation(id + "right_attack")));
	else if (angle > 45.0&&angle <= 135.0) runAction(Animate::create(aniCache->getAnimation(id + "back_attack")));
	else if (angle > 135.0 || angle <= -135.0) runAction(Animate::create(aniCache->getAnimation(id + "left_attack")));
	else if (angle > -135.0&&angle <= -45.0)runAction(Animate::create(aniCache->getAnimation(id + "front_attack")));
	
	//runAction();
	ammo *amo;
	amo->createAnAmmo(this, target);
	return amo;
}

void unit::attackTo(unit * target)
{
	Vec2 destination = target->getPosition();
	if ((getPosition() - destination).length() > (data->getAttackRange())) this->moveTo(destination);
	else attack(target);
}

void unit::attackTo(Vec2 destination)
{
}

void unit::die()
{
}


