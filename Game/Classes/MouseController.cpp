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

unit * MouseController::selectFromSprites(Vec2 pos)
{
	Vector<unit*>::iterator it;
	unit* ans;
	float minlength = 65535.0, curlength;
	for (it = (*sprites).begin(); it < (*sprites).end(); it++) {
		curlength = ((*it)->getPosition() - pos).length();
		if (curlength < minlength && (*it)->getid()[1] == 'r') {
			ans = *it;
			minlength = curlength;
		}
	}
	if (minlength <= 200.0)
		return ans;
	else return nullptr;
}


//初始化
void MouseController::initListener(unit* Hero,Vector<unit*>* children) {
	isPaused = 0;
	
	listener = EventListenerMouse::create();//建立鼠标监听器
	listener->onMouseDown = [this,Hero,children](EventMouse *e) {//用lamda表达式更加简洁，中括号内可以捕获外部变量
		Vec2 endPos = e->getLocationInView() - offset;	
		sprites = children;
		auto a = selectFromSprites(endPos);
		if (a != nullptr) { 
				Hero->attackTo(a);
			return true;
		}
		else {
			//如何判断正在运动的方向？
			if (isPaused) {
				return true;
			}
			Hero->moveDirectionByKey(Hero->getDir(Hero->getPosition(), endPos), endPos);
			return true;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, Hero);
	listener->onMouseMove = [this](EventMouse *e) 
	{
		return true;
	};
}
void MouseController::initListener(HouYi * houyi)
{
}
void MouseController::initListener(YaSe * yase)
{
}
void MouseController::initListener(DaJi * daji)
{
}
;

	


