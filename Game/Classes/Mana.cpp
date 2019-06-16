#include "Mana.h"

void Mana::initial(ManainitialData data)
{
	cur_Mana = data.max;
	Max_Mana = data.max;
	_map = data._map;
	if (ManaID[2] == 'H')
	{
		RecoverMana = 16;
	}
	else if (ManaID[2] == 'D')
	{
		RecoverMana = 18;
	}
	else if (ManaID[2] == 'Y')
	{
		RecoverMana = 0;
	}
	ManaRect = Sprite::create("Mana/manarect.png");
	ManaRect->setPosition(Vec2::ZERO);
	ManaRect->setScaleX(1);
	ManaRect->setScaleY(0.4f);
	ManaRect->setAnchorPoint(Vec2(0, 0.5f));
	_map->addChild(ManaRect, 5);
	if (ManaID[2] != 'Y')
	{
		ManaLine = Sprite::create("Mana/mana.png");
		ManaLine->setPosition(Vec2::ZERO);
		ManaLine->setScaleX(1);
		ManaLine->setScaleY(0.9f);
		ManaLine->setAnchorPoint(Vec2::ZERO);
		_map->addChild(ManaLine, 5);
		ManaLine->setScaleX((float)ManaLine->getContentSize().width / ManaRect->getContentSize().width);
		scheduleUpdate();
	}
	
}

void Mana::update(float dt)
{
	ManaLine->setScaleX(((float)cur_Mana / Max_Mana)*(ManaRect->getContentSize().width / ManaLine->getContentSize().width));
	Timer++;
	if (Timer == 225)
	{
		changeCurMana(RecoverMana);
		Timer = 0;
	}
	
}
void Mana::follow(Vec2 pos) {
	if (ManaID[2]!='Y')
	{
		ManaLine->setPosition(pos.x - 78, pos.y + 90);
		ManaRect->setPosition(pos.x - 78, pos.y + 95);
	}
	else
	{
		ManaRect->setPosition(pos.x - 78, pos.y + 95);
	}
}
