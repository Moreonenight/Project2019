#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__
#pragma once
#include "cocos2d.h"
#include "MouseController.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class Game : public cocos2d::Layer
{	
	MouseController *listener;
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::Sprite* _player;
	cocos2d::TMXLayer* _collidable;
	cocos2d::Label* TimerLabel;
	cocos2d::ui::Button* Moneybutton;
	cocos2d::Sprite* Tower;
	cocos2d::Layer* _shopLayer=nullptr;
	int Time;


public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void setViewpointCenter(cocos2d::Vec2 position);
	void mapupdate(float dt);
	void TimeRecorder(float dt);
	// a selector callback
	void menuItem1Callback(cocos2d::Ref* pSender);
	
	void createShopCallBack(cocos2d::Ref* pSender);
	void closeShopCallBack(cocos2d::Ref* pSender);
	void buyItemCallBack(cocos2d::Ref* pSender) {}
	// implement the "static create()" method manually
	CREATE_FUNC(Game);
};

#endif