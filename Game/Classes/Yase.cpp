#include "YaSe.h"


void YaSe::initwithRole(string HeroName, cocos2d::TMXTiledMap* Map, Vec2 bornpoint, Vector<unit*>* mapUnits,Layer* ammoLayer)

{
	map = Map;
	unitsOnMap = mapUnits;
	auto hero1data = new(unitdata);
	hero1data->initial(HeroName);
	initial(hero1data, Map, mapUnits, ammoLayer);
	auto Act = Animate::create(AnimationCache::getInstance()->getAnimation(HeroName + "up_stand"));
	setPosition(bornpoint);
	setScale(0.6);
	runAction(Act);
	if (getid()[1] == 'b') {
		//³õÊ¼»¯¼üÅÌ¼àÌýÆ÷
		auto skillListener = EventListenerKeyboard::create();
		skillListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event * event)
		{
			if (getDeathCdLeft() > 0) { return true; }
			if (!canRelease()) { return true; }
			if (keyCode == EventKeyboard::KeyCode::KEY_Q) {
				if (sk1Cd_left > 0) { return true; }
				else if (skill_1Level == 0) { return true; }
				else {
					sk1 = true;
				}
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
				if (sk2Cd_left > 0) { return true; }
				else if (skill_2Level == 0) { return true; }
				else {
					sk2 = true;
				}
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_E) {
				if (sk3Cd_left > 0) { return true; }
				else if (skill_3Level == 0) { return true; }
				else {
					sk3 = true;
					useSkill_3();
				}
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_B) {
				if (backCd_left > 0) { return true; }
				else { backCd_left = 3; }
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_1) {
				if (getSkillPoint() == 0) { return true; }
				if (skill_1Level + 1 <= 3)
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/SkillUpLevel.mp3");
					skill_1Level += 1;
					changeSkillPoint(-1);
				}
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_2) {
				if (getSkillPoint() == 0) { return true; }
				if (skill_2Level + 1 <= 3)
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/SkillUpLevel.mp3");
					skill_2Level += 1;
					changeSkillPoint(-1);
				}
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_3) {
				if (getSkillPoint() == 0) { return true; }
				if (skill_3Level + 1 <= 2)
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/SkillUpLevel.mp3");
					skill_3Level += 1;
					changeSkillPoint(-1);
				}
			}

		};
		skillListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event * event) {
			return true;
		};
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(skillListener, this);
	}
	scheduleUpdate();
	schedule(schedule_selector(YaSe::cdUpdate), 1.0f);
	schedule(schedule_selector(YaSe::skillFreshUpdate), 1.0f / 45);
	schedule(schedule_selector(YaSe::AIFunc), 0.1f);
}

void YaSe::useSkill_1(Vec2 startPoint, unit* target)
{
	sk1Cd_left = sk1Cd[skill_1Level - 1];
	runAction(Sequence::createWithTwoActions(
		MoveTo::create(0.2f, target->getPosition()),
		MoveTo::create(0.2f, startPoint))
	);
	target->getDamage(sk1Damage[skill_1Level - 1]+getCurDamage()/10,getid());
	mana->changeCurMana(-100);
	sk1End();
}
void YaSe::useSkill_2(Vec2 pos)
{
	setPosition(pos);
	sk2Cd_left = sk2Cd[skill_2Level - 1];
	mana->changeCurMana(-100);
	sk2End();
}
void YaSe::useSkill_3()
{
	sk3Cd_left = sk3Cd[skill_3Level - 1];
	runAction(RotateBy::create(0.2f, 360));
	mana->changeCurMana(-100);
	sk3 = false;
}

void YaSe::sk1End() {
	sk1 = false;
	return;
}
void YaSe::sk2End() {
	sk2 = false;
	return;
}
void YaSe::sk3End() {

	sk3 = false;
	return;
}
//更新
void YaSe::cdUpdate(float dt)
{
	//因为亚瑟要旋转
	if(this->getRotation()!=0) setRotation(0);
	if (sk1Cd_left > 0) {
		sk1Cd_left -= 1;
		if (sk1Cd_left <= 0) {
			sk1Cd_left = 0;
		}
	}

	if (sk2Cd_left > 0) {
		sk2Cd_left -= 1;
		if (sk2Cd_left <= 0) {
			sk2Cd_left = 0;
		}
	}
	if (sk3Cd_left > 0) {
		if (sk3Cd_left >= sk3Cd[skill_3Level - 1] - 2) {
			auto me = getPosition();
			auto units = *unitsOnMap;
			auto it = units.begin();
			for (; it < units.end(); ++it) {
				if (((*it)->getid())[1]!= getid()[1]) {
					float dis = ((*it)->getPosition() - this->getPosition()).length();
					if (dis <= 300) {
						(*it)->getDamage(sk3Damage[skill_3Level - 1] + getCurDamage() / 15,getid());
					}
				}
			}
		}
		sk3Cd_left -= 1;
		if (sk3Cd_left <= 0) {
			sk3Cd_left = 0;
		}
	}
	if (deathCd_left > 0) {
		deathCd_left -= 1;
	}
	if (backCd_left > 0) {
		if (backCd_left == 1) { setPosition(getSpawnPoint()); }
		backCd_left -= 1;
	}
}

void YaSe::skillFreshUpdate(float dt) {
	if (sk1 || sk2 || sk3) { canReleaseSkill = false; }
	else { canReleaseSkill = true; }
	if (skill_1Level == 0) {

	}
	if (skill_2Level == 0) {

	}
	if (skill_3Level == 0) {

	}
}
void YaSe::useAlti()
{
}

