#include "HouYi.h"

void HouYi::initwithRole(string HeroName, cocos2d::TMXTiledMap* Map, unit* hero1,Vec2 bornpoint,Vector<unit*>* mapUnits,Layer* ammoLayer)
{
	auto hero1data = new(unitdata);
	hero1data->initial(HeroName);
	initial(hero1data, Map, mapUnits, ammoLayer);
	map = Map;
	houyi = hero1;
	houyi->changeid(HeroName);
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
					useSkill_1();
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
				}
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_1) {
				if (getSkillPoint() == 0) { return true; }
				skill_1Level += 1;
				changeSkillPoint(-1);
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_2) {
				if (getSkillPoint() == 0) { return true; }
				skill_2Level += 1;
				changeSkillPoint(-1);
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_3) {
				if (getSkillPoint() == 0) { return true; }
				skill_3Level += 1;
				changeSkillPoint(-1);
			}

		};
		skillListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event * event) {
			return true;
		};
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(skillListener, this);
	}
	scheduleUpdate();
	schedule(schedule_selector(HouYi::cdUpdate), 1.0f);
	schedule(schedule_selector(HouYi::skillFreshUpdate), 1.0f/45);
}


void HouYi::useSkill_1()
{
	sk1Cd_left = sk1Cd[skill_1Level-1];

	houyi->changeDamage(sk1Damage[skill_1Level - 1]);
	sk1End();
	

	
	//schedule(schedule_selector(HouYi::sk1End), this, 5.0f, 0, 0, 0);
}
void HouYi::useSkill_2(Vec2 pos)
{
	houyi->setPosition(pos);
	sk2Cd_left = sk2Cd[skill_2Level-1];
	sk2End();
}
void HouYi::useSkill_3(unit* target)
{
	sk3Cd_left = sk3Cd[skill_3Level-1];

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
	Bird->setScale(0.4f); Bird->setPosition(houyi->getPosition());
	map->addChild(Bird);
	Bird->runAction(RepeatForever::create(animate));
	auto Moving = MoveTo::create(0.5f, target->getPosition());
	auto callbackMove = CallFunc::create([this, Bird, target]() {
		target->changeCurHp(-sk3Damage[skill_3Level - 1]);
		Bird->removeFromParent();
		sk3End();
	});
	auto seq = Sequence::create(Moving, callbackMove, nullptr);
	Bird->runAction(seq);

	
}

void HouYi::sk1End() {
	sk1 = false;
	return;
}
void HouYi::sk2End() {
	sk2 = false;
	return;
}
void HouYi::sk3End() {

	sk3 = false;
	return;
}
void HouYi::sk3End(Vec2 Target) {

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
	Bird->setScale(0.4f); Bird->setPosition(houyi->getPosition());
	map->addChild(Bird);
	Bird->runAction(RepeatForever::create(animate));
	auto Moving = MoveTo::create(0.5f, Target);
	auto callbackMove = CallFunc::create([this, Bird, Target]() {
		Bird->removeFromParent();
		sk3End();
	});
	auto seq = Sequence::create(Moving, callbackMove, nullptr);
	Bird->runAction(seq);

	sk3 = false;
	return;
}

void HouYi::useAlti()
{
}

void HouYi::cdUpdate(float dt)
{
	if (sk1Cd_left > 0) { 
		sk1Cd_left -= 1; 
		if (sk1Cd_left == 3) { houyi->changeDamage((-1)*sk1Damage[skill_1Level-1]); }
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
		if (sk3Cd_left == sk3Cd[skill_3Level-1] - 1) { _map->removeChildByTag(0415); }
		if (sk3Cd_left <= 0) {
			sk3Cd_left = 0;
		}
	}
}

void HouYi::skillFreshUpdate(float dt) {
	if (sk1 || sk2 || sk3) { canReleaseSkill = false; }
	else{ canReleaseSkill = true; }
	if (skill_1Level == 0) {
		
	}
	if (skill_2Level == 0) {

	}
	if (skill_3Level == 0) {

	}
}