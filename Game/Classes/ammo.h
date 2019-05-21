#pragma once
#include "unit.h"
USING_NS_CC;
class ammo :public Sprite {
private:
	unit *target;
	Vec2 velocity;
	int damage, ammoSpeed;
	SpriteFrame *Frame;
public:
	ammo();
	inline Vec2 getDes() {
		return target->getPosition();
	}
	inline Vec2 getVel() {
		return velocity;
	}
	inline SpriteFrame *getFrame() {
		return Frame;
	}
	void fresh();
	ammo* createAnAmmo(unit *attacker,unit * target);
};