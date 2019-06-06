#pragma once
#include <cocos2d.h>

USING_NS_CC;

class HP :public Sprite {
private:


	int velocity;
	//unit *u;
	Sprite *bloodrect;
	int max_HP;
	//Sprite *Hp1000;

	int cur_Hp;
	Sprite *curBlood;

	Sprite *emptyBlood;
public:
	struct HpinitialData {
		int max;
		int velocity;
		Vec2 position;
		Size size;
		bool enemyOrAlly;
		cocos2d::TMXTiledMap* _map;

	public:
		HpinitialData(int ma, int vel, Vec2 pos, Size siz, cocos2d::TMXTiledMap* map, bool eoa) :max(ma), velocity(vel), position(pos), size(siz), enemyOrAlly(eoa),_map(map) {}
	};
	CREATE_FUNC(HP);
	void changeVel(int delta);
	int getCur();
	int getMax();
	void follow(Vec2 pos) {
		bloodrect->setPosition(pos.x-50, pos.y + 70);
		emptyBlood->setPosition(pos.x - 50, pos.y + 70);
		curBlood->setPosition(pos.x - 50, pos.y + 70);
		return;
	}
	void changeCur(int delta);
	void changeMax(int delta);
	void initial(HpinitialData data);
	void update(float dt);

	~HP();
};
