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
	bool DeleteFlag;
	Vector<Soldier*>* MyTeam;
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
	void die(std::string fromId);
	bool AttackingJudgeAI();
	bool Soldierinit(string Soldiername, int number, cocos2d::TMXTiledMap* Map, Vector<unit*>* mapUnits, Vector<Soldier*>* _MyTeam, Layer* ammoLayer);
	virtual int getDamage(int delta, std::string fromId);
	void update(float dt);
	CREATE_FUNC(Soldier);
};

#endif
