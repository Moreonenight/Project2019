#include "YaSe.h"


void YaSe::initwithRole(string HeroName, cocos2d::TMXTiledMap* Map, unit* hero1, Vec2 bornpoint, Vector<unit*>* mapUnits,Layer* ammoLayer)

{

	auto hero1data = new(unitdata);
	hero1data->initial(HeroName);
	initial(hero1data, Map, mapUnits, ammoLayer);
  yase = hero1;
	yase->changeid(HeroName);
	auto Act = Animate::create(AnimationCache::getInstance()->getAnimation(HeroName + "up_stand"));
	setPosition(bornpoint);
	setScale(0.6);
	runAction(Act);
	scheduleUpdate();
}

void YaSe::sk1End(float dt) {
	yase->changeDamage((-1)*sk1Damage[skill_1Level]);
	return;
}

void YaSe::useskill_1()
{
	yase->changeDamage(sk1Damage[skill_1Level]);
	//Scheduler::schedule(schedule_selector(HouYi::sk1End), this, 5.0, 0, 0, 0);
}


void YaSe::useSkill_2(Vec2 pos)
{

}

void YaSe::useAlti()
{
}
