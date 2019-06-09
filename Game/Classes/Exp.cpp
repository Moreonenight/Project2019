#include "Exp.h"

void Exp::initial(int level, cocos2d::TMXTiledMap*map)
{
	Level=level;
	cur_Exp=0;
	Max_Exp = expNeeded[level];
	_map = map;
	ExpRect = Sprite::create("Exp/exprect.png");
	ExpRect->setPosition(Vec2::ZERO);
	ExpRect->setScaleX(1);
	ExpRect->setScaleY(0.4f);
	ExpRect->setAnchorPoint(Vec2(0, 0.5f));
	ExpLine = Sprite::create("Exp/exp.png");
	ExpLine->setPosition(Vec2(-35,0));
	ExpLine->setScaleX(1);
	ExpLine->setScaleY(0.9f);
	ExpLine->setAnchorPoint(Vec2::ZERO);
	_map->addChild(ExpLine,5);
	_map->addChild(ExpRect,5);
	scheduleUpdate();
}

void Exp::update(float dt) 
{
	ExpLine->setScaleX(((float)cur_Exp/Max_Exp)*(ExpRect->getContentSize().width / ExpLine->getContentSize().width));
}
void Exp::follow(Vec2 pos) {
	ExpLine->setPosition(pos.x - 78, pos.y+81);
	ExpRect->setPosition(pos.x - 78, pos.y+86);
}

void Exp::changeCurExp(int delta) {
	if (cur_Exp + delta >= Max_Exp) {
		if (Level == 8) { cur_Exp = Max_Exp; return; }
		else {
			changeLevel(1);
			Max_Exp = expNeeded[Level];
			cur_Exp = 0;
		}
	}
	else {
		cur_Exp += delta;
	}
}
