#pragma once
#include "cocos2d.h"
#include "unit.h"
//#include "Money.h"
//#include "GameScene.h"
class MouseController : public cocos2d::Node
{
private:
	cocos2d::EventListenerMouse* listener;
	unit* _unit;
	Vec2 offset;
	short isPaused;
	//Money* m_Money;
public:
	MouseController();
	~MouseController();
	void initListener(unit* Hero);
	void changeOffset(const Vec2 a) { 
		offset = a; }
	void setPause(short x) {
		isPaused = x;
	}
	CREATE_FUNC(MouseController);
};
