#pragma once
#include "cocos2d.h"
#include "Houyi.h"
#include "YaSe.h"
#include "DaJi.h"
#include "unit.h"
#include "SocketClient.h"
//#include "Money.h"
//#include "GameScene.h"
class HouYi;
class YaSe;
class DaJi;
class MouseController : public cocos2d::Node
{
private:
	cocos2d::EventListenerMouse* listener;
	unit* _unit;
	Vec2 offset;
	short isPaused;
	Vector<unit*>* sprites;
	//Money* m_Money;
public:
	MouseController();
	~MouseController();
	unit* selectFromSprites(Vec2 pos);
	void initListener(unit* Hero, Vector<unit*>* children, SocketClient* _socket_client);
	void initListener(HouYi* houyi, Vector<unit*>* children, SocketClient* _socket_client);
	void initListener(YaSe* yase, Vector<unit*>* children, SocketClient* _socket_client);
	void initListener(DaJi* daji, Vector<unit*>* children, SocketClient* _socket_client);
	void changeOffset(const Vec2 a) {
		offset = a;
	}
	void setPause(short x) {
		isPaused = x;
	}
	CREATE_FUNC(MouseController);
};