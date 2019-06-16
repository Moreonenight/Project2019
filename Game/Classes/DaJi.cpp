#include "DaJi.h"


void DaJi::initwithRole(string HeroName, cocos2d::TMXTiledMap* Map, Vec2 bornpoint,Vector<unit*>* mapUnits,Layer* ammoLayer, SocketClient* _socketClient)
{
	_socketClient_ = _socketClient;
	map = Map;
	unitsOnMap = mapUnits;
	auto hero1data = new(unitdata);
	hero1data->initial(HeroName);
	initial(hero1data, Map, mapUnits, ammoLayer);
	auto Act = Animate::create(AnimationCache::getInstance()->getAnimation(HeroName + "up_stand"));
	setPosition(bornpoint);
	setScale(0.6);
	runAction(Act);
	bool key_number = false;
	if (_socketClient != NULL) {
		if (_socketClient_->playerNumber == RED_PLAYER) {
			if (getid()[1] == 'r')(key_number = true);
		}
		else
		{
			if (getid()[1] == 'b')(key_number = true);
		}
	}
	else {
		if (getid()[1] == 'b')(key_number = true);
	}
	if (key_number == true) {
		auto skillListener = EventListenerKeyboard::create();
		skillListener->onKeyPressed = [this,_socketClient](EventKeyboard::KeyCode keyCode, Event * event)
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
				if (_socketClient != NULL) {
					if (_socketClient->is_sent == false) {
						return true;
					}
					else {
						_socketClient->_mutex.lock();
						_socketClient->wcommand.SkillNumber = 3;
						_socketClient->is_sent = false;
						_socketClient->_mutex.unlock();
					}
				}
				useSkill_3();
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
	schedule(schedule_selector(DaJi::cdUpdate), 1.0f);
	schedule(schedule_selector(DaJi::skillFreshUpdate), 1.0f / 45);
	schedule(schedule_selector(DaJi::AIFunc), 0.1f);
}

void DaJi::AIFunc(float dt) {
	if (isAI() == false) return;
	if (deathCd_left > 0) { stopAllActions(); return; }
	float blood = (getHp()->getCur()) / (float)(getHp()->getMax());
	auto aow = &ammosOnWay;
	if (getSkillPoint() != 0) {
		if (skill_1Level < 3)
		{
			skill_1Level++;
			changeSkillPoint(-1);
		}
		else if (skill_2Level < 3) {
			skill_2Level++;
			changeSkillPoint(-1);
		}
		else if (skill_3Level < 2) {
			skill_3Level++;
			changeSkillPoint(-1);
		}
	}

	if (blood <= 0.1) {
		if (sk2Cd_left == 0 && skill_2Level) {
			useSkill_2(getPosition() + (getSpawnPoint() - getPosition()).getNormalized() * 350);
		}
		else {
			moveDirectionByKey(getDir(getPosition(), getSpawnPoint()), getSpawnPoint());
		}
	}
	else {
		string targetid = "\0";
		unit* target  = NULL;
		float minlength = 65535.0;

		vector<ammo*>::iterator ait = (*aow).begin();
		for (; ait < aow->end(); ait++) {//先看有没有敌方英雄攻击自己
			 if((*ait)->getid()[0] == 'T') {//看有没被塔砸
				 moveDirectionByKey(getDir(getPosition(), getSpawnPoint()), getSpawnPoint());
			}
			else if((*ait)->getid()[0] == 'H' ) {
				targetid = (*ait)->getid();
				break;
			}
		}
		auto units = *unitsOnMap;
		Vector<unit*>::iterator uit = units.begin();

		for (; uit < units.end(); uit++) {
			if ((*uit)->getid()[0] == 'H')//先判断英雄
			{
				if ((*uit)->getid()[1] != this->getid()[1]) {//敌方英雄
					if (targetid == (*uit)->getid()) {//假如有地方英雄那么有1技能就用
						if (sk1Cd_left == 0) {
							useSkill_1((*uit));
							return;
						}
						else//没技能就打
						{
							attackTo((*uit));
							return;
						}
					}
					else if (((*uit)->getPosition() - this->getPosition()).length() <= getAttackRange() - 100)//判断身边有地方英雄就打
					{
						attackTo((*uit));
						return;
					}
				}
				else {//友方英雄
					if (((*uit)->getHp()->getCur()) / (float)(*uit)->getHp()->getMax() <= 0.3) {
						if (((*uit)->getPosition() - getPosition()).length() <= 150) {//血量小就去奶
							useSkill_3();
							return;
						}
						else if (((*uit)->getPosition() - getPosition()).length() <= 600) {//奶不到又不太远就靠过去
							moveDirectionByKey(getDir(getPosition(), (*uit)->getPosition()), (*uit)->getPosition());
							return;
						}
					}
				}
			}
			else if ((*uit)->getid()[0] == 'B') {//小兵
				if ((*uit)->getid()[1] != this->getid()[1]) {//敌方小兵 判断最近的小兵，打过去
					if (((*uit)->getPosition() - this->getPosition()).length() <= minlength) {
						target = (*uit);
					}
				}
				else {//友方小兵
					;
				}
			}
			else if ((*uit)->getid()[0] == 'T') {//塔
				if ((*uit)->getid()[1] != getid()[1]) {//敌方塔
					if (((*uit)->getPosition() - getPosition()).length() < minlength) {
						target = *uit;
					}
				}
				else {//友方塔
					if ((*uit)->IsGettingAttack()) {
						moveDirectionByKey(getDir(getPosition(), (*uit)->getPosition()), (*uit)->getPosition());
						return;
					}
				}

			}
		}
		if (target != nullptr)
			{ 		
				attackTo(target);
				return;
			}
		else {
			return;
		}
	}
}

void DaJi::useSkill_1(unit* target)
{
	sk1Cd_left = sk1Cd[skill_1Level - 1];

	/*auto hitImage = Sprite::create("/button/hitImage.png");
	hitImage->setPosition(target->getPosition()+Vec2(0,10));
	_map->addChild(hitImage, 4,0415);*/

	auto Bird = Sprite::create("Skills/DaJiQ1.png");
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(15);
	animFrames.pushBack(SpriteFrame::create("Skills/DaJiQ1.png", Rect(0, 0, 80, 80)));
	animFrames.pushBack(SpriteFrame::create("Skills/DaJiQ2.png", Rect(0, 0, 80, 80)));
	animFrames.pushBack(SpriteFrame::create("Skills/DaJiQ3.png", Rect(0, 0, 80, 80)));
	animFrames.pushBack(SpriteFrame::create("Skills/DaJiQ4.png", Rect(0, 0, 80, 80)));
	animFrames.pushBack(SpriteFrame::create("Skills/DaJiQ5.png", Rect(0, 0, 80, 80)));
	animFrames.pushBack(SpriteFrame::create("Skills/DaJiQ6.png", Rect(0, 0, 80, 80)));
	animFrames.pushBack(SpriteFrame::create("Skills/DaJiQ7.png", Rect(0, 0, 80, 80)));
	animFrames.pushBack(SpriteFrame::create("Skills/DaJiQ8.png", Rect(0, 0, 80, 80)));
	animFrames.pushBack(SpriteFrame::create("Skills/DaJiQ9.png", Rect(0, 0, 80, 80)));
	animFrames.pushBack(SpriteFrame::create("Skills/DaJiQ10.png", Rect(0, 0, 80, 80)));
	animFrames.pushBack(SpriteFrame::create("Skills/DaJiQ11.png", Rect(0, 0, 80, 80)));
	animFrames.pushBack(SpriteFrame::create("Skills/DaJiQ12.png", Rect(0, 0, 80, 80)));
	animFrames.pushBack(SpriteFrame::create("Skills/DaJiQ13.png", Rect(0, 0, 80, 80)));
	animFrames.pushBack(SpriteFrame::create("Skills/DaJiQ14.png", Rect(0, 0, 80, 80)));
	animFrames.pushBack(SpriteFrame::create("Skills/DaJiQ15.png", Rect(0, 0, 80, 80)));
	// create the animation out of the frames
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);
	Bird->setScale(1.0f); Bird->setPosition(getPosition()); Bird->setAnchorPoint(Vec2(0.5, 0.5));
	map->addChild(Bird);
	Bird->runAction(RepeatForever::create(animate));
	auto Moving = MoveTo::create(0.5f, target->getPosition());
	auto callbackMove = CallFunc::create([this, Bird, target]() {
		target->getDamage(sk1Damage[skill_1Level - 1]+getCurDamage()/10,getid());
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
	sk3End();
}

void DaJi::useBack()
{
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
	backImage->setPosition(getPosition()+Vec2(0,90)); 
	backImage->setOpacity(200);
	backImage->setAnchorPoint(Vec2(0.5, 0.5));
	backImage->runAction(RepeatForever::create(animate));
	map->addChild(backImage,0,8885);
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
void DaJi::backEnd() {
	backCd_left = 0;
	if (map->getChildByTag(8885)) {
		map->removeChildByTag(8885);
	}
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
	if (deathCd_left > 0) {
		deathCd_left -= 1;
	}
	if (backCd_left > 0) {
		if (backCd_left == 1) { setPosition(getSpawnPoint()); backEnd(); }
		backCd_left -= 1;
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
