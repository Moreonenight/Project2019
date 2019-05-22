
#include "HP.h"

/////////////////////////////////////////////////////////
#define HERO 0
#define OPP_HERO 1
#define BING 2
#define OPP_BING 3
/////////////////////////////////////////////////////////

int HP::getMax() {
	return this->max_HP;
}

int HP::getCur() {
	return this->cur_Hp;
}

void HP::changeCur(int delta) {
	int changedHP = cur_Hp + delta;
	if (changedHP <= 0){cur_Hp = 0;u->die();}
	else if (changedHP > max_HP) cur_Hp = max_HP;
	else cur_Hp = changedHP;
	return;
}

void HP::changeMax(int delta) {
	int cdmax = max_HP + delta;
	if (cdmax > 0) {
		max_HP = cdmax;	for (int i = max_HP / 1000; i; i--) {
			Hp1000 = create("../../res/HP/1000hp.png");
			if (Hp1000 == NULL) return;
			Hp1000->setPosition(bloodrect->getPositionX() + i * (1000.0 / max_HP)*bloodrect->getContentSize().width,
				bloodrect->getPositionY() + bloodrect->getContentSize().height - Hp1000->getContentSize().height);
		}
	}
	else CCLOG("MaxBloodError");
	return;
}


void HP::changeVel(int delta) {
	velocity += delta;
	return;
}

void HP::initial(unit *nunit)
{
	if (nunit != NULL) u = nunit;
	else CCLOG("血量未指定单位");
	if (u == NULL) return;

	//位置信息要重新修改，考虑实际图片像素问题
	bloodrect = create("../../res/HP/bloodrect.png");
	bloodrect->setPosition(u->getPositionX(), u->getPositionY() + 10);
	setScaleX(((float)(u->getContentSize().width)) / (bloodrect->getContentSize().width));
	setScaleY(10.0 / bloodrect->getContentSize().height);
	this->addChild(bloodrect, 0);
	
	if (u->getid()[0] == 'E')
		curBlood = create("../../res/HP/RedBlood.png");
	else if (u->getid()[0] == 'A')
		curBlood = create("../../res/HP/GreenBlood.png");

	curBlood->setPosition(bloodrect->getPositionX(), bloodrect->getPositionY());
	curBlood->setScaleY((float)bloodrect->getContentSize().height / curBlood->getContentSize().height);
	curBlood->setScaleX((float)bloodrect->getContentSize().width / curBlood->getContentSize().width);
	this->addChild(curBlood, 1);

	for (int i = max_HP / 1000; i; i--) {
		Hp1000 = create("../../res/HP/1000hp.png");
		if (Hp1000 == NULL) return;
		Hp1000->setPosition(bloodrect->getPositionX() + (i * (1000.0 / max_HP)-0.5) * bloodrect->getContentSize().width,
			bloodrect->getPositionY() + bloodrect->getContentSize().height - Hp1000->getContentSize().height);
	}
	this->addChild(Hp1000, 2);

	emptyBlood = create("../../res/HP/emptyrect.png");
	emptyBlood->setPosition(bloodrect->getPositionX() + bloodrect->getContentSize().width - emptyBlood->getContentSize().width
		, bloodrect->getPositionY());
	emptyBlood->setScaleX(bloodrect->getContentSize().width/emptyBlood->getContentSize().width);
	this->addChild(emptyBlood, 0);
	return;
}

void HP::fresh() {
	changeCur(velocity);
	curBlood->setScaleX(((float)cur_Hp/max_HP)*(bloodrect->getContentSize().width / curBlood->getContentSize().width));
	return;
}

unit::unit(unitdata &unitdata)
{
	data = &unitdata;
	hp = new(HP);
	hp->initial(this); addChild(hp, 0);
	//Velocity = data->getVelocity();
	level = 1; damage = data->getDamage();
	gold = 0; ASPD = data->getASPD(); canAttack = true;
	id = data->getUnitid(); //dpm = data->getDpm();
	createWithSpriteFrameName(id + "front_stand");
	//setPosition(data->getPosition());
	//Scheduler::schedule(schedule_selector(unit::freshCanAttack), 1.0f/ASPD);
}
HP::~HP() {
	delete(this);
}
inline int unit::getMaxHp() { return hp->getMax(); }inline void unit::changeMaxHp(int delta) { hp->changeMax(delta); }
unit::~unit()
{
	hp->~HP();
	delete(this);
}