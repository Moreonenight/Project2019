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
	bool Alreadydead;
	unit* AttackingTarget;
	int Destination;
public:
	inline void ChangeAlreadydead(bool dead)
	{
		Alreadydead = dead;
	}
	inline bool GetAlreadydead()
	{
		return Alreadydead;
	}
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

	bool Soldierinit(string Soldiername, int number, cocos2d::TMXTiledMap* Map, Vector<unit*>* mapUnits);

	virtual int getDamage(int delta, std::string fromId) {
		if (hp->getCur() < delta) {
			die();
			changeDeath(1);
			if (fromId[0] == 'H') {
				unit* killUnit = getUnitWithId(fromId);
				if (killUnit != nullptr) {
					killUnit->changeGold(this->getGold());
					killUnit->addCurExp(30);
					killUnit->changeKillSoldiers(1);
				}
			}
			this->setPosition(getSpawnPoint());
			fullHp();
		}
		hp->changeCur((-delta)*(float)((100.0 - this->getDefenceOfPhysical()) / 100.0));
		return hp->getCur();
	}

	void update(float dt) {
		//hp->update();
		hp->follow(getPosition());

		auto it = ammosOnWay.begin();
		for (; it < ammosOnWay.end(); it++) {
			int MinDis;
			auto Dis = (this->getPosition() - (*it)->getPosition()).length();
			auto id1 = this->getid(); auto id2 = (*it)->getid();
			if (getid()[2] == '1') { MinDis = 5000; }
			else if (getid()[2] == '2') { MinDis = 350; }
			else if (getid()[2] == '3') { MinDis = 350; }
			
			if (Dis < MinDis && id1[1] != id2[1]) {
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
	CREATE_FUNC(Soldier);
};

#endif
