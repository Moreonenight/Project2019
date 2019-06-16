#include "unit.h"
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
void unit::initial(unitdata *unitdata, cocos2d::TMXTiledMap* Map, Vector<unit*>* mapUnits,Layer* ammoLayer)

{
	level = 1;
	_map = Map;
	data = unitdata;
	AI = 1;
	unitsOnMap = mapUnits;
	AmmoLayer = ammoLayer;
	myMenu = Menu::create();
	CanAttack = true;
	EquipmentPostion[0] = Vec2(793, 104); EquipmentPostion[1] = Vec2(858, 104); EquipmentPostion[2] = Vec2(923, 104);
	EquipmentPostion[3] = Vec2(793, 39); EquipmentPostion[4] = Vec2(858, 39); EquipmentPostion[5] = Vec2(923, 39);
	bool EnemeyorAlley;
	GettingAttack = false;
	//addChild(hp, 3);
	id = data->getUnitid();
	Equipment("FALSE");
	//id未确定
	//Velocity = data->getVelocity();
	moveSpeed = data->getMoveSpeed();
	level = 1; 
	KillHero = 0; KillSoldiers = 0; deathnumber = 0;
	damage = data->getDamage();
	InitDamage = damage;//对于塔,想记录一下最初始的攻击力是多少,便于后续恢复
	ammoSpeed = data->getAmmoSpeed();
	ASPD = data->getASPD(); 
	defenceOfPhysical = data->getDefenceOfPhysical();
	defenceOfMagic = data->getDefenceOfMagic();
	canAttack = true;
	hp = HP::create();
	hp->changeID(id);
	if (data->getUnitid()[1] == 'r')
	{
		EnemeyorAlley = true;
	}
	else
		EnemeyorAlley = false;
	hp->initial(HP::HpinitialData(data->getMaxHp(), data->getRecoverOfHp(), getPosition(), getContentSize(), Map, EnemeyorAlley));
	hp->changeVel(data->getRecoverOfHp());
	_map->addChild(hp, 5);

	//生成经验
	if (id[0] == 'H') {
		exp = Exp::create();
		exp->initial(1, _map);
		_map->addChild(exp, 5);
		mana = Mana::create();
		mana->changeID(id);
		mana->initial(Mana::ManainitialData(data->getMaxMana(), getPosition(), Map));
		_map->addChild(mana, 5);
	}
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
Sprite* unit::attack(unit *target)
{
	
	auto id1 = this->getid(); auto id2 = target->getid(); 
	if (id1[1] == id2[1]) {
		return NULL;
	}
	if (canAttack == false) return NULL;
	canAttack = false;
	if (getid()[0] != 'T') {
		auto aniCache = AnimationCache::getInstance();
		switch (getDir(getPosition(), target->getPosition())) {
		case Direction::RIGHT:
			if (getChildByTag(20) != nullptr) {}
			else {
				stopAllActions();
				runAction(Animate::create(aniCache->getAnimation(id + "right_attack")))->setTag(20); break;
			}
		case Direction::LEFT:			
			if (getChildByTag(21) != nullptr) {}
			else {
				stopAllActions();
				runAction(Animate::create(aniCache->getAnimation(id + "left_attack")))->setTag(21); break;
			}
		case Direction::UP:
			if (getChildByTag(21) != nullptr) {}
			else {
				stopAllActions();
				runAction(Animate::create(aniCache->getAnimation(id + "up_attack")))->setTag(22); break;
			}
		case Direction::DOWN:
			if (getChildByTag(21) != nullptr) {}
			else {
				stopAllActions(); runAction(Animate::create(aniCache->getAnimation(id + "down_attack")))->setTag(23); break;
			}
		}
	}

	ammo *amo = ammo::create();
	amo->initial(this->getAmmoFrameName(), this->getid(), getPosition(), getCurDamage(), getAmmoSpeed());
	if (getid()[0] == 'B'&&getid()[2] == '1') { amo->setVisible(0); }	
	AmmoLayer->addChild(amo, 6);
	target->getAttacked(amo);
	schedule(schedule_selector(unit::freshASPD), 0, 1, 1.0 / ASPD);	
	return amo;
}
void unit::attackTo(unit * target)
{
	Vec2 destination = target->getPosition();
	float angle = CC_RADIANS_TO_DEGREES((destination - getPosition()).getAngle());

	if ((getPosition() - destination).length() > (data->getAttackRange())&& getid()[0] != 'T') {
		if (getActionByTag(20) != nullptr) { stopActionByTag(20); }
		if (getActionByTag(21) != nullptr) { stopActionByTag(21); }
		if (getActionByTag(22) != nullptr) { stopActionByTag(22); }
		if (getActionByTag(23) != nullptr) { stopActionByTag(23); }
		moveDirectionByKey(getDir(angle), destination);
	}
	
	else attack(target);
}
void unit::attackTo(Vec2 destination)
{	
	
}

unit* unit::getUnitWithId(std::string id)
{
	auto it = unitsOnMap->begin();
	for (; it < unitsOnMap->end(); ++it) {
		if ((*it)->getid()[0] != 'H') { continue; }
		else if ((*it)->getid() == id) {
			return (*it);
		}
	}
	return nullptr;
}
bool unit::addEquipment(std::string itemId,Layer* equipmentlayer,Layer* shoplayer)
{
	if (shoplayer->getChildByTag(887) != nullptr) { shoplayer->removeChildByTag(887); }
	if (shoplayer->getChildByTag(888) != nullptr) { shoplayer->removeChildByTag(888); }
	if (shoplayer->getChildByTag(889) != nullptr) { shoplayer->removeChildByTag(889); }
	if (shoplayer->getChildByTag(890) != nullptr) { shoplayer->removeChildByTag(890); }
	if (shoplayer->getChildByTag(891) != nullptr) { shoplayer->removeChildByTag(891); }
	auto item = Equipment(itemId);
	if (this->getGold() < item.Price) { 
		auto Money = Label::create("Your Money is not enough", "fonts/Arial.ttf", 20);
		Money->enableGlow(Color4B::MAGENTA);
		Money->setPosition(Director::getInstance()->getVisibleSize().width / 2, 250);
		shoplayer->addChild(Money, 0, 887);
		return false; }
	for (int count = 0; count < 6; ++count) {
		if (!equip[count].isOccupied) {
			
			if (itemId == "Shoe")
			{
				auto shoe = Sprite::create("item/shoe_normal.png");
				shoe->setPosition(EquipmentPostion[count]);
				equipmentlayer->addChild(shoe,1,count);
				auto Label_1 = Label::create("Congratulations on the success of your purchase.\nYour speed has increased a lot.", "fonts/Arial.ttf", 20);
				Label_1->enableGlow(Color4B::MAGENTA);
				Label_1->setPosition(Director::getInstance()->getVisibleSize().width / 2, 250);
				shoplayer->addChild(Label_1,0,888);
			}
			else if (itemId == "Hat")
			{
				auto hat = Sprite::create("item/hat_normal.png");
				hat->setPosition(EquipmentPostion[count]);
				equipmentlayer->addChild(hat, 1, count);
				auto Label_2 = Label::create("Congratulations on the success of your purchase.\nYour HP has increased a lot.", "fonts/Arial.ttf", 20);
				Label_2->enableGlow(Color4B::MAGENTA);
				Label_2->setPosition(Director::getInstance()->getVisibleSize().width / 2, 250);
				shoplayer->addChild(Label_2, 0, 889);
			}
			else
			{
				auto sword = Sprite::create("item/shield_normal.png");
				sword->setPosition(EquipmentPostion[count]);
				equipmentlayer->addChild(sword, 1, count);
				auto Label_3 = Label::create("Congratulations on the success of your purchase.\nYour Damage has increased a lot.", "fonts/Arial.ttf", 20);
				Label_3->enableGlow(Color4B::MAGENTA);
				Label_3->setPosition(Director::getInstance()->getVisibleSize().width / 2, 250);
				shoplayer->addChild(Label_3, 0, 890);
			}
			equip[count] = item;
			equip[count].isOccupied = true;
			this->changeGold(-item.Price);
			this->changeDamage(item.plusDamage);
			this->changeMoveSpeed(item.plusMoveSpeed);
			this->changeMaxHp(item.plusMaxHp);
			return true;
		}
		if(count==5){
			auto Label_4 = Label::create("You have already have 6 equipments.\nYou can't buy more.", "fonts/Arial.ttf", 20);
			Label_4->enableGlow(Color4B::MAGENTA);
			Label_4->setPosition(Director::getInstance()->getVisibleSize().width / 2, 250);
			shoplayer->addChild(Label_4, 0, 891);
		}
	}
	return false;
}
bool unit::sellEquipment(int number, Layer* equipmentlayer, Layer* shoplayer)
{
	if (shoplayer->getChildByTag(887) != nullptr) { shoplayer->removeChildByTag(887); }
	if (shoplayer->getChildByTag(888) != nullptr) { shoplayer->removeChildByTag(888); }
	if (shoplayer->getChildByTag(889) != nullptr) { shoplayer->removeChildByTag(889); }
	if (shoplayer->getChildByTag(890) != nullptr) { shoplayer->removeChildByTag(890); }
	if (shoplayer->getChildByTag(891) != nullptr) { shoplayer->removeChildByTag(891); }
	if (shoplayer->getChildByTag(892) != nullptr) { shoplayer->removeChildByTag(892); }
	if (shoplayer->getChildByTag(893) != nullptr) { shoplayer->removeChildByTag(893); }
	if (equip[number].isOccupied)
	{
		auto Label_5 = Label::create("Sold successfully!", "fonts/Arial.ttf", 20);
		Label_5->enableGlow(Color4B::BLACK);
		Label_5->setPosition(700, 150);
		shoplayer->addChild(Label_5, 0, 892);
		equip[number].isOccupied = false;
		this->changeGold(equip[number].Price / 2);
		this->changeDamage(-equip[number].plusDamage);
		this->changeMoveSpeed(-equip[number].plusMoveSpeed);
		this->changeMaxHp(-equip[number].plusMaxHp);
		equipmentlayer->removeChildByTag(number);
		return true;
	}
	else
	{
		auto Label_6 = Label::create("There is nothing!", "fonts/Arial.ttf", 20);
		Label_6->enableGlow(Color4B::BLACK);
		Label_6->setPosition(700, 150);
		shoplayer->addChild(Label_6, 0, 893);
	}
	return true;
}
Vec2 unit::getSpawnPoint() {
	auto group = _map->getObjectGroup("hero");
	auto blueSpawnPoint = group->getObject("BlueSpawnpoint");
	auto redSpawnPoint = group->getObject("RedSpawnpoint");
	float bluex = blueSpawnPoint["x"].asFloat();
	float bluey = blueSpawnPoint["y"].asFloat();
	float redx = redSpawnPoint["x"].asFloat();
	float redy = redSpawnPoint["y"].asFloat();
	if (getid()[1] == 'r') {
		return Vec2(redx, redy);
	}
	else {
		return Vec2(bluex, bluey);
	}
}
void unit::stop()
{
	;
}
unit::~unit()
{
//	hp->~HP();
//	delete(this);
}
