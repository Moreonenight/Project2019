#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__
#pragma once
#include "cocos2d.h"
#include "MouseController.h"
#include "ui/CocosGUI.h"

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <stdlib.h>   
#include <string.h>

class HouYi;
class YaSe;
class DaJi;
USING_NS_CC;
class Game : public cocos2d::Layer
{
	MouseController *listener;
	MouseController *skillListener;
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::Sprite* _player;
	cocos2d::TMXLayer* _collidable;
	cocos2d::Label* TimerLabel;
	cocos2d::ui::Button* Moneybutton;
	cocos2d::Sprite* Tower;
	cocos2d::Layer* _shopLayer = nullptr;
	cocos2d::Layer* _skillLayer = nullptr;
	int Time;
	unit*hero1;
	Vector<unit*> unitsOnMap;


public:
	static cocos2d::Scene* createScene(string HeroName);
	void initwithRole(string HeroName);

	virtual bool init();

	void setViewpointCenter(cocos2d::Vec2 position);
	void mapupdate(float dt);
	void TimeRecorder(float dt);


	// a selector callback
	void menuItem1Callback(cocos2d::Ref* pSender);


	void addToMap(unit* unit, int zorder, int Tag);
	Vector<Node*> *selectFromMap(Vec2 pos);
	Vector<unit*> *getUnits();

	void createShopCallBack(cocos2d::Ref* pSender);
	void closeShopCallBack(cocos2d::Ref* pSender);
	void buyItemCallBack(cocos2d::Ref* pSender) {}
	void createSkillLayerCallBack(cocos2d::Ref* pSender);
	void undoSkillCallBack(cocos2d::Ref* pSender);

	// implement the "static create()" method manually

	//×ª»»ÏñËØµ½ÍßÆ¬×ø±ê
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 pos);
	CREATE_FUNC(Game);
};

#endif