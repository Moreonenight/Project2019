#pragma once

#include <cocos2d.h>
#include "HP.h"
#include "string.h"
#include "unitdata.h"

USING_NS_CC;

class unit:public Sprite
{
private:
	unitdata *data;
	Vec2 Velocity,dpm;
	HP *hp;//MP maxMana;
	std::string id;
	int level, gold, damage,ASPD;
	bool canAttack;
public:
	unit(unitdata& unitdata);
	~unit();
	inline string getid() { return id; }inline //
		
	//string changeid(string& newid) { id = newid; return id; }
	inline int getMaxHp() { return hp->getMax(); }inline void changeMaxHp(int delta) { hp->changeMax(delta);}
	inline int getDamage()/*when want to know how much the unit damage is*/ { return damage; }inline int changeDamage(int delta) { if (damage + delta > 0) damage += delta; else damage = 0; return damage; }
	inline string getAmmoFrameName() { return data->getAmmoFrameName(); }
	
	void stop();
	void moveTo(cocos2d::Vec2 destination);
	Sprite *attack(unit *target);
	void attackTo(unit *target);
	void attackTo(Vec2 destination);
	int getAmmoSpeed() {
		return data->getAmmoSpeed();
	}
	void freshCanAttack(float delta) { if (canAttack == 1) return; else { canAttack == 1; return; } }
	int getDamage(int damage) {
		float i = damage * dpm.x;
		hp->changeCur((int)i);
	}//when get damaged
	void die();

	
	


};

