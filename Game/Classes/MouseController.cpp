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
	if (minlength <= 150.0)
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
void MouseController::initListener(HouYi * houyi, Vector<unit*>* children)
{
	isPaused = 0;

	listener = EventListenerMouse::create();//建立鼠标监听器
	listener->onMouseDown = [this, houyi, children](EventMouse *e) {//用lamda表达式更加简洁，中括号内可以捕获外部变量
		Vec2 endPos = e->getLocationInView() - offset;
		sprites = children;
		if(((HouYi*)houyi)->isReleasing()){
			if (((HouYi*)houyi)->getSk2()) {
				((HouYi*)houyi)->useSkill_2(endPos);
			}
			else if (((HouYi*)houyi)->getSk3()) {
				auto a = selectFromSprites(endPos);
				if (a != nullptr) {((HouYi*)houyi)->useSkill_3(a);}
				else{ ((HouYi*)houyi)->sk3End(); }
			}
		}
		else {
			auto a = selectFromSprites(endPos);
			if (a != nullptr) {
				houyi->attackTo(a);
				return true;
			}
			else {
				if (isPaused) {
					return true;
				}
				houyi->moveDirectionByKey(houyi->getDir(houyi->getPosition(), endPos), endPos);
				return true;
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, houyi);
	listener->onMouseMove = [this](EventMouse *e)
	{
		return true;
	};
}
void MouseController::initListener(YaSe * yase)
{
}
void MouseController::initListener(DaJi * daji)
{
}
;

	


