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
	Vector<SpriteFrame*> animFrames_up;
	Vector<SpriteFrame*> animFrames_down;
	Vector<SpriteFrame*> animFrames_left;
	Vector<SpriteFrame*> animFrames_right;
	animFrames_up.reserve(6);
	animFrames_down.reserve(6);
	animFrames_left.reserve(6);
	animFrames_right.reserve(6);
	animFrames_down.pushBack(SpriteFrame::create("Player/Player2_1.png", Rect(0, 0, 32, 32)));
	animFrames_down.pushBack(SpriteFrame::create("Player/Player2_2.png", Rect(0, 0, 32, 32)));
	animFrames_down.pushBack(SpriteFrame::create("Player/Player2_3.png", Rect(0, 0, 32, 32)));
	animFrames_down.pushBack(SpriteFrame::create("Player/Player2_4.png", Rect(0, 0, 32, 32)));
	animFrames_down.pushBack(SpriteFrame::create("Player/Player2_5.png", Rect(0, 0, 32, 32)));
	animFrames_left.pushBack(SpriteFrame::create("Player/Player2_6.png", Rect(0, 0, 32, 32)));
	animFrames_left.pushBack(SpriteFrame::create("Player/Player2_7.png", Rect(0, 0, 32, 32)));
	animFrames_left.pushBack(SpriteFrame::create("Player/Player2_8.png", Rect(0, 0, 32, 32)));
	animFrames_left.pushBack(SpriteFrame::create("Player/Player2_9.png", Rect(0, 0, 32, 32)));
	animFrames_left.pushBack(SpriteFrame::create("Player/Player2_10.png", Rect(0, 0, 32, 32)));
	animFrames_right.pushBack(SpriteFrame::create("Player/Player2_11.png", Rect(0, 0, 32, 32)));
	animFrames_right.pushBack(SpriteFrame::create("Player/Player2_12.png", Rect(0, 0, 32, 32)));
	animFrames_right.pushBack(SpriteFrame::create("Player/Player2_13.png", Rect(0, 0, 32, 32)));
	animFrames_right.pushBack(SpriteFrame::create("Player/Player2_14.png", Rect(0, 0, 32, 32)));
	animFrames_right.pushBack(SpriteFrame::create("Player/Player2_15.png", Rect(0, 0, 32, 32)));
	animFrames_up.pushBack(SpriteFrame::create("Player/Player2_16.png", Rect(0, 0, 32, 32)));
	animFrames_up.pushBack(SpriteFrame::create("Player/Player2_17.png", Rect(0, 0, 32, 32)));
	animFrames_up.pushBack(SpriteFrame::create("Player/Player2_18.png", Rect(0, 0, 32, 32)));
	animFrames_up.pushBack(SpriteFrame::create("Player/Player2_19.png", Rect(0, 0, 32, 32)));
	animFrames_up.pushBack(SpriteFrame::create("Player/Player2_20.png", Rect(0, 0, 32, 32)));
	Animation* animation_down = Animation::createWithSpriteFrames(animFrames_down, 0.1f);
	Animation* animation_left = Animation::createWithSpriteFrames(animFrames_left, 0.1f);
	Animation* animation_right = Animation::createWithSpriteFrames(animFrames_right, 0.1f);
	Animation* animation_up = Animation::createWithSpriteFrames(animFrames_up, 0.1f);
	Animate* animate_down = Animate::create(animation_down);
	Animate* animate_left = Animate::create(animation_left);
	Animate* animate_right = Animate::create(animation_right);
	Animate* animate_up = Animate::create(animation_up);
	double Distancex = abs(Hero->getPositionX() - x);//x获取光标当前x位置
	double Distancey = abs(Hero->getPositionY() - y);//y获取光标当前y位置
	double Distance = sqrt(Distancex*Distancex + Distancey * Distancey);//计算人物与目标点距离
	double Speed = 100;//控制速度
	switch (direction)
	{
	case Hero::Direction::LEFT:
		
		Hero->stopAllActions();
		Hero->runAction(Repeat::create(animate_left, Distance / Speed / 0.4f));
		Hero->runAction(MoveTo::create(Distance / Speed, Vec2(x, y)));
		break;
	case Hero::Direction::RIGHT:
		Hero->stopAllActions();
		Hero->runAction(Repeat::create(animate_right, Distance / Speed / 0.4f));
		Hero->runAction(MoveTo::create(Distance / Speed, Vec2(x, y)));
		break;
	case Hero::Direction::UP:

		Hero->stopAllActions();
		
		Hero->runAction(Repeat::create(animate_up, Distance / Speed/0.4f));
		Hero->runAction(MoveTo::create(Distance / Speed, Vec2(x, y)));
		break;
	case Hero::Direction::DOWN:
		Hero->stopAllActions();
		Hero->runAction(MoveTo::create(Distance / Speed, Vec2(x, y)));
		Hero->runAction(Repeat::create(animate_down, Distance / Speed / 0.4f));

		break;
	case Hero::Direction::NONE:
		break;
	default:
		break;
	}
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