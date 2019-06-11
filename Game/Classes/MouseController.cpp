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
void MouseController::initListener(HouYi * Houyi, Vector<unit*>* children)
{
	isPaused = 0;

	listener = EventListenerMouse::create();//建立鼠标监听器
	listener->onMouseDown = [this, Houyi, children](EventMouse *e) {//用lamda表达式更加简洁，中括号内可以捕获外部变量
		Vec2 endPos = e->getLocationInView() - offset;
		sprites = children;
		auto houyi = static_cast<HouYi*>(Houyi);
		if(houyi->isReleasing()){
			if (houyi->getSk2()) {
				houyi->useSkill_2(endPos);
			}
			else if (houyi->getSk3()) {
				auto a = selectFromSprites(endPos);
				if (a != nullptr) {houyi->useSkill_3(a); houyi->sk3End();}
				else{ houyi->sk3End(e->getLocationInView() - offset); }
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
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, Houyi);
	listener->onMouseMove = [this](EventMouse *e)
	{
		return true;
	};
}
void MouseController::initListener(YaSe * Yase, Vector<unit*>* children)
{
	isPaused = 0;

	listener = EventListenerMouse::create();//建立鼠标监听器
	listener->onMouseDown = [this, Yase, children](EventMouse *e) {//用lamda表达式更加简洁，中括号内可以捕获外部变量
		Vec2 endPos = e->getLocationInView() - offset;
		sprites = children;
		auto yase = static_cast<YaSe*>(Yase);
		if (yase->isReleasing()) {
			if (yase->getSk1()) {
				auto a = selectFromSprites(endPos);
				if (a != nullptr) {
					yase->useSkill_1(yase->getBeforePos(), a);
				}
				else { yase->sk1End(); }
			}
			else if (yase->getSk2()) {
				yase->useSkill_2(endPos);
			}
		}
		else {
			auto a = selectFromSprites(endPos);
			if (a != nullptr) {
				yase->attackTo(a);
				return true;
			}
			else {
				if (isPaused) {
					return true;
				}
				yase->moveDirectionByKey(yase->getDir(yase->getPosition(), endPos), endPos);
				return true;
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, Yase);
	listener->onMouseMove = [this](EventMouse *e)
	{
		return true;
	};
}
void MouseController::initListener(DaJi * Daji, Vector<unit*>* children)
{

	isPaused = 0;

	listener = EventListenerMouse::create();//建立鼠标监听器
	listener->onMouseDown = [this, Daji, children](EventMouse *e) {//用lamda表达式更加简洁，中括号内可以捕获外部变量
		Vec2 endPos = e->getLocationInView() - offset;
		sprites = children;
		auto daji = static_cast<DaJi*>(Daji);
		if (daji->isReleasing()) {
			if (daji->getSk1()) {
				auto a = selectFromSprites(endPos);
				if (a != nullptr) {
					daji->useSkill_1(a);
				}
			}
			else if (daji->getSk2()) {
				daji->useSkill_2(endPos);
			}
		}
		else {
			auto a = selectFromSprites(endPos);
			if (a != nullptr) {
				daji->attackTo(a);
				return true;
			}
			else {
				if (isPaused) {
					return true;
				}
				daji->moveDirectionByKey(daji->getDir(daji->getPosition(), endPos), endPos);
				return true;
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, Daji);
	listener->onMouseMove = [this](EventMouse *e)
	{
		return true;
	};
}
;

	


