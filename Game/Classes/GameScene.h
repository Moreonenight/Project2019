#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__
#pragma once
#include "cocos2d.h"
#include "MouseController.h"
#include "ui/CocosGUI.h"
#include "Soldier.h"
#include "HouYi.h"
#include "DaJi.h"
#include "Yase.h"
#include "Tower.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <stdlib.h>   
#include <string.h>
#include<time.h>

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
	cocos2d::Layer* _ammoLayer = nullptr;
	cocos2d::Layer* _shopLayer = nullptr;
	cocos2d::Layer* _skillLayer = nullptr;
	cocos2d::Layer* _equipmentlLayer = nullptr;
	int Time;
	unit* hero1;
	unit* hero2;
	string _heroname;
	Vector<unit*> unitsOnMap;
	Vector<unit*> MyUnit;
	Vector<unit*> EnemeyUnit;
	Vector<Soldier*> EnemeySoldier;
	Vector<Soldier*> MySoldier;
	Vector<Tower*> MyTower;
	Vector<Tower*> EnemeyTower;
public:
	static cocos2d::Scene* createScene(string HeroName);
	void initwithRole(string HeroName);

	virtual bool init();
	void GoldRecorder(float dt);
	void setViewpointCenter(cocos2d::Vec2 position);
	void mapupdate(float dt);
	void TimeRecorder(float dt);
	void InitSkillButton(string HeroName);

	void addToMap(unit* unit, int zorder, int Tag);
	Vector<Node*> *selectFromMap(Vec2 pos);
	Vector<unit*> *getUnits();
	void InitTabListener(string Hero1Name,string Hero2Name);

	// a selector callback
	void menuItem1Callback(cocos2d::Ref* pSender);
	void createShopCallBack(cocos2d::Ref* pSender);
	void closeShopCallBack(cocos2d::Ref* pSender);
	void createSkillLayerCallBack(cocos2d::Ref* pSender);
	void undoSkillCallBack(cocos2d::Ref* pSender);

	void buyShoeCallBack(cocos2d::Ref* pSender);
	void buyHatCallBack(cocos2d::Ref* pSender);
	void buySwordCallBack(cocos2d::Ref* pSender);
	void sell1CallBack(cocos2d::Ref* pSender);
	void sell2CallBack(cocos2d::Ref* pSender);
	void sell3CallBack(cocos2d::Ref* pSender);
	void sell4CallBack(cocos2d::Ref* pSender);
	void sell5CallBack(cocos2d::Ref* pSender);
	void sell6CallBack(cocos2d::Ref* pSender);

	// implement the "static create()" method manually

	//×ª»»ÏñËØµ½ÍßÆ¬×ø±ê
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 pos);
	CREATE_FUNC(Game);
};

#endif