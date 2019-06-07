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
	cocos2d::Label* goldLabel;
	cocos2d::ui::Button* Moneybutton;
	cocos2d::Sprite* Tower;
	cocos2d::Layer* _skillLayer = nullptr;
	cocos2d::Layer* _uiLayer = nullptr;
	int Time;
	unit*myHero;
	Vector<unit*> unitsOnMap;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void setViewpointCenter(cocos2d::Vec2 position);
	void mapupdate(float dt);
	void TimeRecorder(float dt);
	void GoldRecorder(float dt);


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

	//返回地图上特定单位
	unit* getUnitWithId(std::string id);
	
	//返回unitsOnMap;
	//转换像素到瓦片坐标
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 pos);
	CREATE_FUNC(Game);
};

#endif