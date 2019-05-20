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

		hero->moveDirectionByKey(Hero::Direction::NONE, e->getCursorX(), e->getCursorY(), Hero);
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, Hero);
	listener->onMouseMove = [this](EventMouse *e) 
	{
		return true;
	};
};
	


