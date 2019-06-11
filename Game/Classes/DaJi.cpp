#include "DaJi.h"


void DaJi::initwithRole(string HeroName, cocos2d::TMXTiledMap* Map, unit*hero1, Vec2 bornpoint,Vector<unit*>* mapUnits,Layer* ammoLayer)
{
	map = Map;
	unitsOnMap = mapUnits;
	auto hero1data = new(unitdata);
	hero1data->initial(HeroName);
	initial(hero1data, Map, mapUnits, ammoLayer);
    daji = hero1;
	daji->changeid(HeroName);
	auto Act = Animate::create(AnimationCache::getInstance()->getAnimation(HeroName + "up_stand"));
	setPosition(bornpoint);
	setScale(0.6);
	runAction(Act);
	if (getid()[1] == 'b') {
		//³õÊ¼»¯¼üÅÌ¼àÌýÆ÷
		auto skillListener = EventListenerKeyboard::create();
		skillListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event * event)
		{
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
			else if (keyCode == EventKeyboard::KeyCode::KEY_1) {
				if (getSkillPoint() == 0) { return true; }
				if (skill_1Level + 1 <= 3)
				{
					skill_1Level += 1;
					changeSkillPoint(-1);
				}
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_2) {
				if (getSkillPoint() == 0) { return true; }
				if (skill_2Level + 1 <= 3)
				{
					skill_2Level += 1;
					changeSkillPoint(-1);
				}
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_3) {
				if (getSkillPoint() == 0) { return true; }
				if (skill_3Level + 1 <= 2)
				{
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
	schedule(schedule_selector(DaJi::cdUpdate), 1.0f);
	schedule(schedule_selector(DaJi::skillFreshUpdate), 1.0f / 45);
}

void DaJi::useSkill_1(unit* target)
{
	sk1Cd_left = sk1Cd[skill_1Level - 1];

	/*auto hitImage = Sprite::create("/button/hitImage.png");
	hitImage->setPosition(target->getPosition()+Vec2(0,10));
	_map->addChild(hitImage, 4,0415);*/

	auto Bird = Sprite::create("Skills/HouYiR1.png");
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(15);
	animFrames.pushBack(SpriteFrame::create("Skills/HouYiR1.png", Rect(0, 0, 1200, 1200)));
	animFrames.pushBack(SpriteFrame::create("Skills/HouYiR2.png", Rect(0, 0, 1200, 1200)));
	animFrames.pushBack(SpriteFrame::create("Skills/HouYiR3.png", Rect(0, 0, 1200, 1200)));
	animFrames.pushBack(SpriteFrame::create("Skills/HouYiR4.png", Rect(0, 0, 1200, 1200)));
	animFrames.pushBack(SpriteFrame::create("Skills/HouYiR5.png", Rect(0, 0, 1200, 1200)));
	animFrames.pushBack(SpriteFrame::create("Skills/HouYiR6.png", Rect(0, 0, 1200, 1200)));
	animFrames.pushBack(SpriteFrame::create("Skills/HouYiR7.png", Rect(0, 0, 1200, 1200)));
	animFrames.pushBack(SpriteFrame::create("Skills/HouYiR8.png", Rect(0, 0, 1200, 1200)));
	animFrames.pushBack(SpriteFrame::create("Skills/HouYiR9.png", Rect(0, 0, 1200, 1200)));
	animFrames.pushBack(SpriteFrame::create("Skills/HouYiR10.png", Rect(0, 0, 1200, 1200)));
	animFrames.pushBack(SpriteFrame::create("Skills/HouYiR11.png", Rect(0, 0, 1200, 1200)));
	animFrames.pushBack(SpriteFrame::create("Skills/HouYiR12.png", Rect(0, 0, 1200, 1200)));
	animFrames.pushBack(SpriteFrame::create("Skills/HouYiR13.png", Rect(0, 0, 1200, 1200)));
	animFrames.pushBack(SpriteFrame::create("Skills/HouYiR14.png", Rect(0, 0, 1200, 1200)));
	animFrames.pushBack(SpriteFrame::create("Skills/HouYiR15.png", Rect(0, 0, 1200, 1200)));
	// create the animation out of the frames
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);
	Bird->setScale(0.4f); Bird->setPosition(daji->getPosition());
	map->addChild(Bird);
	Bird->runAction(RepeatForever::create(animate));
	auto Moving = MoveTo::create(0.5f, target->getPosition());
	auto callbackMove = CallFunc::create([this, Bird, target]() {
		target->changeCurHp(-sk1Damage[skill_1Level - 1]);
		Bird->removeFromParent();
		sk1End();
	});
	auto seq = Sequence::create(Moving, callbackMove, nullptr);
	Bird->runAction(seq);


}
void DaJi::useSkill_2(Vec2 pos)
{
	sk2Cd_left = sk2Cd[skill_2Level - 1];
	daji->setPosition(pos);
	sk2End();
}
void DaJi::useSkill_3()
{
	sk3Cd_left = sk3Cd[skill_3Level - 1];
	sk3 = false;
}

void DaJi::sk1End() {
	sk1 = false;
	return;
}
void DaJi::sk2End() {
	sk2 = false;
	return;
}
void DaJi::sk3End() {

	sk3 = false;
	return;
}

void DaJi::useAlti()
{
}

void DaJi::cdUpdate(float dt)
{
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
		sk3Cd_left -= 1;
		if (sk3Cd_left >= sk3Cd[skill_3Level - 1] - 4) {
			changeCurHp(sk3Damage[skill_3Level - 1]);
			auto me = getPosition();
			auto it = unitsOnMap->begin();
			for (; it != unitsOnMap->end(); ++it) {
				if (((*it)->getid())[1] == getid()[1]&&(*it)->getid()[2]!='T') {
					float dis = ((*it)->getPosition() - this->getPosition()).length();
					if (dis <= 300) {
						(*it)->changeCurHp(sk3Damage[skill_3Level - 1]/2);
					}
				}
			}
		}
		if (sk3Cd_left <= 0) {
			sk3Cd_left = 0;
		}
	}
}

void DaJi::skillFreshUpdate(float dt) {
	if (sk1 || sk2 || sk3) { canReleaseSkill = false; }
	else { canReleaseSkill = true; }
	if (skill_1Level == 0) {

	}
	if (skill_2Level == 0) {

	}
	if (skill_3Level == 0) {

	}
}
