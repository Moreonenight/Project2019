#pragma once
#include "cocos2d.h"
#include "unit.h"
USING_NS_CC;
class Tower:public unit
{
private:
	bool Attacking;
	bool CanAttackSoldier;
	bool CanAttackHero;
	bool Alreadydead;
	unit* AttackingTarget;
	unit* LastAttackingTarget;
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
	bool Tower::InitWithRole(string Towername, cocos2d::TMXTiledMap* Map, Vector<unit*>* mapUnits, Layer* ammoLayer);
	bool AttackingJudgeAI();
	virtual int getDamage(int delta, std::string fromId) {
		if (hp->getCur() < delta) {
			die();
			//�õ���ɱ��unit*���ӽ���
			if (fromId[0] == 'H') {
				unit* killUnit = getUnitWithId(fromId);
				if (killUnit != nullptr) {
					killUnit->changeGold(50);
					killUnit->addCurExp(50);
				}
			}
			if (getid()[1] == 'r') {

				this->setPosition(Vec2(2000, 2000));

			}
			else if ((getid()[1] == 'b'))
			{
				this->setPosition(Vec2(-200, -200));

			}
			this->stopAllActions();
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
	CREATE_FUNC(Tower);
};

