#pragma once
#include "cocos2d.h"
#include "unit.h"
//#include "Money.h"
//#include "GameScene.h"
class MouseController : public cocos2d::Node
{
private:
	unit* _unit;
	Vec2 offset;
	//Money* m_Money;
public:
	MouseController();
	~MouseController();
	void initListener(unit* A);
	void changeOffset(const Vec2 a) { 
		offset = a; }
	CREATE_FUNC(MouseController);
};
