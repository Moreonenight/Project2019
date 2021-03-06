#include "ammo.h"

void ammo::initial(std::string fileName,std::string fromid,Vec2 currentPosition,int damge,int ammSpeed)
{
	this->setPosition(currentPosition);
	damage = damge; ammoSpeed = ammSpeed;
	fromId = fromid;
	auto a = SpriteFrameCache::getInstance();
	Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
	setSpriteFrame(Frame);
	scheduleUpdate();
	if (fromid[2] == 'D')
	{
		setScale(0.03);
	}
	else
	{
		setScale(0.5);
	}
	
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
	}

