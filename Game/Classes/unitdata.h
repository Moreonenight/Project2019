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
	"front_",
	"back_",
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
		3,
		2,
		1
	};
	string unitid;

	//skill

	cocos2d::Animation animations[NUM_OF_KINDS][4];
	int maxMana, maxHp, initGold, initLvl, damage/*damage of single attack*/
		, ASPD/*attack speed*/,
		attackRange,
		ammoSpeed,
		initMoveSpeed,
		defenceOfPhysical,
		defenceOfMagic;
	//cocos2d::Vec2 velocity;
	//cocos2d::Vec2 position;
	//cocos2d::Vec2 dpm;//defPhyicalMagic;
	//map<string, float> m1; 
	map<string, int> m2;
	
public:
	inline int getMaxHp() {
		return maxHp;
	}
	inline int getDamage() {
		return damage;
	}
	inline int getASPD() {
		return ASPD;
	}
	inline int getInitGold() {
		return initGold;
	}
	inline int getInitLvl() {
		return initLvl;
	}
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
		return (this->unitid + "Ammo");
	}
	inline string getUnitid() {
		return unitid;
	}
	~unitdata();
};

