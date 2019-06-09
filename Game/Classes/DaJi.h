#pragma once
#include "unit.h"

class DaJi:public unit
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
	void initwithRole(string HeroName, cocos2d::TMXTiledMap* Map, Vec2 bornpoint, Vector<unit*>* mapUnits, Layer* ammoLayer);
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
	CREATE_FUNC(DaJi);
};