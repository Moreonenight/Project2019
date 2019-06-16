#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Mana :public Sprite {
private:
	int cur_Mana;
	int Max_Mana;
	int velocity;
	int Timer;
	int RecoverMana;
	Sprite* ManaRect;
	Sprite* ManaLine;
	cocos2d::TMXTiledMap* _map;
	std::string ManaID;
public:
	struct ManainitialData {
		int max;
		Vec2 position;
		cocos2d::TMXTiledMap* _map;
	public:
		ManainitialData(int ma, Vec2 pos, cocos2d::TMXTiledMap* map) :max(ma), position(pos),_map(map) {}
	};

	//≥ı ºªØ
	void initial(ManainitialData data);

	
	inline void changeCurMana(int delta)
	{
		int changedMana = cur_Mana + delta;
		if (changedMana <= 0) { cur_Mana = 0; }
		else if (changedMana > Max_Mana) cur_Mana = Max_Mana;
		else cur_Mana = changedMana;
		return;
	}
	void changeID(std::string id) {
		ManaID = id;
	}
		
	void changeMaxMana(int num){ Max_Mana += num; }
	
	
	//getFunc
	inline int getCurMana() { return cur_Mana; }
	inline int getMaxMana() { return Max_Mana; }
	//otherFunc
	void update(float dt);
	void follow(Vec2 pos);

	CREATE_FUNC(Mana);
};