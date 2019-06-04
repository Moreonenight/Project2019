#pragma once
#include "unitdata.h"
#include "ammo.h"
#include "HP.h"
USING_NS_CC;
class HP;
class unit:public Sprite
{
private:
	unitdata *data;
	Vec2 Velocity,dpm;
	HP *hp;//MP maxMana;
	std::string id;
	int level, gold, damage,ASPD,moveSpeed,ammoSpeed;
	bool canAttack;
	vector<ammo*> ammosOnWay;

	Animate* AnimateLeft;
Vec2 beforePos;

public:
	enum class Direction :int
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE
	};
	
	
	void initial(unitdata *unitdata);
	CREATE_FUNC(unit);
	
	
	~unit();
	
	
	inline string getid() { return id; }
	inline int getMaxHp();
	inline int getDamage() { return damage; }/*when want to know how much the unit damage is*/
	inline int changeDamage(int delta) { if (damage + delta > 0) damage += delta; else damage = 0; return damage; }
	int getAmmoSpeed() { return ammoSpeed; }
	inline string getAmmoFrameName() { return data->getAmmoFrameName(); }
	
	
	
	//string changeid(string& newid) { id = newid; return id; }
	inline void changeMaxHp(int delta);
	





	void getAttacked(ammo* amo) {
		ammosOnWay.push_back(amo);
		amo->changeTargetPosition(getPosition());
		return;
	}

	inline int getDamage(int delta);

	//inline int getDamage() { return damage; }/*when want to know how much the unit damage is*/ 
//	inline int changeDamage(int delta) { if (damage + delta > 0) damage += delta; else damage = 0; return damage; }
//	inline string getAmmoFrameName() { return data->getAmmoFrameName(); }
	inline void setBeforePos(Vec2 x) { beforePos = x; }
	inline Vec2 getBeforePos() { return beforePos; }
	//int getAmmoSpeed() { return ammoSpeed; }




	void stop();
	void moveDirectionByKey(unit::Direction direction, Vec2 e, unit* Hero);
	
	Sprite *attack(unit *target);
	void attackTo(unit *target);
	void attackTo(Vec2 destination);
	/*int getAmmoSpeed() {
		return data->getAmmoSpeed();
	}*/

	/*int getDamage(int damage) {
		float i = damage * dpm.x;
		hp->changeCur((int)i);
	}//when get damaged*/
	void die();

	void fresh() {
		hp->fresh();
		if (hp->getCur() <= 1) die();
		hp->setPosition(this->getPosition());
		if (canAttack == 1) return;
		else { canAttack = 1; return; }
		auto it = ammosOnWay.begin(); {
			for (; it < ammosOnWay.end(); it++)
				if (getPosition() == (*it)->getPosition()) {
					getDamage((*it)->getDamage());
				}
				else {
					(*it)->changeTargetPosition(getPosition());
					(*it)->fresh();
				}
		}
	}
};

