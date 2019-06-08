#pragma once
#include "unit.h"

class HouYi :public unit
{
private:
	unit* houyi;
	unitdata* houyiData;
	int level;
	int skill_1Level;
	int skill_2Level;
	int skill_3Level;
	int sk1Damage[6] = { 200,240,280,320,360,400 };
	int sk2Damage[6] = { 300,350,400,450,500,550 };
	float sk2Cd[6] = { 8.0,7.4,6.8,6.2,5.6,5 };
	int sk3Damage[3] = { 700,875,1050 };
	float sk3Cd[3] = { 45,40,35 };
public:
	void initwithRole(string HeroName, cocos2d::TMXTiledMap* Map, Vec2 bornpoint,Vector<unit*>* mapUnits);
	unit* getUnit() { return houyi; }
	void useskill_1();
	void sk1End(float dt);
	void skill_1_cd(float dt);
	void useSkill_2(Vec2 pos);
	void useAlti();
	void update(float dt) {
		//hp->update();
		if (hp->getCur() <= 1) die();
		hp->follow(getPosition());
		exp->follow(getPosition());
		auto it = ammosOnWay.begin();
		for (; it < ammosOnWay.end(); it++) {
			auto Dis = (this->getPosition() - (*it)->getPosition()).length();
			auto id1 = this->getid(); auto id2 = (*it)->getid();
			if (Dis < 100 && id1[1] != id2[1]) {
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
			if (fromId[0] == 'H') {
				unit* killUnit = getUnitWithId(fromId);
				if (killUnit != nullptr) {
					killUnit->changeGold(float(getGold())*0.3>150? float(getGold())*0.3:150);
					killUnit->changeCurExp((getExp()->getMaxExp())*2/10);
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