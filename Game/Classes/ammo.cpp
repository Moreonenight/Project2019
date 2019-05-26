#include "ammo.h"

void ammo::initial(std::string fileName,Vec2 currentPosition,int damge,int ammSpeed)
{
	this->setPosition(currentPosition);
	damage = damge; ammoSpeed = ammSpeed;
	Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
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

void ammo::fresh() //ammo�ġ�update��������һ��Layer��updateӦ�õ��������ӽ���update����
{	
	velocity = destination-getPosition();
	this->setRotation(CC_RADIANS_TO_DEGREES(velocity.getAngle()));
	velocity.normalize(); velocity *= ammoSpeed;
	this->runAction(MoveTo::create(1 / velocity.length(), velocity + getPosition()));
		/*
		*��Ҫͳһ��ʱ���ʾ��ʽ
		*����ȷ�ĸ�����������
		*��Ӣ�۹�����
		*unitdata��ʼ����
		*������ȫ��ͳһ�����ٶȣ�
		*/
	}

