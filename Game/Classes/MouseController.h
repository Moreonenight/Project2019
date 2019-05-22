#pragma once
#include "cocos2d.h"
#include "unit.h"
//#include "Money.h"
#include "GameScene.h"
class MouseController : public cocos2d::Node
{
private:
	unit* _unit;
	//Money* m_Money;
public:
	MouseController();
	~MouseController();
	void initListener(Sprite* A);
	CREATE_FUNC(MouseController);
};
