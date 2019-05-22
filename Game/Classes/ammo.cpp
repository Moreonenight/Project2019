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

void ammo::fresh() //ammo的“update”函数，一个Layer的update应该调用所有子结点的update函数
{
	if (getPosition() == target->getPosition()) {
		//target->getDamage(damage);
	}
	else {
		this->setRotation(CC_RADIANS_TO_DEGREES((target->getPosition()-getPosition()).getAngle()));
		velocity = getPosition() - target->getPosition(); velocity.normalize(); velocity *= (float)ammoSpeed;
		this->runAction(MoveTo::create(1 / velocity.length(), velocity + getPosition()));
		/*
		*需要统一的时间表示方式
		*不明确的浮点数的意义
		*与英雄关联？
		*unitdata初始化？
		*或者是全局统一弹道速度？
		*/
	}
}
