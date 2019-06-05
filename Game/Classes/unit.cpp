#include "unit.h"

void unit::stop()
{
	;
}

/*Action标签作如下规定:
跑动动画：
runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation
		  (getid()+		"up_walk"		))))->
		  setTag(1：向上；	2：向下；	3：向左；	4：向右；  );
移动后站立动画：
runAction(Sequence::create(
		 MoveTo::create(Distance / moveSpeed, e),Animate::create(AnimationCache::getInstance()->getAnimation
		 (getid() +    "up_stand"      ), nullptr))->
		 setTag(	5：向上；向下：6；向左：7；向右：8；);
站立动画：
runAction(Animate::create(AnimationCache::getInstance()->getAnimation
		(getid() +		"up_stand"		)))->
		setTag(9：向上站立；10：向下站立；11：向左站立；12：向右站立.)
攻击动画：
	13: 向上攻击	14：向下攻击	15：向左攻击	16：向右攻击
*/

void unit::initial(unitdata *unitdata, cocos2d::TMXTiledMap* Map)
{
	_map = Map;
	data = unitdata;
	id = data->getUnitid();
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
	_map->addChild(hp, 5);
	scheduleUpdate();

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
		runAction(Animate::create(Singleton->getAnimation(getid() + "left_stand")))->setTag(11);
	});
	auto CallBackRight = CallFunc::create([this, Singleton]() {
		stopAllActions();
		runAction(Animate::create(Singleton->getAnimation(getid() + "right_stand")))->setTag(12);
	});
	auto CallBackUp = CallFunc::create([this, Singleton]() {
		stopAllActions();
		runAction(Animate::create(Singleton->getAnimation(getid() + "up_stand")))->setTag(9);
	});
	auto CallBackDown = CallFunc::create([this, Singleton]() {
		stopAllActions();
		runAction(Animate::create(Singleton->getAnimation(getid() + "down_stand")))->setTag(10);
	});

	switch (direction)
	{
	case unit::Direction::UP:
		if (getActionByTag(1) == nullptr)
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
	auto pAC = AnimationCache::getInstance();
	auto CallBackLeft = CallFunc::create([this, pAC]() {
		stopAllActions();
		runAction(Animate::create(pAC->getAnimation(getid() + "left_stand")))->setTag(11);
	});
	auto CallBackRight = CallFunc::create([this, pAC]() {
		stopAllActions();
		runAction(Animate::create(pAC->getAnimation(getid() + "right_stand")))->setTag(12);
	});
	auto CallBackUp = CallFunc::create([this, pAC]() {
		stopAllActions();
		runAction(Animate::create(pAC->getAnimation(getid() + "up_stand")))->setTag(9);
	});
	auto CallBackDown = CallFunc::create([this, pAC]() {
		stopAllActions();
		runAction(Animate::create(pAC->getAnimation(getid() + "down_stand")))->setTag(10);
	});
	if (canAttack == false) return NULL;
	canAttack = false;
	stopAllActions();
	ammo *amo = ammo::create();
	switch (getDir(getPosition(), target->getPosition())) {

	case Direction::
	RIGHT:runAction(Animate::create(pAC->getAnimation(id + "right_attack")))->setTag(16);
		amo->initial(this->getAmmoFrameName(), getPosition() + Vec2(0.0, 30.5), getDamage(), getAmmoSpeed()); break;
	case Direction::
	LEFT:runAction(Animate::create(pAC->getAnimation(id + "left_attack")))->setTag(15);
		amo->initial(this->getAmmoFrameName(), getPosition() + Vec2(0.0, 30.5), getDamage(), getAmmoSpeed());
		break;
	case Direction::
	UP:runAction(Animate::create(pAC->getAnimation(id + "up_attack")))->setTag(13);
		amo->initial(this->getAmmoFrameName(), getPosition(), getDamage(), getAmmoSpeed());
		break;
	case Direction::
	DOWN:runAction(Animate::create(pAC->getAnimation(id + "down_attack")))->setTag(14);
		amo->initial(this->getAmmoFrameName(), getPosition(), getDamage(), getAmmoSpeed());
		break;
	}
	

	target->getAttacked(amo);
	schedule(schedule_selector(unit::freshASPD), 1.0 / ASPD, 0, 0);
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
