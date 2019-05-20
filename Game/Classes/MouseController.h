#pragma once
#include "cocos2d.h"
#include "Hero.h"
class MouseController : public cocos2d::Node
{
private:
	Hero* hero;
public:
	MouseController();
	~MouseController();
	void initListener(Sprite* A);
	CREATE_FUNC(MouseController);
};
