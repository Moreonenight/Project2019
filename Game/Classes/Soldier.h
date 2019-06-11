#ifndef __SOLDIER_H__
#define __SOLDIER_H__
#include "unit.h"
#include "cocos2d.h"

class Soldier : public unit
{
private:
	bool Attacking;
	bool CanAttackTower;
	bool CanAttackSoldier;
	bool CanAttackHero;
	Layer* _ammolayer;
	unit* AttackingTarget;
	int Destination;
public:
	
	inline bool ifAttacking()
	{
		return Attacking;
	}
	inline void ChangeAttacking(bool Attack)
	{
		Attacking = Attack;
	}
	inline void changeAttackingTarget(unit* target)
	{
		AttackingTarget = target;
	}
	inline unit* getAttackingTarget()
	{
		return AttackingTarget;

	}
	inline void ChangeCanAttackTower(bool Can)
	{
		CanAttackTower = Can;

	}
	inline bool GetCanAttackTower()
	{
		return CanAttackTower;

	}
	inline void ChangeCanAttackSoldier(bool Can)
	{
		CanAttackSoldier = Can;

	}
	inline bool GetCanAttackSoldier()
	{
		return CanAttackSoldier;

	}
	inline void ChangeCanAttackHero(bool Can)
	{
		CanAttackHero = Can;

	}
	inline bool GetCanAttackHero()
	{
		return CanAttackHero;

	}
	bool AttackingJudgeAI();

	bool Soldierinit(string Soldiername, int number, cocos2d::TMXTiledMap* Map, Vector<unit*>* mapUnits, Layer* ammoLayer);

	virtual int getDamage(int delta, std::string fromId) {
		if (hp->getCur() < delta) {
			die();
			ChangeAlreadydead(true);
			changeDeath(1);
			if (fromId[0] == 'H') {
				unit* killUnit = getUnitWithId(fromId);
				if (killUnit != nullptr) {
					killUnit->changeGold(this->getGold());
					killUnit->addCurExp(30);
					killUnit->changeKillSoldiers(1);
				}
			}
			//getHp()->dieHp();
			//getHp()->deleteHp();
			//removeFromParent();
			if (getid()[1] == 'r') {
				this->setPosition(Vec2(2000, 2000));

			}
			else if ((getid()[1] == 'b'))
			{
				this->setPosition(Vec2(-200, -200));

			}
			hp->changeCur(3000000);
		}
		hp->changeCur((-delta)*(float)((100.0 - this->getDefenceOfPhysical()) / 100.0));
		return hp->getCur();
	}
	void update(float dt) {
		//hp->update();
		if (hp->getCur() <= 1) die();
		hp->follow(getPosition());
		auto it = ammosOnWay.begin();
		for (; it < ammosOnWay.end(); it++) {

			auto Dis = (this->getPosition() - (*it)->getPosition()).length();
			auto id1 = this->getid(); auto id2 = (*it)->getid();
			if (Dis < 200 && id1[1] != id2[1]) {
				auto Damage = (*it)->getDamage();
				this->getDamage(Damage, (*it)->getid());
				(*it)->removeFromParentAndCleanup(1);
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

	CREATE_FUNC(Soldier);
};

#endif
