#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include <cocos2d.h>
using namespace std;
#define NUM_OF_KINDS 5


class unitdata
{
private:


	string dir[NUM_OF_KINDS] = {
		"up_",
		"down_",
		"left_",
		"right_",
		""
	};
	string kind[NUM_OF_KINDS] = {
		"attack",
		"walk",
		"death",
		"stand",
		"ammo"
	};
	int numOfFrames[NUM_OF_KINDS] = {
		8,
		8,
		8,
		8,
		0
	};
	string unitid;

	//skill

	//cocos2d::Animation animations[NUM_OF_KINDS][4];
	int maxMana,
		maxHp,
		initGold,
		damage/*damage of single attack*/
		, ASPD/*attack speed*/,
		attackRange,
		ammoSpeed,
		moveSpeed,
		defenceOfPhysical,
		defenceOfMagic,
		recoverOfHp,
		recoverOfMana;
	//cocos2d::Vec2 velocity;
	//cocos2d::Vec2 position;
	//cocos2d::Vec2 dpm;//defPhyicalMagic;
	//map<string, float> m1; 
	map<string, int> m2;
	
public:
	inline int getMaxHp() {
		return maxHp;
	}
	int getRecoverOfHp() {
		return recoverOfHp;
	}
	inline int getDamage() {
		return damage;
	}
	inline int getASPD() {
		return ASPD;
	}
	int getMoveSpeed() {
		return moveSpeed;
	}
	inline int getInitGold() {
		return initGold;
	}
	int getDefenceOfPhysical() {
		return defenceOfPhysical;
	}
	int getDefenceOfMagic() {
		return defenceOfMagic;
	}
	int getMaxMana() { return maxMana; }
	int getRecoverOfMana() { return recoverOfMana; }

	inline int getAmmoSpeed() {
		return ammoSpeed;
	}
	inline int getAttackRange() { return attackRange; }
	bool initial(string &datapath);/*datapath下的文件
								   *必须由几个kind内的txt文件
								   *和float.txt/integer.txt构成，
								   *各文件都以图集信息在第一行，
								   *按顺序每行一个帧的图片名称*/
	inline string unitdata::getAmmoFrameName() {
		return (this->unitid + "ammo.png");
	}
	inline string getUnitid() {
		return unitid;
	}
	~unitdata();
};

