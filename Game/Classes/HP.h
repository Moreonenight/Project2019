#pragma once

#include <cocos2d.h>
#include "../proj.win32/unit.h"

USING_NS_CC;

class HP :public Sprite {
private:
	int velocity;
	unit *u;
	Sprite *bloodrect;
	int max_HP;
	Sprite *Hp1000;

	int cur_Hp;
	Sprite *curBlood;

	Sprite *emptyBlood;
public:

	void changeVel(int delta);
	int getCur();
	int getMax();
	void changeCur(int delta);
	void changeMax(int delta);
	void initial(unit *nunit);
	void fresh();
};
