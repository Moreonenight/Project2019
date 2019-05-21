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


void Hero::moveDirectionByKey(Direction direction,float x,float y,Sprite* Hero)
{
	double Distancex = abs(Hero->getPositionX() - x);//x获取光标当前x位置
	double Distancey = abs(Hero->getPositionY() - y);//y获取光标当前y位置
	double Distance = sqrt(Distancex*Distancex + Distancey * Distancey);//计算人物与目标点距离
	double Speed = 300;//控制速度
	Hero->stopAllActions();//一定在每次响应时停止所有动作，不然连续点击会有bug
	Hero->runAction(MoveTo::create(Distance / Speed, Vec2(x,y)));
	//runAction第一个参数是移动所需要的时间，根据距离计算，第二个参数是移动目标点;

	//动画
	if (this->direction == Direction::LEFT)
	{
		//runAnimation(roleName + "_left", this);
	}
	else if (this->direction == Direction::RIGHT)
	{
		//runAnimation(roleName + "_right", this);
	}
	else if (this->direction == Direction::UP)
	{
		//runAnimation(roleName + "_up", this);
	}
	else if (this->direction == Direction::DOWN)
	{
		//runAnimation(roleName + "_down", this);
	}
}

Hero::Direction Hero::getDirection()
{
	return direction;
}