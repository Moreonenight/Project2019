#include "MouseController.h"

using cocos2d::EventListenerMouse;
using cocos2d::NotificationCenter;
using cocos2d::EventMouse;
using cocos2d::Event;
using cocos2d::Rect;
MouseController::MouseController()
{
}


MouseController::~MouseController()
{
}
//初始化
void MouseController::initListener(Sprite* Hero) {
	auto listener = EventListenerMouse::create();//建立鼠标监听器
	listener->onMouseDown = [this,Hero](EventMouse *e) {//用lamda表达式更加简洁，中括号内可以捕获外部变量
		//如何判断正在运动的方向？
		Vec2 startPos=Hero->getPosition();
		Vec2 endPos = Vec2(e->getCursorX(), e->getCursorY());
		Vec2 dis = endPos - startPos;
		int Angle= CC_RADIANS_TO_DEGREES(Vec2(dis.y, dis.x).getAngle());
		if (Angle>-45&&Angle<45)		{
			_unit->moveDirectionByKey(unit::Direction::UP, Vec2(e->getCursorX(),e->getCursorY()), Hero);
		}
		else if (Angle > -135 && Angle < -45)
		{ 
			_unit->moveDirectionByKey(unit::Direction::LEFT, Vec2(e->getCursorX(), e->getCursorY()), Hero);
		}
			
		else if ((Angle > -180 && Angle < -135) || (Angle >135&& Angle < 180))
		{
			_unit->moveDirectionByKey(unit::Direction::DOWN, Vec2(e->getCursorX(), e->getCursorY()), Hero);

		}
		else
		{

			_unit->moveDirectionByKey(unit::Direction::RIGHT, Vec2(e->getCursorX(), e->getCursorY()), Hero);
		}
			

		//hero->moveDirectionByKey(Hero::Direction::NONE, e->getCursorX(), e->getCursorY(), Hero);
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, Hero);
	listener->onMouseMove = [this](EventMouse *e) 
	{
		return true;
	};
};
	


