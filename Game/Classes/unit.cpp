#include "unit.h"

void unit::stop()
{
	;
}

void unit::initial(unitdata *unitdata, cocos2d::TMXTiledMap* Map)
{
	_map = Map;
	data = unitdata;
	
	//addChild(hp, 3);
	
	id = data->getUnitid();
	//id未确定
	//Velocity = data->getVelocity();
	moveSpeed = data->getMoveSpeed();
	level = 1; 
	damage = data->getDamage();
	ammoSpeed = data->getAmmoSpeed();
	ASPD = data->getASPD(); 
	defenceOfPhysical = data->getDefenceOfPhysical();
	defenceOfMagic = data->getDefenceOfMagic();
	canAttack = true;
	hp = HP::create();
	hp->initial(HP::HpinitialData(data->getMaxHp(), data->getRecoverOfHp(), getPosition(), getContentSize(), Map,0));
	hp->changeVel(data->getRecoverOfHp());
	_map->addChild(hp, 5);
	scheduleUpdate();
	
	//dpm = data->getDpm();
	//setPosition(data->getPosition());
	//((Layer *)(this->getParent()->getParent()))->schedule(schedule_selector(unit::fresh));
	///scheldue函数不能在initial未完成之前加入（尚未addchild）
}

void unit::moveDirectionByKey(unit::Direction direction, Vec2 e)
{

	Vec2 a = getPosition() - e; //英雄当前位置与目标位置连成的向量
	float Distance = a.length();//计算向量的长度即为将要行走的距离
	///double moveSpeed = 200;//控制速度
	auto Singleton = AnimationCache::getInstance();//通过动画缓存获取单例对象
	/*加载走动动画*/
	Animation* up_walk= Singleton->getAnimation(getid()+"up_walk");
	Animation* down_walk = Singleton->getAnimation(getid() + "down_walk");
	Animation* left_walk = Singleton->getAnimation(getid() + "left_walk");
	Animation* right_walk = Singleton->getAnimation(getid() + "right_walk");
	Animate* animate_up = Animate::create(up_walk);
	Animate* animate_down = Animate::create(down_walk);
	Animate* animate_left = Animate::create(left_walk);
	Animate* animate_right = Animate::create(right_walk);
	
	auto Moving = MoveTo::create(Distance / moveSpeed, e);//定义移动函数，第一个参数为时间
	/*定义移动完成的回调函数*/
	auto CallBackLeft = CallFunc::create([this,Singleton]() {
		stopAllActions();
		runAction(Animate::create(Singleton->getAnimation(getid() + "left_stand")));
	});
	auto CallBackRight = CallFunc::create([this, Singleton]() {
		stopAllActions();
		runAction(Animate::create(Singleton->getAnimation(getid() + "right_stand")));
	});
	auto CallBackUp = CallFunc::create([this, Singleton]() {
		stopAllActions();
		runAction(Animate::create(Singleton->getAnimation(getid() + "up_stand")));
	});
	auto CallBackDown = CallFunc::create([this, Singleton]() {
		stopAllActions();
		runAction(Animate::create(Singleton->getAnimation(getid() + "down_stand")));
	});
	/*Action标签作如下规定：
	向上跑动动画：1；向下跑动动画：2；向左跑动动画：3；向右跑动动画：4；
	向上走动：5；向下走动：6；向左走动：7；向右走动：8；
	向上战立：9；向下战立：10；向左战立：11；向右战立：12.
	*/
	switch (direction)
	{
	case unit::Direction::UP:
		if (getActionByTag(1) != nullptr)
		{
			stopAllActions();
			runAction(RepeatForever::create(animate_up))->setTag(1);
		}
		else
		{			
			stopActionByTag(5);
		}
		runAction(Sequence::create(Moving, CallBackUp, nullptr))->setTag(5);
		break;
	case unit::Direction::DOWN:
		if (getActionByTag(2) == nullptr)
		{
			stopAllActions();
			runAction(RepeatForever::create(animate_down))->setTag(2);
		}
		else
		{
			stopActionByTag(6);
		}
		runAction(Sequence::create(Moving, CallBackDown, nullptr))->setTag(6);
		break;
	case unit::Direction::LEFT:
		if (getActionByTag(3) == nullptr)
		{
			stopAllActions();
			runAction(RepeatForever::create(animate_left))->setTag(3);
		}
		else
		{
			stopActionByTag(7);
		}
		runAction(Sequence::create(Moving, CallBackLeft, nullptr))->setTag(7);
		break;
	case unit::Direction::RIGHT:
		if (getActionByTag(4) == nullptr)
		{
			stopAllActions();
			runAction(RepeatForever::create(animate_right))->setTag(4);
		}
		else
		{
			stopActionByTag(8);
		}
		runAction(Sequence::create(Moving, CallBackRight, nullptr))->setTag(8);

		break;
	case unit::Direction::NONE:
		break;
	default:
		break;
	}
}
Sprite* unit::attack(unit *target)//返回攻击产生的弹道对象指针，可以把它加到layer中去。
{
	if (canAttack == false) return NULL;
	this->stopAllActions();
	auto aniCache = AnimationCache::getInstance();
	canAttack = false;
	switch (getDir(getPosition(), target->getPosition())) {
	case Direction::RIGHT:runAction(Animate::create(aniCache->getAnimation(id + "right_attack"))); break;
	case Direction::LEFT:runAction(Animate::create(aniCache->getAnimation(id + "left_attack"))); break;
	case Direction::UP:runAction(Animate::create(aniCache->getAnimation(id + "up_attack"))); break;
	case Direction::DOWN:runAction(Animate::create(aniCache->getAnimation(id + "down_attack"))); break;
	}
	ammo *amo = ammo::create();
	amo->initial(this->getAmmoFrameName(), getPosition(), getDamage(), getAmmoSpeed());
	target->getAttacked(amo);
	_map->addChild(amo, 6);
	//((Layer *)(this->getParent()->getParent()))->schedule(schedule_selector(unit::freshASPD), 1.0 / ASPD, 1, 0);
	return amo;
}


void unit::attackTo(unit * target)
{
	Vec2 destination = target->getPosition();
	float angle = CC_RADIANS_TO_DEGREES((destination - getPosition()).getAngle());
	if ((getPosition() - destination).length() > (data->getAttackRange())) {
		moveDirectionByKey(getDir(angle), destination);
	}
	else attack(target);
}


void unit::attackTo(Vec2 destination)
{	
	
}

void unit::die()
{
}



inline int unit::getMaxHp() { return hp->getMax(); }inline void unit::changeMaxHp(int delta) { hp->changeMax(delta); }
unit::~unit()
{
//	hp->~HP();
//	delete(this);
}
