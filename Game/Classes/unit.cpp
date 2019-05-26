#include "unit.h"


void unit::stop()
{
	this->stopAllActions();
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
	//Unitdata后续优化
	/*Vector<SpriteFrame*> animFrames_up;
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


	pAC->addAnimation(animation_down, "animation_down");
	Animate* animate_down = Animate::create(pAC->getAnimation("animation_down"));
	Animate* animate_left = Animate::create(animation_left);
	Animate* animate_right = Animate::create(animation_right);
	Animate* animate_up = Animate::create(animation_up);
	*/

	//double Distancex = abs(Hero->getPositionX() - x);//x获取光标当前x位置
	//double Distancey = abs(Hero->getPositionY() - y);//y获取光标当前y位置
	//double Distance = sqrt(Distancex*Distancex + Distancey * Distancey);//计算人物与目标点距离
	auto pAC = AnimationCache::getInstance();
	Vec2 a = Hero->getPosition() - e; 
	float Distance = a.length();
<<<<<<< HEAD
	double Speed = 100;//控制速度
	//auto pAC = AnimationCache::getInstance();
	//auto animationleftwalk = pAC->getAnimation(Hero->getid() + "left_walk");
//	auto animateleftwalk = Animate::create(animationleftwalk);
	//auto repeatleftwawlk = Repeat::create(animateleftwalk, Distance / Speed / 0.4f);
=======
	double Speed = 200;//控制速度
>>>>>>> Amonkey
	switch (direction)
	{
	case unit::Direction::LEFT:

		Hero->stopAllActions();
		Hero->runAction(Animate::create(pAC->getAnimation(Hero->getid() + "left_walk")));
		Hero->runAction(MoveTo::create(Distance / Speed, e));
		break;
	case unit::Direction::RIGHT:
		Hero->stopAllActions();
		Hero->runAction(Animate::create(pAC->getAnimation(Hero->getid() + "right_walk")));
		Hero->runAction(MoveTo::create(Distance / Speed, e));
		break;
	case unit::Direction::UP:

		Hero->stopAllActions();

		Hero->runAction(Animate::create(pAC->getAnimation(Hero->getid() + "up_walk")));
		Hero->runAction(MoveTo::create(Distance / Speed, e));
		break;
	case unit::Direction::DOWN:
		Hero->stopAllActions();
		Hero->runAction(Animate::create(pAC->getAnimation(Hero->getid() + "down_walk")));
		Hero->runAction(MoveTo::create(Distance / Speed, e));
		break;
	case unit::Direction::NONE:
		break;
	default:
		break;
	}
	//id需要后续处理
	/*auto aniCache = AnimationCache::getInstance();
	if (angle <= 45.0&&angle > -45.0) runAction(Animate::create(aniCache->getAnimation(id + "right_walk")));
	else if (angle > 45.0&&angle <= 135.0) runAction(Animate::create(aniCache->getAnimation(id + "back_walk")));
	else if (angle > 135.0 || angle <= -135.0) runAction(Animate::create(aniCache->getAnimation(id + "left_walk")));
	else if (angle > -135.0&&angle <= -45.0)runAction(Animate::create(aniCache->getAnimation(id + "front_walk")));
	runAction(MoveTo::create((((destination - getPosition()).length()) / Velocity.length()), destination));*/

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
