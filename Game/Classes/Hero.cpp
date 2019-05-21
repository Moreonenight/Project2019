#include "Hero.h"
USING_NS_CC;
Hero * Hero::create(const std::string& id, int role)
{
	auto hero = new (std::nothrow) Hero();
	return hero;//����ָ������ָ��
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
	1.�����󴥷�Ӣ����������
	2.������ʱ����
	3.������
	4.��������³�ʼ��Ӣ��
	*/
}

bool Hero::ifAlive()
{

	return true;
}


void Hero::moveDirectionByKey(Direction direction,float x,float y,Sprite* Hero)
{
	double Distancex = abs(Hero->getPositionX() - x);//x��ȡ��굱ǰxλ��
	double Distancey = abs(Hero->getPositionY() - y);//y��ȡ��굱ǰyλ��
	double Distance = sqrt(Distancex*Distancex + Distancey * Distancey);//����������Ŀ������
	double Speed = 300;//�����ٶ�
	Hero->stopAllActions();//һ����ÿ����Ӧʱֹͣ���ж�������Ȼ�����������bug
	Hero->runAction(MoveTo::create(Distance / Speed, Vec2(x,y)));
	//runAction��һ���������ƶ�����Ҫ��ʱ�䣬���ݾ�����㣬�ڶ����������ƶ�Ŀ���;

	//����
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