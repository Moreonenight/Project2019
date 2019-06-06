#include "HouYi.h"

void HouYi::initial()
{
	houyiData = new(unitdata);
	houyiData->initial(string("HouYi"));
	houyi = unit::create();
	//houyi->initial(houyiData);
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("HouYi/ammo.plist");
}

void HouYi::sk1End(float dt) {
	houyi->changeDamage((-1)*sk1Damage[skill_1Level]);
	return;
}

void HouYi::useskill_1()
{
	houyi->changeDamage(sk1Damage[skill_1Level]);
	//Scheduler::schedule(schedule_selector(HouYi::sk1End), this, 5.0, 0, 0, 0);
}


void HouYi::useSkill_2(Vec2 pos)
{

}

void HouYi::useAlti()
{
}
