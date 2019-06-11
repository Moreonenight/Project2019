#pragma once
#include "unit.h"
#include "SimpleAudioEngine.h"
class YaSe:public unit
{
private:
	unit* yase;
	unitdata* yaseData;
	cocos2d::TMXTiledMap* map;
	Vector<unit*>* unitsOnMap;
	int level;
	int skill_1Level;
	int skill_2Level;
	int skill_3Level;
	int sk1Damage[6] = { 2000,240,280,320,360,400 };
	int sk1Cd[6] = { 8,7,6,6,5,5 };
	int sk2Damage[6] = { 300,350,400,450,500,550 };
	int sk2Cd[6] = { 8,7,6,6,5,5 };
	int sk3Damage[3] = { 2000,875,1050 };
	int sk3Cd[3] = { 5,40,35 };
	//表示技能是否开启
	bool sk1 = false;
	bool sk2 = false;
	bool sk3 = false;
	int sk1Cd_left = 0;
	int sk2Cd_left = 0;
	int	sk3Cd_left = 0;
	//表示当前能否释放其他技能
	bool canReleaseSkill = true;
public:
	void initwithRole(string HeroName, cocos2d::TMXTiledMap* Map, unit* hero1, Vec2 bornpoint, Vector<unit*>* mapUnits, Layer* ammoLayer);
	unit* getUnit() { return yase; }
	void useSkill_1(Vec2 startPoint, unit* target);
	void useSkill_2(Vec2 pos);
	void useSkill_3();
	void sk1End();
	void sk2End();
	void sk3End();
	void sk3End(Vec2 Target);
	void useAlti();
	//技能相关
	inline bool isReleasing() { return sk1 || sk2 || sk3; }
	inline bool getSk1() { return sk1; }
	inline bool getSk2() { return sk2; }
	inline bool getSk3() { return sk3; }
	inline int getSk1CdLeft() { return sk1Cd_left; }
	inline int getSk2CdLeft() { return sk2Cd_left; }
	inline int getSk3CdLeft() { return sk3Cd_left; }
	inline int getSk1Level() { return skill_1Level; }
	inline int getSk2Level() { return skill_2Level; }
	inline int getSk3Level() { return skill_3Level; }
	inline bool canRelease() { return canReleaseSkill; }
	inline void changeCanRelease(bool now) { canReleaseSkill = now; }

	//游戏刷新
	void cdUpdate(float dt);
	void skillFreshUpdate(float dt);

	void update(float dt) {
		if (hp->getCur() <= 1) die();
		hp->follow(getPosition());
		exp->follow(getPosition());
		if (exp->getLevel() > level)
		{
			level = exp->getLevel();
			auto Upgrade = Sprite::create("Upgrade/gg-tx-025-0013.png");
			Vector<SpriteFrame*> animFrames;
			animFrames.reserve(13);
			animFrames.pushBack(SpriteFrame::create("Upgrade/gg-tx-025-0001.png", Rect(0, 0, 850, 800)));
			animFrames.pushBack(SpriteFrame::create("Upgrade/gg-tx-025-0002.png", Rect(0, 0, 850, 800)));
			animFrames.pushBack(SpriteFrame::create("Upgrade/gg-tx-025-0003.png", Rect(0, 0, 850, 800)));
			animFrames.pushBack(SpriteFrame::create("Upgrade/gg-tx-025-0004.png", Rect(0, 0, 850, 800)));
			animFrames.pushBack(SpriteFrame::create("Upgrade/gg-tx-025-0005.png", Rect(0, 0, 850, 800)));
			animFrames.pushBack(SpriteFrame::create("Upgrade/gg-tx-025-0006.png", Rect(0, 0, 850, 800)));
			animFrames.pushBack(SpriteFrame::create("Upgrade/gg-tx-025-0007.png", Rect(0, 0, 850, 800)));
			animFrames.pushBack(SpriteFrame::create("Upgrade/gg-tx-025-0008.png", Rect(0, 0, 850, 800)));
			animFrames.pushBack(SpriteFrame::create("Upgrade/gg-tx-025-0009.png", Rect(0, 0, 850, 800)));
			animFrames.pushBack(SpriteFrame::create("Upgrade/gg-tx-025-0010.png", Rect(0, 0, 850, 800)));
			animFrames.pushBack(SpriteFrame::create("Upgrade/gg-tx-025-0011.png", Rect(0, 0, 850, 800)));
			animFrames.pushBack(SpriteFrame::create("Upgrade/gg-tx-025-0012.png", Rect(0, 0, 850, 800)));
			animFrames.pushBack(SpriteFrame::create("Upgrade/gg-tx-025-0013.png", Rect(0, 0, 850, 800)));
			Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
			Animate* animate = Animate::create(animation);
			Upgrade->setScale(0.5f); Upgrade->setPosition(yase->getPosition());
			map->addChild(Upgrade); auto Playit = Repeat::create(animate, 1.0f);
			auto callback = CallFunc::create([this, Upgrade]() {
				Upgrade->removeFromParent();
			});
			auto seq = Sequence::create(Playit, callback, nullptr);
			yase->runAction(seq);
		}
		auto it = ammosOnWay.begin();
		for (; it < ammosOnWay.end(); it++) {
			auto Dis = (this->getPosition() - (*it)->getPosition()).length();
			auto id1 = this->getid(); auto id2 = (*it)->getid();
			if (Dis < 150 && id1[1] != id2[1]) {
				auto Damage = (*it)->getDamage();
				this->getDamage(Damage, (*it)->getid());
				(*it)->removeFromParentAndCleanup(1);
				//(*it)->setVisible(0);
				//(*it)->setPosition(-200.0, -200.0);
				if (it == (ammosOnWay.end() - 1)) { ammosOnWay.clear(); break; }
				else it = ammosOnWay.erase(it);
			}
			else {
				(*it)->changeTargetPosition(getPosition());
			}
		}
		//回城回血
		if ((getPosition() - getSpawnPoint()).length() <= 200) {
			fullHp();
		}

		if (this->canAttack == 1)return;
		else { this->canAttack = 1; return; }

	}

	virtual int getDamage(int delta, std::string fromId) {
		if (hp->getCur() < delta) {
			die();
			//得到击杀者unit*添加奖励
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/kill.mp3");
			changeDeath(1);
			if (fromId[0] == 'H') {
				unit* killUnit = getUnitWithId(fromId);
				if (killUnit != nullptr) {
					killUnit->changeGold(float(getGold())*0.3 > 150 ? float(getGold())*0.3 : 150);
					killUnit->addCurExp((getExp()->getMaxExp()) * 2 / 10);
					killUnit->changeKillHero(1);
				}
			}
			this->setPosition(Vec2(270, 90));
		}
		hp->changeCur((-delta)*(float)((100.0 - this->getDefenceOfPhysical()) / 100.0));
		return hp->getCur();
	}
	CREATE_FUNC(YaSe);
};