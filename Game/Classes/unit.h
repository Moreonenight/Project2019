#pragma once
#include "unitdata.h"
#include "ammo.h"
#include "HP.h"
#include "Exp.h"
#include "Equipment.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
//出生点坐标


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
	int skillPoint;

		Animate* AnimateLeft;
		Vec2 beforePos;
		Equipment equip[6];
		Vec2 EquipmentPostion[6];
		Layer* AmmoLayer;
		Menu* myMenu;
		int KillHero, KillSoldiers, deathnumber;
		bool Alreadydead;

public:
	HP *hp;//MP maxMana;
	Exp *exp=nullptr;
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
	int* getDamagepointer(){


		return &damage;

	}
	Vec2 getSpawnPoint();
	inline void ChangeAlreadydead(bool dead)
	{
		Alreadydead = dead;
	}
	inline bool GetAlreadydead()
	{
		return Alreadydead;
	}

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

	void initial(unitdata *unitdata, cocos2d::TMXTiledMap* Map, Vector<unit*>* mapUnits, Layer* ammoLayer);
	CREATE_FUNC(unit);
	
	
	~unit();
	inline int getInitDamage() { return InitDamage; }
	int getDefenceOfPhysical() {
		return defenceOfPhysical;
	}
	int getDefencOfMagic() {
		return defenceOfMagic;
	}

	//getFunc
	//int getMaxMana() { return maxMana; }
	HP* getHp() { return hp; }
	unitdata* getdata() { return data; }
	Exp* getExp(){ return exp; }
	int getRecoverOfMana() { return recoverOfMana; }
	int getGold() { return gold; }int changeGold(int delta) { if (gold + delta <= 0)gold = 0; else gold += delta; return gold; }
	inline int getKillHero() { return KillHero; }
	inline int getDeath() { return deathnumber; }
	inline int getKillSoldiers() { return KillSoldiers; }
	inline string getid() { return id; }


	inline int getMoveSpeed() {		return moveSpeed;	}
	inline int getDamage() { return damage; }/*when want to know how much the unit damage is*/
	int getAmmoSpeed() { return ammoSpeed; }
	inline string getAmmoFrameName() { return data->getAmmoFrameName(); }
	inline void changeMaxHp(int delta) { hp->changeMax(delta); }
	inline int getMaxHp() { return hp->getMax(); }

	inline int getSkillPoint() { return skillPoint; }
	

	//change Func
	inline std::string changeid(string newid) { id = newid; return id; }
	inline void changeLevel(int num) { if (num == 0) { return; }if (level + num <= 8)level += num; skillPoint += num; }
	inline int changeMoveSpeed(int delta) { if (moveSpeed + delta < 0)moveSpeed = 0; else moveSpeed += delta; return moveSpeed; }
	inline int changeDamage(int delta) { if (damage + delta > 0) damage += delta; else damage = 0; return damage; }
	inline void changeCurHp(int delta) { hp->changeCur(delta); }
	void addCurExp(int delta) { exp->changeCurExp(delta); changeLevel(exp->getLevel() - level);}
	inline void changeKillHero(int delta) { KillHero += delta; }
	inline void changeKillSoldiers(int delta) { KillSoldiers += delta; }
	inline void changeDeath(int delta) { deathnumber += delta; }
	inline void fullHp() { hp->changeCur(hp->getMax()); }

	inline void changeSkillPoint(int num) { if ((skillPoint + num) < 0)skillPoint = 0; else skillPoint += num; }

	//otherFunc
	void getAttacked(ammo* amo) {
		ammosOnWay.push_back(amo);
		amo->changeTargetPosition(getPosition());
		return;
	}

	virtual int getDamage(int delta,std::string fromId) {
		if (hp->getCur() < delta) {
			die();
			//得到击杀者unit*添加奖励
			if (fromId[0] == 'H') {
				unit* killUnit = getUnitWithId(fromId);
				if (killUnit != nullptr) {
					killUnit->changeGold(50);
					killUnit->addCurExp(50);
				}
			}
			this->setPosition(getSpawnPoint());
			fullHp();
			this->stopAllActions();
		}
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
	void die(){}
	
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
	bool addEquipment(std::string itemId, Layer* equipmentlayer,Layer* shoplayer);
	bool sellEquipment(int number, Layer* equipmentlayer, Layer* shoplayer);
};

