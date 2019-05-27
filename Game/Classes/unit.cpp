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
	//idδȷ��
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
	//Unitdata�����Ż�
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
	


	pAC->addAnimation(animation_down, "animation_down");

	*/

	//double Distancex = abs(Hero->getPositionX() - x);//x��ȡ��굱ǰxλ��
	//double Distancey = abs(Hero->getPositionY() - y);//y��ȡ��굱ǰyλ��
	//double Distance = sqrt(Distancex*Distancex + Distancey * Distancey);//����������Ŀ������
	auto pAC = AnimationCache::getInstance();
	Vec2 a = Hero->getPosition() - e; 
	float Distance = a.length();
	double Speed = 100;//�����ٶ�
	Animation* up_walk= pAC->getAnimation(Hero->getid()+"up_walk");
	Animation* down_walk = pAC->getAnimation(Hero->getid() + "down_walk");
	Animation* left_walk = pAC->getAnimation(Hero->getid() + "left_walk");
	Animation* right_walk = pAC->getAnimation(Hero->getid() + "right_walk");
		
	Animate* animate_up = Animate::create(up_walk);
	Animate* animate_down = Animate::create(down_walk);
	Animate* animate_left = Animate::create(left_walk);
	Animate* animate_right = Animate::create(right_walk);

	auto _move = MoveTo::create(Distance / Speed, e);
	Hero->stopAllActions();
	switch (direction)
	{
	case unit::Direction::LEFT:
		Hero->runAction(animate_left);
		Hero->runAction(_move);
		if(Hero->getPosition() == e)
			Hero->runAction(Animate::create(pAC->getAnimation(Hero->getid() + "left_stand")));
		//Hero->runAction(animate_left);
	//	Hero->runAction(MoveTo::create(Distance / Speed, e));
		break;
	case unit::Direction::RIGHT:
		Hero->runAction(animate_right);
		Hero->runAction(_move);
		if (Hero->getPosition() == e)
			Hero->runAction(Animate::create(pAC->getAnimation(Hero->getid() + "right_stand")));
		break;
	case unit::Direction::UP:

		Hero->runAction(animate_up);
		Hero->runAction(_move);
		if (Hero->getPosition() == e)
			Hero->runAction(Animate::create(pAC->getAnimation(Hero->getid() + "up_stand")));
		//Hero->runAction();

		break;
	case unit::Direction::DOWN:
		Hero->runAction(animate_down);
		Hero->runAction(_move);
		if (Hero->getPosition() == e)
			Hero->runAction(Animate::create(pAC->getAnimation(Hero->getid() + "down_stand")));
		break;
	case unit::Direction::NONE:
		break;
	default:
		break;
	}
	//id��Ҫ��������
	/*auto aniCache = AnimationCache::getInstance();
	if (angle <= 45.0&&angle > -45.0) runAction(Animate::create(aniCache->getAnimation(id + "right_walk")));
	else if (angle > 45.0&&angle <= 135.0) runAction(Animate::create(aniCache->getAnimation(id + "back_walk")));
	else if (angle > 135.0 || angle <= -135.0) runAction(Animate::create(aniCache->getAnimation(id + "left_walk")));
	else if (angle > -135.0&&angle <= -45.0)runAction(Animate::create(aniCache->getAnimation(id + "front_walk")));
	runAction(MoveTo::create((((destination - getPosition()).length()) / Velocity.length()), destination));*/

}
Sprite* unit::attack(unit * target)//���ع��������ĵ�������ָ�룬���԰����ӵ�layer��ȥ��
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
