#include "Mana.h"

void Mana::initial(ManainitialData data)
{
	cur_Mana = data.max;
	Max_Mana = data.max;
	_map = data._map;
	ManaRect = Sprite::create("Mana/manarect.png");
	ManaRect->setPosition(Vec2::ZERO);
	ManaRect->setScaleX(1);
	ManaRect->setScaleY(0.4f);
	ManaRect->setAnchorPoint(Vec2(0, 0.5f));
	ManaLine = Sprite::create("Mana/mana.png");
	ManaLine->setPosition(Vec2::ZERO);
	ManaLine->setScaleX(1);
	ManaLine->setScaleY(0.9f);
	ManaLine->setAnchorPoint(Vec2::ZERO);
	_map->addChild(ManaRect,5);
	_map->addChild(ManaLine,5);
	ManaLine->setScaleX((float)ManaLine->getContentSize().width / ManaRect->getContentSize().width);
	scheduleUpdate();
}

void Mana::update(float dt)
{
	ManaLine->setScaleX(((float)cur_Mana / Max_Mana)*(ManaRect->getContentSize().width / ManaLine->getContentSize().width));
	Timer++;
	if (Timer == 45)
	{
		changeCurMana(15);
		Timer = 0;
	}
	
}
void Mana::follow(Vec2 pos) {
	ManaLine->setPosition(pos.x - 78, pos.y+90);
	ManaRect->setPosition(pos.x - 78, pos.y+95);
}
