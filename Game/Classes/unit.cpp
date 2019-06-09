#include "unit.h"

void unit::stop()
{
	;
}

void unit::initial(unitdata *unitdata, cocos2d::TMXTiledMap* Map, Vector<unit*>* mapUnits)
{
	level = 1;
	_map = Map;
	data = unitdata;
	unitsOnMap = mapUnits;
	bool EnemeyorAlley;
	//addChild(hp, 3);
	id = data->getUnitid();
	
	//idδȷ��
	//Velocity = data->getVelocity();
	moveSpeed = data->getMoveSpeed();
	level = 1; 
	KillHero = 0; KillSoldiers = 0; deathnumber = 0;
	damage = data->getDamage();
	InitDamage = damage;//������,���¼һ�����ʼ�Ĺ������Ƕ���,���ں����ָ�
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

	//���ɾ���
	if (id[0] == 'H') {
		exp = Exp::create();
		exp->initial(1, _map);
		_map->addChild(exp, 5);
	}
	//scheduleUpdate();
	
	//dpm = data->getDpm();
	//setPosition(data->getPosition());
	//((Layer *)(this->getParent()->getParent()))->schedule(schedule_selector(unit::fresh));
	///scheldue����������initialδ���֮ǰ���루��δaddchild��
}

void unit::moveDirectionByKey(unit::Direction direction, Vec2 e)
{

	Vec2 a = getPosition() - e; //Ӣ�۵�ǰλ����Ŀ��λ�����ɵ�����
	float Distance = a.length();//���������ĳ��ȼ�Ϊ��Ҫ���ߵľ���
	///double moveSpeed = 200;//�����ٶ�
	auto Singleton = AnimationCache::getInstance();//ͨ�����������ȡ��������
	/*�����߶�����*/
	Animation* up_walk= Singleton->getAnimation(getid()+"up_walk");
	Animation* down_walk = Singleton->getAnimation(getid() + "down_walk");
	Animation* left_walk = Singleton->getAnimation(getid() + "left_walk");
	Animation* right_walk = Singleton->getAnimation(getid() + "right_walk");
	Animate* animate_up = Animate::create(up_walk);
	Animate* animate_down = Animate::create(down_walk);
	Animate* animate_left = Animate::create(left_walk);
	Animate* animate_right = Animate::create(right_walk);
	
	auto Moving = MoveTo::create(Distance / moveSpeed, e);//�����ƶ���������һ������Ϊʱ��
	/*�����ƶ���ɵĻص�����*/
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
	/*Action��ǩ�����¹涨��
	�����ܶ�������1�������ܶ�������2�������ܶ�������3�������ܶ�������4��
	�����߶���5�������߶���6�������߶���7�������߶���8��
	����ս����9������ս����10������ս����11������ս����12.
	*/
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
Sprite* unit::attack(unit *target)//���ع��������ĵ�������ָ�룬���԰����ӵ�layer��ȥ��
{
	if (canAttack == false) return NULL;
	this->stopAllActions();
	auto aniCache = AnimationCache::getInstance();
	canAttack = false;
	if(getid()[0]!='T'){
	
		switch (getDir(getPosition(), target->getPosition())) {
		case Direction::RIGHT:runAction(Animate::create(aniCache->getAnimation(id + "right_attack")))->setTag(20); break;
		case Direction::LEFT:runAction(Animate::create(aniCache->getAnimation(id + "left_attack")))->setTag(21); break;
		case Direction::UP:runAction(Animate::create(aniCache->getAnimation(id + "up_attack")))->setTag(22); break;
		case Direction::DOWN:runAction(Animate::create(aniCache->getAnimation(id + "down_attack")))->setTag(23); break;
		}
	}

	ammo *amo = ammo::create();
	amo->initial(this->getAmmoFrameName(),this->getid(),getPosition(), getDamage(), getAmmoSpeed());
	if (getid()[2] == '1') { amo->setVisible(0); }
	auto id1 = target->getid(); auto id2 = amo->getid();
	if (id1[1] != id2[1]) {
		_map->addChild(amo, 6);
		target->getAttacked(amo);
	}
	//schedule(schedule_selector(unit::freshASPD), 1.0 / ASPD, 1, 0);
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

inline void unit::changeMaxHp(int delta) { hp->changeMax(delta); }
inline int unit::getMaxHp() { return hp->getMax(); }

unit::~unit()
{
//	hp->~HP();
//	delete(this);
}

//���๦�ܺ���
bool unit::addEquipment(std::string itemName)
{
	auto item = Equipment(itemName);
	if (this->getGold() < item.Price) { return false; }
	for (int count = 0; count < 7; ++count) {
		if (!equip[count].isOccupied) {
			equip[count] = item;
			this->changeGold(-item.Price);
			this->changeDamage(equip[count].plusDamage);
			this->changeMaxHp(equip[count].plusMaxHp);
			this->changeMoveSpeed(equip[count].plusMoveSpeed);
			return true;
		}
	}
	return false;
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

unit::~unit()
{
//	hp->~HP();
//	delete(this);
}
