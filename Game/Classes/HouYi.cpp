#include "HouYi.h"

void HouYi::initwithRole(string HeroName, cocos2d::TMXTiledMap* Map,Vec2 bornpoint,Vector<unit*>* mapUnits,Layer* ammoLayer, SocketClient* _socketClient)
{
	_socketClient_=_socketClient;
	auto hero1data = new(unitdata);
	hero1data->initial(HeroName);
	initial(hero1data, Map, mapUnits, ammoLayer);
	map = Map;
	auto Act = Animate::create(AnimationCache::getInstance()->getAnimation(HeroName + "up_stand"));
	setPosition(bornpoint);
	setScale(0.6);
	runAction(Act);
	if (getid()[1] == 'b') {
		//³õÊ¼»¯¼üÅÌ¼àÌýÆ÷
		auto skillListener = EventListenerKeyboard::create();
		skillListener->onKeyPressed = [this,_socketClient](EventKeyboard::KeyCode keyCode, Event * event) 
		{
			if (getDeathCdLeft() > 0) { return true; }
			if (!canRelease()) { return true; }
			if (keyCode == EventKeyboard::KeyCode::KEY_Q) {
				if (sk1Cd_left > 0) { return true; }
				else if (skill_1Level == 0) { return true; }
				else {
					if (_socketClient != NULL) {
						if (_socketClient->is_sent == false) {
							return true;
						}
						else {
							_socketClient->_mutex.lock();
							_socketClient->wcommand.SkillNumber = 1;
							_socketClient->is_sent = false;
							_socketClient->_mutex.unlock();
						}
					}
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
			else if (keyCode == EventKeyboard::KeyCode::KEY_B) {
				if (backCd_left > 0) { return true; }
				else {
					if (_socketClient != NULL) {
						if (_socketClient->is_sent == false) {
							return true;
						}
						else {
							_socketClient->_mutex.lock();
							_socketClient->wcommand.now_back = true;
							_socketClient->is_sent = false;
							_socketClient->_mutex.unlock();
						}
					}
					useBack(); 
				}
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_1) {
				if (getSkillPoint() == 0) { return true; }
				if (skill_1Level + 1 <= 3)
				{
					if (_socketClient != NULL) {
						if (_socketClient->is_sent == false) {
							return true;
						}
						else {
							_socketClient->_mutex.lock();
							_socketClient->wcommand.SkillUpNumber = 1;
							_socketClient->is_sent = false;
							_socketClient->_mutex.unlock();
						}
					}
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/SkillUpLevel.mp3");
					skill_1Level += 1;
					changeSkillPoint(-1);
				}
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_2) {
				if (getSkillPoint() == 0) { return true; }
				if (skill_2Level + 1 <= 3)
				{
					if (_socketClient != NULL) {
						if (_socketClient->is_sent == false) {
							return true;
						}
						else {
							_socketClient->_mutex.lock();
							_socketClient->wcommand.SkillUpNumber = 2;
							_socketClient->is_sent = false;
							_socketClient->_mutex.unlock();
						}
					}
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/SkillUpLevel.mp3");
					skill_2Level += 1;
					changeSkillPoint(-1);
				}
			}
			else if (keyCode == EventKeyboard::KeyCode::KEY_3) {
				if (getSkillPoint() == 0) { return true; }
				if (skill_3Level + 1 <= 2)
				{
					if (_socketClient != NULL) {
						if (_socketClient->is_sent == false) {
							return true;
						}
						else {
							_socketClient->_mutex.lock();
							_socketClient->wcommand.SkillUpNumber = 3;
							_socketClient->is_sent = false;
							_socketClient->_mutex.unlock();
						}
					}
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
	schedule(schedule_selector(HouYi::cdUpdate), 1.0f);
	schedule(schedule_selector(HouYi::skillFreshUpdate), 1.0f/45);
	schedule(schedule_selector(HouYi::AIFunc), 0.1f);

}


void HouYi::useSkill_1()
{
	sk1Cd_left = sk1Cd[skill_1Level-1];
	changeDamage(sk1Damage[skill_1Level - 1]);
	mana->changeCurMana(-100);
	sk1 = false;
}
void HouYi::useSkill_2(Vec2 pos)
{
	setPosition(pos);
	sk2Cd_left = sk2Cd[skill_2Level-1];
	mana->changeCurMana(-100);
	sk2End();
}
void HouYi::useSkill_3(unit* target)
{
	sk3Cd_left = sk3Cd[skill_3Level-1];
	mana->changeCurMana(-100);

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
	Bird->setScale(0.4f); Bird->setPosition(getPosition());
	map->addChild(Bird);
	Bird->runAction(RepeatForever::create(animate));
	auto Moving = MoveTo::create(0.5f, target->getPosition());
	auto callbackMove = CallFunc::create([this, Bird, target]() {
		target->getDamage(sk3Damage[skill_3Level - 1]+ getCurDamage()/10,getid());
		Bird->removeFromParent();
		sk3End();
	});
	auto seq = Sequence::create(Moving, callbackMove, nullptr);
	Bird->runAction(seq);
}
void HouYi::useBack() {
	backCd_left = 3;
	stopAllActions();
	auto Singleton = AnimationCache::getInstance();
	runAction(Animate::create(Singleton->getAnimation(getid() + "down_stand")))->setTag(10);
	auto backImage = Sprite::create("Skills/back1.png");
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(14);
	animFrames.pushBack(SpriteFrame::create("Skills/back1.png", Rect(0, 0, 380, 380)));
	animFrames.pushBack(SpriteFrame::create("Skills/back2.png", Rect(0, 0, 380, 380)));
	animFrames.pushBack(SpriteFrame::create("Skills/back3.png", Rect(0, 0, 380, 380)));
	animFrames.pushBack(SpriteFrame::create("Skills/back4.png", Rect(0, 0, 380, 380)));
	animFrames.pushBack(SpriteFrame::create("Skills/back5.png", Rect(0, 0, 380, 380)));
	animFrames.pushBack(SpriteFrame::create("Skills/back6.png", Rect(0, 0, 380, 380)));
	animFrames.pushBack(SpriteFrame::create("Skills/back7.png", Rect(0, 0, 380, 380)));
	animFrames.pushBack(SpriteFrame::create("Skills/back8.png", Rect(0, 0, 380, 380)));
	animFrames.pushBack(SpriteFrame::create("Skills/back9.png", Rect(0, 0, 380, 380)));
	animFrames.pushBack(SpriteFrame::create("Skills/back10.png", Rect(0, 0, 380, 380)));
	animFrames.pushBack(SpriteFrame::create("Skills/back11.png", Rect(0, 0, 380, 380)));
	animFrames.pushBack(SpriteFrame::create("Skills/back12.png", Rect(0, 0, 380, 380)));
	animFrames.pushBack(SpriteFrame::create("Skills/back13.png", Rect(0, 0, 380, 380)));
	animFrames.pushBack(SpriteFrame::create("Skills/back14.png", Rect(0, 0, 380, 380)));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);
	backImage->setPosition(getPosition() + Vec2(0, 90));
	backImage->setOpacity(200);
	backImage->setAnchorPoint(Vec2(0.5, 0.5));
	backImage->runAction(RepeatForever::create(animate));
	map->addChild(backImage, 0, 8885);
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
	Bird->setScale(0.4f); Bird->setPosition(getPosition());
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
void HouYi::backEnd()
{
	backCd_left = 0;
	if (map->getChildByTag(8885)) {
		map->removeChildByTag(8885);
	}
	return;
}


void HouYi::useAlti()
{
}

void HouYi::cdUpdate(float dt)
{
	if (sk1Cd_left > 0) { 
		sk1Cd_left -= 1; 
		if (sk1Cd_left == 3) { changeDamage((-1)*sk1Damage[skill_1Level - 1]); sk1End(); }
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
	if (deathCd_left > 0) {
		deathCd_left -= 1;
	}
	if (backCd_left > 0) {
		if (backCd_left == 1) { setPosition(getSpawnPoint()); backEnd(); }
		backCd_left -= 1;
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