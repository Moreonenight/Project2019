#include "ammo.h"

void ammo::initial(std::string fileName,std::string fromid,Vec2 currentPosition,int damge,int ammSpeed)
{
	this->setPosition(currentPosition);
	damage = damge; ammoSpeed = ammSpeed;
	fromId = fromid;
	Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
	setSpriteFrame(Frame);
	scheduleUpdate();
	setScale(0.5);
	return ;
}

ammo::ammo()
{
}

void ammo::changeTargetPosition(Vec2 targetPosition)
{
	destination = targetPosition;
	return;
}

void ammo::update(float dt) //ammo的“update”函数，一个Layer的update应该调用所有子结点的update函数
{	
	velocity = destination-getPosition();
	this->setRotation(180-CC_RADIANS_TO_DEGREES(velocity.getAngle()));
	velocity.normalize(); velocity *= ammoSpeed;
	this->setPosition( velocity + getPosition());
		/*
		*需要统一的时间表示方式
		*不明确的浮点数的意义
		*与英雄关联？
		*unitdata初始化？
		*或者是全局统一弹道速度？
		*/
	}

