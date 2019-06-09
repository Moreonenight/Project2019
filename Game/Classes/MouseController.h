#pragma once
#include "cocos2d.h"
#include "Houyi.h"
#include "unit.h"
//#include "Money.h"
//#include "GameScene.h"
class HouYi;
class YaSe;
class DaJi;
class MouseController : public cocos2d::Node
{
private:
	cocos2d::EventListenerMouse* listener;
	unit* _unit;
	Vec2 offset;
	short isPaused;
	Vector<unit*>* sprites;
	//Money* m_Money;
public:
	MouseController();
	~MouseController();
	unit* selectFromSprites(Vec2 pos);
	void initListener(unit* Hero,Vector<unit*>* children);
	void initListener(HouYi* houyi,Vector<unit*>* children);
	void initListener(YaSe* yase);
	void initListener(DaJi* daji);
	void changeOffset(const Vec2 a) {
		offset = a;
	}
	void setPause(short x) {
		isPaused = x;
	}
	CREATE_FUNC(MouseController);
};