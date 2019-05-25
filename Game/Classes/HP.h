#pragma once
#include <cocos2d.h>

USING_NS_CC;

class HP :public Sprite {
private:
	Vec2 position;

	int velocity;
	//unit *u;
	Sprite *bloodrect;
	int max_HP;
	Sprite *Hp1000;

	int cur_Hp;
	Sprite *curBlood;

	Sprite *emptyBlood;
public:
	CREATE_FUNC(HP);
	void changeVel(int delta);
	int getCur();
	int getMax();
	void changeCur(int delta);
	void changeMax(int delta);
	void initial(Vec2 position, Size size, bool enemyOrAlly);
	void fresh();
	~HP();
};
