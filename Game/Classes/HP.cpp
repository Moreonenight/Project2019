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
	if (changedHP <= 0){cur_Hp = 0;}
	else if (changedHP > max_HP) cur_Hp = max_HP;
	else cur_Hp = changedHP;
	return;
}

void HP::changeMax(int delta) {
	int cdmax = max_HP + delta;
	if (cdmax > 0) {
		max_HP = cdmax;
	}
	else CCLOG("MaxBloodError");
	return;
}


void HP::changeVel(int delta) {
	velocity += delta;
	return;
}


void HP::initial(HpinitialData data)
{
	
	max_HP = data.max;
	cur_Hp = data.max;
	velocity = data.velocity;
	bool enemyOrAlly = data.enemyOrAlly;
	Size size = Size(Vec2(200.0, 10.0)); //data.size;
	Vec2 position = data.position;
	this->setPosition(position);
	//位置信息要重新修改，考虑实际图片像素问题
	bloodrect = Sprite::create("HP/bloodrect.png");
	bloodrect->setPosition(position.x-100, position.y + 100);
	setScaleX(((float)(size.width)) / (size.width));
	setScaleY(10.0 / bloodrect->getContentSize().height);
	bloodrect->setAnchorPoint(Vec2::ZERO);
	data._map->addChild(bloodrect, 6);
	
	if (enemyOrAlly)
		curBlood = Sprite::create("HP/RedBlood.png");
	else
		curBlood = Sprite::create("HP/GreenBlood.png");

	curBlood->setPosition(bloodrect->getPositionX(), bloodrect->getPositionY());
	curBlood->setScaleY((float)bloodrect->getContentSize().height / curBlood->getContentSize().height);
	curBlood->setScaleX((float)bloodrect->getContentSize().width / curBlood->getContentSize().width);
	curBlood->setAnchorPoint(Vec2::ZERO);
	data._map->addChild(curBlood, 5);

	emptyBlood = Sprite::create("HP/emptyrect.png");
	emptyBlood->setPosition(bloodrect->getPositionX() /*+ bloodrect->getContentSize().width - emptyBlood->getContentSize().width*/
		, bloodrect->getPositionY());
	emptyBlood->setScaleX(bloodrect->getContentSize().width/emptyBlood->getContentSize().width);
	emptyBlood->setScaleY(bloodrect->getContentSize().height / emptyBlood->getContentSize().height);
	emptyBlood->setAnchorPoint(Vec2::ZERO);
	data._map->addChild(emptyBlood, 4);
	this->scheduleUpdate();
	return;
}

void HP::update(float dt) {
	changeCur(velocity);
	curBlood->setScaleX(((float)cur_Hp/max_HP)*(bloodrect->getContentSize().width / curBlood->getContentSize().width));
	/*auto a = curBlood->getContentSize();
	auto b = bloodrect->getPosition();
	auto c = bloodrect->getContentSize();
	auto e = curBlood->getPosition();
	auto d = Vec2(((float)cur_Hp / max_HP)*(bloodrect->getContentSize().width / curBlood->getContentSize().width)bloodrect->getContentSize().width, 0);
	curBlood->setPosition(b - c + d);Vec2(((float)cur_Hp / max_HP)*(bloodrect->getContentSize().width / curBlood->getContentSize().width)*curBlood->getContentSize().width, curBlood->getContentSize().height));*/
	return;
}
HP::~HP() {
	//delete(this);
}

