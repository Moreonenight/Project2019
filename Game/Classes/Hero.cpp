#include "Hero.h"
USING_NS_CC;
Hero * Hero::create(const std::string& id, int role)
{
	auto hero = new (std::nothrow) Hero();
	return hero;//返回指向此类的指针
}

bool Hero::init()
{
	Vec2 initPostion = Director::getInstance()->getVisibleSize();
	direction = Direction::NONE;
	//this->setPosition(initPostion/2);

	//this->setAnchorPoint();
	return true;
}
Sprite* Hero::initWithRole(Vec2 Postion)
{
	auto _player = Sprite::create("mysprite.png");
	_player->setPosition(Postion);
	this->addChild(_player, 2, 200);
	return _player;
}
int Hero::getSpeed()
{
	return Speed;
}
void Hero::setSpeed(int speed)
{
	this->Speed = speed;
}
int Hero::getHP()
{
	return HP;
}
void Hero::setHP(int HP)
{
	this->HP = HP;

}
int Hero::getATK()
{
	return ATK;
}
void Hero::setATK(int ATK)
{
	this->ATK = ATK;
}
int Hero::getDEF()
{
	return DEF;
}
void Hero::setDEF(int DEF)
{
	this->DEF = DEF;
}
void Hero::HeroDead()
{
	/*
	1.死亡后触发英雄死亡动画
	2.开启计时功能
	3.画面变灰
	4.复活后重新初始化英雄
	*/
}

bool Hero::ifAlive()
{

	return true;
}


void Hero::moveDirectionByKey(Hero::Direction direction,float x,float y,Sprite* Hero)
{
	//这里思桐后续会优化(Unitdata)
	

}

Hero::Direction Hero::getDirection()
{
	return direction;
}