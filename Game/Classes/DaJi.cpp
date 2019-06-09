#include "DaJi.h"


void DaJi::initwithRole(string HeroName, cocos2d::TMXTiledMap* Map, unit*hero1, Vec2 bornpoint,Vector<unit*>* mapUnits,Layer* ammoLayer)
{
	auto hero1data = new(unitdata);
	hero1data->initial(HeroName);
	initial(hero1data, Map, mapUnits, ammoLayer);
    daji = hero1;
	daji->changeid(HeroName);
	auto Act = Animate::create(AnimationCache::getInstance()->getAnimation(HeroName + "up_stand"));
	setPosition(bornpoint);
	setScale(0.6);
	runAction(Act);
	scheduleUpdate();
}

void DaJi::sk1End(float dt) {
	daji->changeDamage((-1)*sk1Damage[skill_1Level]);
	return;
}

void DaJi::useskill_1()
{
	daji->changeDamage(sk1Damage[skill_1Level]);
	//Scheduler::schedule(schedule_selector(HouYi::sk1End), this, 5.0, 0, 0, 0);
}


void DaJi::useSkill_2(Vec2 pos)
{

}

void DaJi::useAlti()
{
}
