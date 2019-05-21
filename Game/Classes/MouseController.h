#pragma once
#include "cocos2d.h"
#include "Hero.h"
#include "Money.h"
#include "GameScene.h"
class MouseController : public cocos2d::Node
{
private:
	Hero* hero;
	Money* m_Money;
public:
	MouseController();
	~MouseController();
	void initListener(Sprite* A);
	CREATE_FUNC(MouseController);
};
