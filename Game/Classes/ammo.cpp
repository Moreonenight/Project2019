#include "ammo.h"

ammo * ammo::createAnAmmo(unit * attacker, unit * target)
{
	this->setPosition(attacker->getPosition());
	damage = attacker->getDamage(); ammoSpeed = attacker->getAmmoSpeed();
	Frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(attacker->getAmmoFrameName());
	this->target = target;
	return nullptr;
}

ammo::ammo()
{
}

void ammo::fresh() //ammo�ġ�update��������һ��Layer��updateӦ�õ��������ӽ���update����
{
	if (getPosition() == target->getPosition()) {
		//target->getDamage(damage);
	}
	else {
		this->setRotation(CC_RADIANS_TO_DEGREES((target->getPosition()-getPosition()).getAngle()));
		velocity = getPosition() - target->getPosition(); velocity.normalize(); velocity *= (float)ammoSpeed;
		this->runAction(MoveTo::create(1 / velocity.length(), velocity + getPosition()));
		/*
		*��Ҫͳһ��ʱ���ʾ��ʽ
		*����ȷ�ĸ�����������
		*��Ӣ�۹�����
		*unitdata��ʼ����
		*������ȫ��ͳһ�����ٶȣ�
		*/
	}
}
