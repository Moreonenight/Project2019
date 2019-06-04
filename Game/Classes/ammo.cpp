#include "ammo.h"

void ammo::initial(std::string fileName,Vec2 currentPosition,int damge,int ammSpeed)
{
	this->setPosition(currentPosition);
	damage = damge; ammoSpeed = ammSpeed;
	Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
	setSpriteFrame(Frame);
	auto a = getContentSize();
	//setAnchorPoint(getPosition()+(a/2));
	scheduleUpdate();
	setScale(2.0);
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

void ammo::update(float dt) //ammo�ġ�update��������һ��Layer��updateӦ�õ��������ӽ���update����
{	
	velocity = destination-getPosition();
	this->setRotation(CC_RADIANS_TO_DEGREES(velocity.getAngle())+3.1415926);
	velocity.normalize(); velocity *= ammoSpeed;
	this->setPosition( velocity + getPosition());
		/*
		*��Ҫͳһ��ʱ���ʾ��ʽ
		*����ȷ�ĸ�����������
		*��Ӣ�۹�����
		*unitdata��ʼ����
		*������ȫ��ͳһ�����ٶȣ�
		*/
	}

