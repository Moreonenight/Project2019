#pragma once
#include "unit.h"

class HouYi :public unit
{
private:
	unit* houyi;
	unitdata* houyiData;
	int level=1;
	int skill_1Level=0;
	int skill_2Level=0;
	int skill_3Level=0;
	int sk1Damage[6] = { 200,240,280,320,360,400 };
	int sk1Cd[6] = { 8,7,6,5,5,4 };
	int sk2Damage[6] = { 300,350,400,450,500,550 };
	int sk2Cd[6] = { 8,7,6,5,5,4 };
	int sk3Damage[3] = { 7000,875,1050 };
	int sk3Cd[3] = { 8,40,35 };
	//表示技能是否开启
	bool sk1 = false;
	bool sk2 = false;
	bool sk3=  false;
	int sk1Cd_left = 0;
	int sk2Cd_left = 0;
	int	sk3Cd_left = 0;
	//表示当前能否释放其他技能
	bool canReleaseSkill = true;
public:
	void initwithRole(string HeroName, cocos2d::TMXTiledMap* Map, unit* hero1,Vec2 bornpoint,Vector<unit*>* mapUnits);
	unit* getUnit() { return houyi; }
	void useSkill_1();
	void useSkill_2(Vec2 pos);
	void useSkill_3(unit* target);
	void sk1End();
	void sk2End();
	void sk3End();
	void useAlti();
	//技能相关
	inline bool isReleasing() { return sk1 || sk2 || sk3; }
	inline bool getSk1() { return sk1; }
	inline bool getSk2() { return sk2; }
	inline bool getSk3() { return sk3; }
	inline int getSk1Level() { return skill_1Level; }
	inline int getSk2Level() { return skill_2Level; }
	inline int getSk3Level() { return skill_3Level; }
	inline bool canRelease() { return canReleaseSkill; }
	inline void changeCanRelease(bool now) { canReleaseSkill = now; }

	//游戏刷新
	void cdUpdate(float dt);
	void skillFreshUpdate(float dt);

	void update(float dt) {
		//hp->update();
		if (hp->getCur() <= 1) die();
		hp->follow(getPosition());
		exp->follow(getPosition());
		auto it = ammosOnWay.begin();
		for (; it < ammosOnWay.end(); it++) {
			auto Dis = (this->getPosition() - (*it)->getPosition()).length();
			auto id1 = this->getid(); auto id2 = (*it)->getid();
			if (Dis < 150 && id1[1] != id2[1]) {
				auto Damage = (*it)->getDamage();
				this->getDamage(Damage,(*it)->getid());
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
		if (this->canAttack == 1)return;
		else { this->canAttack = 1; return; }
	}
	virtual int getDamage(int delta, std::string fromId) {
		if (hp->getCur() < delta) {
			die();
			//得到击杀者unit*添加奖励
			changeDeath(1);
			if (fromId[0] == 'H') {
				unit* killUnit = getUnitWithId(fromId);
				if (killUnit != nullptr) {
					killUnit->changeGold(float(getGold())*0.3>150? float(getGold())*0.3:150);
					killUnit->addCurExp((getExp()->getMaxExp())*2/10);
					killUnit->changeKillHero(1);
				}
			}
			this->setPosition(Vec2(270, 90));
			hp->changeCur(60000);
		}
		hp->changeCur((-delta)*(float)((100.0 - this->getDefenceOfPhysical()) / 100.0));
		return hp->getCur();
	}
	CREATE_FUNC(HouYi);
};