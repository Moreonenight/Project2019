#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Exp :public Sprite {
private:
	int Level;
	int cur_Exp;
	int Max_Exp;
	Sprite* ExpRect;
	Sprite* ExpLine;
	
	cocos2d::TMXTiledMap* _map;
public:

	//初始化
	void initial(int level, cocos2d::TMXTiledMap* map);
	//常量
	int expNeeded[9] = { 0,100,200,200,500,500,500,500,500 };
	//changeFunc
	void changeCurExp(int delta);
	void changeMaxExp(int num){ Max_Exp += num; }
	void changeLevel(int num){ Level += num; }
	
	//getFunc
	inline int getCurExp() { return cur_Exp; }
	inline int getMaxExp() { return Max_Exp; }
	inline int getLevel() { return Level; }

	//otherFunc
	void update(float dt);
	void follow(Vec2 pos);

	CREATE_FUNC(Exp);
};