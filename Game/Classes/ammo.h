
#pragma once
#include <cocos2d.h>
USING_NS_CC;
class ammo :public Sprite {
private:
	//unit *target;
	std::string fromId;
	Vec2 velocity;
	Vec2 destination;
	int damage, ammoSpeed;
	SpriteFrame *Frame;
public:
	void initial(std::string fileName, std::string fromid,Vec2 currentPosition, int damge, int ammSpeed);
	ammo();
	CREATE_FUNC(ammo);
	inline Vec2 getDes() {
		return destination;
	}
	inline Vec2 getVel() {
		return velocity;
	}
	inline SpriteFrame *getFrame() {
		return Frame;
	}
	inline std::string getid() { return fromId; }
	int getDamage() { return damage; }
	void changeTargetPosition(Vec2 targtPosition);
	void update(float dt);

};