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
void MouseController::initListener(unit* Hero,Vector<unit*>* children, SocketClient* _socket_client) {
	isPaused = 0;
	Hero->AIClose();
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
void MouseController::initListener(HouYi * Houyi, Vector<unit*>* children,SocketClient* _socket_client)
{
	isPaused = 0;

	Houyi->AIClose();

	listener = EventListenerMouse::create();//建立鼠标监听器
	listener->onMouseDown = [this, Houyi, children,_socket_client](EventMouse *e) {//用lamda表达式更加简洁，中括号内可以捕获外部变量
		Vec2 endPos = e->getLocationInView() - offset;
		sprites = children;
		auto houyi = static_cast<HouYi*>(Houyi);
		if (houyi->getDeathCdLeft() > 0) { return true; }
		houyi->backEnd();
		if(houyi->isReleasing()){
			if (houyi->getSk2()) {
				if (_socket_client != NULL) {
					if (_socket_client->is_sent == false) {
						return true;
					}
					else {
						_socket_client->_mutex.lock();
						_socket_client->wcommand.SkillNumber = 2;
						_socket_client->wcommand.CurrentLocation = endPos;
						_socket_client->is_sent = false;
						_socket_client->_mutex.unlock();
					}
				}
				houyi->useSkill_2(endPos);
			}
			else if (houyi->getSk3()) {
				auto a = selectFromSprites(endPos);
				if (a != nullptr) {
					if (_socket_client != NULL) {
						if (_socket_client->is_sent == false) {
							return true;
						}
						else {
							_socket_client->_mutex.lock();
							_socket_client->wcommand.SkillNumber = 3;
							_socket_client->wcommand.CurrentLocation = endPos;
							_socket_client->is_sent = false;
							_socket_client->_mutex.unlock();
						}
					}
					houyi->useSkill_3(a); 
					houyi->sk3End();
				}
				else{ houyi->sk3End(e->getLocationInView() - offset); }
			}
		}
		else {
			auto a = selectFromSprites(endPos);
			if (a != nullptr) {
				if (_socket_client != NULL) {
					if (_socket_client->is_sent == false) {
						return true;
					}
					else {
						_socket_client->_mutex.lock();
						_socket_client->wcommand.now_attack=true;
						_socket_client->wcommand.CurrentLocation = endPos;
						_socket_client->is_sent = false;
						_socket_client->_mutex.unlock();
					}
				}
				houyi->attackTo(a);
				return true;
			}
			else {
				if (isPaused) {
					return true;
				}
				if (_socket_client != NULL) {
					if (_socket_client->is_sent == false) {
						return true;
					}
					else {
						_socket_client->_mutex.lock();
						_socket_client->wcommand.now_move = true;
						_socket_client->wcommand.CurrentLocation = endPos;
						_socket_client->is_sent = false;
						_socket_client->_mutex.unlock();
					}
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
void MouseController::initListener(YaSe * Yase, Vector<unit*>* children, SocketClient* _socket_client)
{
	isPaused = 0;
	
	Yase->AIClose();

	listener = EventListenerMouse::create();//建立鼠标监听器
	listener->onMouseDown = [this, Yase, children,_socket_client](EventMouse *e) {//用lamda表达式更加简洁，中括号内可以捕获外部变量
		Vec2 endPos = e->getLocationInView() - offset;
		sprites = children;
		auto yase = static_cast<YaSe*>(Yase);
		yase->backEnd();
		if (yase->getDeathCdLeft() > 0) { return true; }
		if (yase->isReleasing()) {
			if (yase->getSk1()) {
				auto a = selectFromSprites(endPos);
				if (a != nullptr) {
					if (_socket_client != NULL) {
						if (_socket_client->is_sent == false) {
							return true;
						}
						else {
							_socket_client->_mutex.lock();
							_socket_client->wcommand.SkillNumber = 1;
							_socket_client->wcommand.BeforePos = yase->getBeforePos();
							_socket_client->wcommand.CurrentLocation = endPos;
							_socket_client->is_sent = false;
							_socket_client->_mutex.unlock();
						}
					}
					yase->useSkill_1(yase->getBeforePos(), a);
				}
				else { yase->sk1End(); }
			}
			else if (yase->getSk2()) {
				if (_socket_client != NULL) {
					if (_socket_client->is_sent == false) {
						return true;
					}
					else {
						_socket_client->_mutex.lock();
						_socket_client->wcommand.SkillNumber = 2;
						_socket_client->wcommand.CurrentLocation = endPos;
						_socket_client->is_sent = false;
						_socket_client->_mutex.unlock();
					}
				}
				yase->useSkill_2(endPos);
			}
		}
		else {
			auto a = selectFromSprites(endPos);
			if (a != nullptr) {
				if (_socket_client != NULL) {
					if (_socket_client->is_sent == false) {
						return true;
					}
					else {
						_socket_client->_mutex.lock();
						_socket_client->wcommand.now_attack = true;
						_socket_client->wcommand.CurrentLocation = endPos;
						_socket_client->is_sent = false;
						_socket_client->_mutex.unlock();
					}
				}
				yase->attackTo(a);
				return true;
			}
			else {
				if (isPaused) {
					return true;
				}
				if (_socket_client != NULL) {
					if (_socket_client->is_sent == false) {
						return true;
					}
					else {
						_socket_client->_mutex.lock();
						_socket_client->wcommand.now_move = true;
						_socket_client->wcommand.CurrentLocation = endPos;
						_socket_client->is_sent = false;
						_socket_client->_mutex.unlock();
					}
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
void MouseController::initListener(DaJi * Daji, Vector<unit*>* children, SocketClient* _socket_client)
{

	isPaused = 0;

	Daji->AIClose();

	listener = EventListenerMouse::create();//建立鼠标监听器
	listener->onMouseDown = [this, Daji, children,_socket_client](EventMouse *e) {//用lamda表达式更加简洁，中括号内可以捕获外部变量
		Vec2 endPos = e->getLocationInView() - offset;
		sprites = children;
		auto daji = static_cast<DaJi*>(Daji);
		daji->backEnd();
		if (daji->getDeathCdLeft() > 0) { return true; }
		if (daji->isReleasing()) {
			if (daji->getSk1()) {
				auto a = selectFromSprites(endPos);
				if (a != nullptr) {
					if (_socket_client != NULL) {
						if (_socket_client->is_sent == false) {
							return true;
						}
						else {
							_socket_client->_mutex.lock();
							_socket_client->wcommand.SkillNumber = 1;
							_socket_client->wcommand.CurrentLocation = endPos;
							_socket_client->is_sent = false;
							_socket_client->_mutex.unlock();
						}
					}
					daji->useSkill_1(a);
				}
			}
			else if (daji->getSk2()) {
				if (_socket_client != NULL) {
					if (_socket_client->is_sent == false) {
						return true;
					}
					else {
						_socket_client->_mutex.lock();
						_socket_client->wcommand.SkillNumber = 2;
						_socket_client->wcommand.CurrentLocation = endPos;
						_socket_client->is_sent = false;
						_socket_client->_mutex.unlock();
					}
				}
				daji->useSkill_2(endPos);
			}
		}
		else {
			auto a = selectFromSprites(endPos);
			if (a != nullptr) {
				if (_socket_client != NULL) {
					if (_socket_client->is_sent == false) {
						return true;
					}
					else {
						_socket_client->_mutex.lock();
						_socket_client->wcommand.now_attack = true;
						_socket_client->wcommand.CurrentLocation = endPos;
						_socket_client->is_sent = false;
						_socket_client->_mutex.unlock();
					}
				}
				daji->attackTo(a);
				return true;
			}
			else {
				if (isPaused) {
					return true;
				}
				if (_socket_client != NULL) {
					if (_socket_client->is_sent == false) {
						return true;
					}
					else {
						_socket_client->_mutex.lock();
						_socket_client->wcommand.now_move=true;
						_socket_client->wcommand.CurrentLocation = endPos;
						_socket_client->is_sent = false;
						_socket_client->_mutex.unlock();
					}
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

	


