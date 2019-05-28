#include "unit.h"

void unit::stop()
{
	;
}

void unit::initial(unitdata *unitdata)
{
	data = unitdata;
	hp = HP::create();
	hp->initial(getPosition(), getContentSize(), 0/*atoi((const char*)id[0])*/); 
	addChild(hp, 0);
	id = data->getUnitid();
	//id未确定
	//Velocity = data->getVelocity();
	level = 1; 
	/*damage = data->getDamage();
	ammoSpeed = data->getAmmoSpeed();
	gold = 0;
	ASPD = data->getASPD(); 
	canAttack = true;
 
	*/
	//dpm = data->getDpm();
	//setPosition(data->getPosition());
	//Scheduler::schedule(schedule_selector(unit::freshCanAttack), 1.0f/ASPD);
}

void unit::moveDirectionByKey(unit::Direction direction, Vec2 e, unit* Hero)
{

	Vec2 a = Hero->getPosition() - e; //英雄当前位置与目标位置连成的向量
	float Distance = a.length();//计算向量的长度即为将要行走的距离
	double Speed = 200;//控制速度
	auto Singleton = AnimationCache::getInstance();//通过动画缓存获取单例对象
	/*加载走动动画*/
	Animation* up_walk= Singleton->getAnimation(Hero->getid()+"up_walk");
	Animation* down_walk = Singleton->getAnimation(Hero->getid() + "down_walk");
	Animation* left_walk = Singleton->getAnimation(Hero->getid() + "left_walk");
	Animation* right_walk = Singleton->getAnimation(Hero->getid() + "right_walk");
	Animate* animate_up = Animate::create(up_walk);
	Animate* animate_down = Animate::create(down_walk);
	Animate* animate_left = Animate::create(left_walk);
	Animate* animate_right = Animate::create(right_walk);
	
	auto Moving = MoveTo::create(Distance / Speed, e);//定义移动函数，第一个参数为时间
	/*定义移动完成的回调函数*/
	auto CallBackLeft = CallFunc::create([Hero,Singleton]() {
		Hero->stopAllActions();
		Hero->runAction(Animate::create(Singleton->getAnimation(Hero->getid() + "left_stand")));
	});
	auto CallBackRight = CallFunc::create([Hero, Singleton]() {
		Hero->stopAllActions();
		Hero->runAction(Animate::create(Singleton->getAnimation(Hero->getid() + "right_stand")));
	});
	auto CallBackUp = CallFunc::create([Hero, Singleton]() {
		Hero->stopAllActions();
		Hero->runAction(Animate::create(Singleton->getAnimation(Hero->getid() + "up_stand")));
	});
	auto CallBackDown = CallFunc::create([Hero, Singleton]() {
		Hero->stopAllActions();
		Hero->runAction(Animate::create(Singleton->getAnimation(Hero->getid() + "down_stand")));
	});
	/*Action标签作如下规定：
	向上跑动动画：1；向下跑动动画：2；向左跑动动画：3；向右跑动动画：4；
	向上走动：5；向下走动：6；向左走动：7；向右走动：8；
	向上战立：9；向下战立：10；向左战立：11；向右战立：12.
	*/
	switch (direction)
	{
	case unit::Direction::UP:
		if (Hero->getActionByTag(1) == nullptr)
		{
			Hero->stopAllActions();
			Hero->runAction(RepeatForever::create(animate_up))->setTag(1);
		}
		else
		{
			Hero->stopActionByTag(5);
		}
		Hero->runAction(Sequence::create(Moving, CallBackUp, nullptr))->setTag(5);
		break;
	case unit::Direction::DOWN:
		if (Hero->getActionByTag(2) == nullptr)
		{
			Hero->stopAllActions();
			Hero->runAction(RepeatForever::create(animate_down))->setTag(2);
		}
		else
		{
			Hero->stopActionByTag(6);
		}
		Hero->runAction(Sequence::create(Moving, CallBackDown, nullptr))->setTag(6);
		break;
	case unit::Direction::LEFT:
		if (Hero->getActionByTag(3) == nullptr)
		{
			Hero->stopAllActions();
			Hero->runAction(RepeatForever::create(animate_left))->setTag(3);
		}
		else
		{
			Hero->stopActionByTag(7);
		}
		Hero->runAction(Sequence::create(Moving, CallBackLeft, nullptr))->setTag(7);
		break;
	case unit::Direction::RIGHT:
		if (Hero->getActionByTag(4) == nullptr)
		{
			Hero->stopAllActions();
			Hero->runAction(RepeatForever::create(animate_right))->setTag(4);
		}
		else
		{
			Hero->stopActionByTag(8);
		}
		Hero->runAction(Sequence::create(Moving, CallBackRight, nullptr))->setTag(8);

		break;
	case unit::Direction::NONE:
		break;
	default:
		break;
	}
}
Sprite* unit::attack(unit * target)//返回攻击产生的弹道对象指针，可以把它加到layer中去。
{
	if (canAttack == false) return NULL;
	stop();
	auto aniCache = AnimationCache::getInstance();
	canAttack = false;
	float angle = CC_RADIANS_TO_DEGREES((target->getPosition() - getPosition()).getAngle());
	if (angle <= 45.0&&angle > -45.0) runAction(Animate::create(aniCache->getAnimation(id + "right_attack")));
	else if (angle > 45.0&&angle <= 135.0) runAction(Animate::create(aniCache->getAnimation(id + "back_attack")));
	else if (angle > 135.0 || angle <= -135.0) runAction(Animate::create(aniCache->getAnimation(id + "left_attack")));
	else if (angle > -135.0&&angle <= -45.0)runAction(Animate::create(aniCache->getAnimation(id + "front_attack")));
	//delay

	//runAction();
	ammo *amo = ammo::create();
	amo->initial(this->getAmmoFrameName(), getPosition(),getDamage(),getAmmoSpeed());//velocity = getAmmoSpeed()*Vec2.length()
	return amo;
}

void unit::attackTo(unit * target)
{
	Vec2 destination = target->getPosition();
	if ((getPosition() - destination).length() > (data->getAttackRange()));// this->moveTo(destination);
	else attack(target);
}

void unit::attackTo(Vec2 destination)
{
}

void unit::die()
{
}



inline int unit::getDamage(int delta) { hp->changeCur(delta); return hp->getCur(); }
inline int unit::getMaxHp() { return hp->getMax(); }inline void unit::changeMaxHp(int delta) { hp->changeMax(delta); }
unit::~unit()
{
//	hp->~HP();
//	delete(this);
}
