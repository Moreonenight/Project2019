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
	HP *hp;//MP maxMana;
	std::string id;
	int level,
		gold, 
		damage,
		ASPD,
		moveSpeed,
		ammoSpeed,
		attackRange,
		defenceOfPhysical,
		defenceOfMagic,
		recoverOfMana;
	bool canAttack;
	vector<ammo*> ammosOnWay;
	cocos2d::TMXTiledMap* _map;

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
	
	Direction getDir(Vec2 v) { return getDir(CC_RADIANS_TO_DEGREES(v.getAngle()));  };
	Direction getDir(float angle) {
		Direction dir; 
		if (angle <= 45.0&&angle > -45.0) dir = Direction::RIGHT;
		else if (angle > 45.0&&angle <= 135.0) dir = Direction::UP;
		else if (angle > 135.0 || angle <= -135.0) dir = Direction::LEFT;
		else if (angle > -135.0&&angle <= -45.0) dir = Direction::DOWN;
		return dir;
	}
	Direction getDir(Vec2 curPos, Vec2 desPos) { return getDir(desPos - curPos); }

	void initial(unitdata *unitdata, cocos2d::TMXTiledMap* _tileMap);
	CREATE_FUNC(unit);
	
	
	~unit();
	
	int getDefenceOfPhysical() {
		return defenceOfPhysical;
	}
	int getDefencOfMagic() {
		return defenceOfMagic;
	}
	//int getMaxMana() { return maxMana; }
	HP* getHp() { return hp; }
	int getRecoverOfMana() { return recoverOfMana; }
	int getGold() { return gold; }int changeGold(int delta) { if (gold + delta <= 0)gold = 0; else gold += delta; return gold; }
	inline string getid() { return id; }
	inline int getMaxHp();
	inline int getMoveSpeed() {		return moveSpeed;	}
	inline int getDamage() { return damage; }/*when want to know how much the unit damage is*/
	inline int changeMoveSpeed(int delta) { if (moveSpeed + delta < 0)moveSpeed = 0; else moveSpeed += delta; return moveSpeed; }
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

	inline int getDamage(int delta) {
		hp->changeCur((-delta)*(float)((100.0-defenceOfPhysical) / 100.0));
		return hp->getCur();
	}

	//inline int getDamage() { return damage; }/*when want to know how much the unit damage is*/ 
//	inline int changeDamage(int delta) { if (damage + delta > 0) damage += delta; else damage = 0; return damage; }
//	inline string getAmmoFrameName() { return data->getAmmoFrameName(); }
	inline void setBeforePos(Vec2 x) { beforePos = x; }
	inline Vec2 getBeforePos() { return beforePos; }
	//int getAmmoSpeed() { return ammoSpeed; }




	void stop();
	void moveDirectionByKey(unit::Direction direction, Vec2 e);
	
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
	
	void update(float dt) {
		//hp->update();
		if (hp->getCur() <= 1) die();
		hp->follow(getPosition());

		auto it = ammosOnWay.begin(); 
			for (; it < ammosOnWay.end(); it++){
				auto Dis = (this->getPosition() - (*it)->getPosition()).length();

				if (Dis<100) {
					auto Damage = (*it)->getDamage();
					this->getDamage(Damage);
					(*it)->removeFromParentAndCleanup(1);
					//(*it)->setVisible(0);
					//(*it)->setPosition(200.0, 200.0);
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
	void freshASPD(float dt) {
		;
	}
};

