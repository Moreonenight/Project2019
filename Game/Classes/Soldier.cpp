#include "Soldier.h"

#define CENTERX origin.x+visibleSize.width/2
#define CENTERY origin.y+visibleSize.height/2
USING_NS_CC;

bool Soldier::Soldierinit(string Soldiername,int number,cocos2d::TMXTiledMap* Map, Vector<unit*>* mapUnits, Vector<Soldier*>* _MyTeam,Layer* ammoLayer)
{
	MyTeam = _MyTeam;
	_ammolayer = ammoLayer;
	auto data = new(unitdata);
	data->initial(Soldiername);
	initial(data, Map, mapUnits, ammoLayer);
	auto Act = Animate::create(AnimationCache::getInstance()->getAnimation(Soldiername +"up_stand"));
	setScale(0.6);
	runAction(Act);
	if (getid()[1] == 'r'&&getid()[2] == '1'&&number == 1)
	{
		setPosition(1700, 1350);
		this->changeGold(32);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '2'&&number == 1)
	{
		setPosition(1850, 1300);
		this->changeGold(32);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '3'&&number == 1)
	{
		setPosition(1950, 1250);
		this->changeGold(45);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '1'&&number == 2)
	{
		setPosition(1750, 1300);
    this->changeGold(32);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '2'&&number == 2)
	{
		setPosition(1800, 1250);
    this->changeGold(32);
	}
	else if (getid()[1] == 'r'&&getid()[2] == '3'&&number == 2)
	{
		setPosition(1850, 1200);
    this->changeGold(45);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '1'&&number == 1)
	{
		setPosition(490, 410);
    this->changeGold(32);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '2'&&number == 1)
	{
		setPosition(630, 340);
    this->changeGold(32);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '3'&&number == 1)
	{
		setPosition(700, 270);
    this->changeGold(45);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '1'&&number == 2)
	{
		setPosition(390, 340);
    this->changeGold(32);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '2'&&number == 2)
	{
		setPosition(460, 270);
    this->changeGold(32);
	}
	else if (getid()[1] == 'b'&&getid()[2] == '3'&&number == 2)
	{
		setPosition(530, 200);
		this->changeGold(45);
	}
	scheduleUpdate();
	return true;
}


bool Soldier::AttackingJudgeAI()
{
	stopAllActions();
	if (getAttackingTarget() == nullptr&&GetAlreadydead()==false)
	{
		if (getid()[1] == 'r')
		{
			moveDirectionByKey(getDir(getPosition(), Vec2(300, 180)), Vec2(300, 180));
		}
		else if (getid()[1] == 'b')
		{
			moveDirectionByKey(getDir(getPosition(), Vec2(1930, 1430)), Vec2(1930, 1430));
		}

	}
	else if(getAttackingTarget() != nullptr&&GetAlreadydead() == false) {
		attackTo(getAttackingTarget());
	
		}
	return true;
}

int Soldier::getDamage(int delta, std::string fromId) {
	if (hp->getCur() < delta) {
		die(fromId);
	}
	if (GetAlreadydead() == false) {
		hp->changeCur((-delta)*(float)((100.0 - this->getDefenceOfPhysical()) / 100.0));
		return hp->getCur();
	}

}
void Soldier::die(std::string fromId)
{
	ChangeAlreadydead(true);
	changeDeath(1);
	if (fromId[0] == 'H') {
		unit* killUnit = getUnitWithId(fromId);
		if (killUnit != nullptr) {
			killUnit->changeGold(this->getGold());
			killUnit->addCurExp(30);
			killUnit->changeKillSoldiers(1);
		}
	}
	if (!DeleteFlag)
	{
		for (auto it = unitsOnMap->begin(); it < unitsOnMap->end(); it++)
		{
			if (static_cast<Soldier*>(*it) == this)
			{
				if (unitsOnMap->size() == 1) { unitsOnMap->clear(); break; }
				else
				{
					it = unitsOnMap->erase(it);
					if (it == unitsOnMap->end())
					{
						break;
					}
				}
			}
		}
		//this->setPosition(-1000, -1000);//remove后英雄还可选中地图上不存在的单位？
		this->getHp()->curBlood->removeFromParent();
		this->getHp()->emptyBlood->removeFromParent();
		this->getHp()->bloodrect->removeFromParent();
		this->unscheduleUpdate();
		this->getHp()->unscheduleUpdate();
		this->removeFromParent();
		DeleteFlag = true;
	}
}

void Soldier::update(float dt) {
	hp->follow(getPosition());
	auto it = ammosOnWay.begin();
	if (!ammosOnWay.empty()) {
		for (; it < ammosOnWay.end(); it++) {
			auto Dis = (this->getPosition() - (*it)->getPosition()).length();
			auto id1 = this->getid(); auto id2 = (*it)->getid();
			if (Dis < 100 && id1[1] != id2[1])
			{
				auto Damage = (*it)->getDamage();
				this->getDamage(Damage, (*it)->getid());
				(*it)->removeFromParentAndCleanup(1);
				//if (it == (ammosOnWay.end() - 1)) { ammosOnWay.clear(); break; }
				if (ammosOnWay.size() == 1) { ammosOnWay.clear(); break; }
				else
				{
					it = ammosOnWay.erase(it);
					if (it == ammosOnWay.end())
					{
						break;
					}
				}
			}
			else {
				(*it)->changeTargetPosition(getPosition());
			}
		}
	}
	
	if (this->canAttack == 1)return;
	else { this->canAttack = 1; return; }
}