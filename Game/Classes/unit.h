#pragma once
#include "unitdata.h"
USING_NS_CC;
class HP;
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
	enum class Direction :int
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		NONE
	};
	unit(unitdata& unitdata);
	~unit();
	inline string getid() { return id; }

		//string changeid(string& newid) { id = newid; return id; }
	inline int getMaxHp();
	inline void changeMaxHp(int delta);
	
	inline int getDamage()/*when want to know how much the unit damage is*/ { return damage; }inline int changeDamage(int delta) { if (damage + delta > 0) damage += delta; else damage = 0; return damage; }
	inline string getAmmoFrameName() { return data->getAmmoFrameName(); }
	
	void stop();
	void moveDirectionByKey(unit::Direction direction, Vec2 e, Sprite* Hero);


	Sprite *attack(unit *target);
	void attackTo(unit *target);
	void attackTo(Vec2 destination);
	int getAmmoSpeed() {
		return data->getAmmoSpeed();
	}
	void freshCanAttack() { if (canAttack == 1) return; else { canAttack = 1; return; } }
	/*int getDamage(int damage) {
		float i = damage * dpm.x;
		hp->changeCur((int)i);
	}//when get damaged*/
	void die();

	
	


};

