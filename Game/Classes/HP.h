#pragma once
#include <cocos2d.h>
#include <string.h>
USING_NS_CC;

class HP :public Sprite {
private:

	std::string HpId;
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
		HpinitialData(int ma, int vel, Vec2 pos, Size siz, cocos2d::TMXTiledMap* map, bool eoa) :max(ma), velocity(vel), position(pos), size(siz), enemyOrAlly(eoa), _map(map) {}
	};
	CREATE_FUNC(HP);
	void changeVel(int delta);
	int getCur();
	int getMax();
	void follow(Vec2 pos) {
		if (!HpId.empty())
		{
			if (HpId[0] == 'H')
			{
			bloodrect->setPosition(pos.x - 80, pos.y + 100);
			emptyBlood->setPosition(pos.x - 80, pos.y + 100);
			curBlood->setPosition(pos.x - 80, pos.y + 100);
			}
			else if (HpId[0] == 'B')
			{
				bloodrect->setPosition(pos.x - 80, pos.y + 20);
				emptyBlood->setPosition(pos.x - 80, pos.y + 20);
				curBlood->setPosition(pos.x - 80, pos.y + 20);
			}
			else if (HpId[0] == 'T'&&HpId[2] == '3')
			{
				bloodrect->setPosition(pos.x - 70, pos.y + 90);
				emptyBlood->setPosition(pos.x - 70, pos.y + 90);
				curBlood->setPosition(pos.x - 70, pos.y + 90);
			}
			else if (HpId[0] == 'T'&&(HpId[2] == '1'|| HpId[2] == '2'))
			{
				bloodrect->setPosition(pos.x - 50, pos.y + 135);
				emptyBlood->setPosition(pos.x - 50, pos.y + 135);
				curBlood->setPosition(pos.x - 50, pos.y + 135);
			}

		}
		
		return;
	}

	void changeID(std::string id) {

		HpId = id;
	}
	void changeCur(int delta);
	void changeMax(int delta);
	void initial(HpinitialData data);
	void update(float dt);

	~HP();
};
