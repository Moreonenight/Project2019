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
//��ʼ��
void MouseController::initListener(Sprite* Hero) {
	auto listener = EventListenerMouse::create();//������������
	listener->onMouseDown = [this,Hero](EventMouse *e) {//��lamda���ʽ���Ӽ�࣬�������ڿ��Բ����ⲿ����
		//����ж������˶��ķ���
		Vec2 startPos=Hero->getPosition();
		Vec2 endPos = Director::getInstance()->convertToGL(e->getLocation());
		Vec2 dis = endPos - startPos;
		int Angle= CC_RADIANS_TO_DEGREES(Vec2(dis.y, dis.x).getAngle());
		if (Angle>-45&&Angle<45)		
		{
			_unit->moveDirectionByKey(unit::Direction::UP, endPos, Hero);
		}
		else if (Angle > -135 && Angle < -45)
		{ 
			_unit->moveDirectionByKey(unit::Direction::LEFT, endPos, Hero);
		}
			
		else if ((Angle > -180 && Angle < -135) || (Angle >135&& Angle < 180))
		{
			_unit->moveDirectionByKey(unit::Direction::DOWN, endPos, Hero);

		}
		else
		{
			_unit->moveDirectionByKey(unit::Direction::RIGHT, endPos, Hero);
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
	


