#pragma once
#include "unitdata.h"
#include "ammo.h"
#include "HP.h"
#include "Equipment.h"
#include "Exp.h"
USING_NS_CC;
class HP;
class unit:public Sprite
{
private:
	unitdata *data;
	
	std::string id;
	int level,
		gold,
		damage,
		InitDamage,
		ASPD,
		moveSpeed,
		ammoSpeed,
		attackRange,
		defenceOfPhysical,
		defenceOfMagic,
		recoverOfMana;
	Animate* AnimateLeft;
	Equipment equip[6];
	Vec2 beforePos;

public:
	HP *hp;//MP maxMana;
	Exp *exp;
	bool canAttack;
	vector<ammo*> ammosOnWay;
	cocos2d::TMXTiledMap* _map;
	Vector<unit*>* unitsOnMap;
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

	void initial(unitdata *unitdata, cocos2d::TMXTiledMap* _tileMap, Vector<unit*>* mapUnits);
	CREATE_FUNC(unit);
	
	
	~unit();
	inline int getInitDamage() { return InitDamage; }
	int getDefenceOfPhysical() {
		return defenceOfPhysical;
	}
	int getDefencOfMagic() {
		return defenceOfMagic;
	}
	//int getMaxMana() { return maxMana; }
	HP* getHp() { return hp; }
	Exp* getExp() { return exp; }
	int getRecoverOfMana() { return recoverOfMana; }
	int getGold() { return gold; }int changeGold(int delta) { if (gold + delta <= 0)gold = 0; else gold += delta; return gold; }
	inline string getid() { return id; }
	inline int getMaxHp();
	inline int getMoveSpeed() {		return moveSpeed;	}
	inline int getDamage() { return damage; }/*when want to know how much the unit damage is*/
	int getAmmoSpeed() { return ammoSpeed; }
	inline string getAmmoFrameName() { return data->getAmmoFrameName(); }
	
	

	///////    �ı����״̬    ///////
	inline void changeMaxHp(int delta);
	inline int changeMoveSpeed(int delta) { if (moveSpeed + delta < 0)moveSpeed = 0; else moveSpeed += delta; return moveSpeed; }
	inline int changeDamage(int delta) { if (damage + delta > 0) damage += delta; else damage = 0; return damage; }
	inline void setDamage(int num) { damage = num;}
	inline void setMaxHp() { hp->changeCur(getMaxHp()); }
	inline void setBeforePos(Vec2 x) { beforePos = x; }
	inline Vec2 getBeforePos() { return beforePos; }
	inline std::string changeid(string newid) { id = newid; return id; }



	///////    ���๦�ܺ���    ///////
	void getAttacked(ammo* amo) {
		ammosOnWay.push_back(amo);
		amo->changeTargetPosition(getPosition());
		return;
	}

	int getDamage(int delta,std::string fromId) {
		if (hp->getCur() < delta) {
			die();
			//�õ���ɱ��unit*���ӽ���
			unit* killUnit=getUnitWithId(fromId);
			if (killUnit != nullptr) {
				killUnit->changeGold(50);
			}
			this->setPosition(Vec2(270, 90));
			setMaxHp();
			this->stopAllActions();
		}
		hp->changeCur((-delta)*(float)((100.0-defenceOfPhysical) / 100.0));
		return hp->getCur();
	}

	//inline int getDamage() { return damage; }/*when want to know how much the unit damage is*/ 
//	inline int changeDamage(int delta) { if (damage + delta > 0) damage += delta; else damage = 0; return damage; }
//	inline string getAmmoFrameName() { return data->getAmmoFrameName(); }
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
	virtual void die(){}
	
	/*void update(float dt) {
		//hp->update();
		if (hp->getCur() <= 1) die();
		hp->follow(getPosition());

		auto it = ammosOnWay.begin(); 
			for (; it < ammosOnWay.end(); it++){
				auto Dis = (this->getPosition() - (*it)->getPosition()).length();

				if (Dis<100) {
					auto Damage = (*it)->getDamage();
					this->getDamage(Damage,(*it)->getid());
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
	}
	void freshASPD(float dt) {
		if (this->canAttack == 1)return;
		else { this->canAttack = 1; return; }
	}*/
	unit* getUnitWithId(std::string id);

	bool addEquipment(std::string itemName);
};

