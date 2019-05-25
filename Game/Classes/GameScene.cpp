#pragma once
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "MouseController.h"
#include <stdlib.h>   
#include <string.h>
USING_NS_CC;
#define IS_SHOP_OPEN this->getChildByTag(133)
Scene* Game::createScene()
{
	auto scene = Scene::create();
	auto layer = Game::create();
	scene->addChild(layer);
	return scene;
}

bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Time = 0;
	//初始化地图
	_tileMap = TMXTiledMap::create("map/map1.tmx");
	addChild(_tileMap, 0, 100);
	
	//初始化碰撞层
	//_collidable = _tileMap->getLayer("collidable");
	//_collidable->setVisible(true);

	//获取地图设置出生点
	auto group = _tileMap->getObjectGroup("hero");
	auto spawnPoint = group->getObject("spawnpoint");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	//初始化单位属性
	//auto hero1data = new(unitdata);
	//hero1data->initial(string("Player/Player2.png"));


	//初始化英雄
	_player = Sprite::create("Player/Player2.png");
	_player->setPosition(Vec2(x,y));
	//this->addChild(_player, 2, 200);
	_tileMap->addChild(_player, 2, 200);


	auto Tower = Sprite::create("000073.png");
	Tower->setPosition(Vec2(x, y));
	//Tower->setScale(0.5, 0.5);
	this->addChild(Tower, 2, 400);
	auto A=Tower->getContentSize();

	Tower->getPosition();


	//初始化监听器
	listener = MouseController::create();
	listener->initListener(_player);
	listener->changeOffset(Vec2::ZERO);
	//初始化时间标签
	TimerLabel = Label::createWithSystemFont("00:00", "Arial", 30);
	this->addChild(TimerLabel, 3);


	//初始化退出按钮
	auto closeItem = MenuItemImage::create(
		"/button/closetoupper.png",
		"/button/closetoupper_selected.png",
		CC_CALLBACK_1(Game::menuItem1Callback, this));

	closeItem->setPosition(Vec2(
		origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2
	));


	////  商店界面  ////

	//进入按钮
	auto shopButton = MenuItemImage::create(
		"/button/Money.png",
		"/button/Money.png",
		CC_CALLBACK_1(Game::createShopCallBack, this));
	shopButton->setPosition(30, visibleSize.height / 2+25);
	shopButton->setScale(0.8f);


	auto menu = Menu::create(closeItem,shopButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//////////  循环更新  /////////
	this->schedule(schedule_selector(Game::mapupdate), 1.0f/60);
	this->schedule(schedule_selector(Game::TimeRecorder), 1.0f);
	return true;
}

//返回主页面
void Game::menuItem1Callback(cocos2d::Ref* pSender)
{
	unscheduleAllSelectors();
	Director::getInstance()->popScene();
}

//////////   滚动地图    //////////
void Game::setViewpointCenter(Vec2 position)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);

	//获得地图大小
	auto MapWidth = _tileMap->getMapSize().width*_tileMap->getTileSize().width;
	auto MapHeight = _tileMap->getMapSize().height*_tileMap->getTileSize().height;
	//_tileMap->
	//当前中心点
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//得到精灵走后地图移动的目标位置
	x = MIN(x, MapWidth - visibleSize.width / 2);
	y = MIN(y, MapHeight - visibleSize.height / 2);
	Vec2 pointB = Vec2(x, y);
	//需要调整的方位
	Vec2 offset = pointA - pointB;
	_tileMap->setPosition(offset);
	listener->changeOffset(offset); 
	TimerLabel->setVisible(true);
	TimerLabel->setPosition(Director::getInstance()->getVisibleSize().width-50, Director::getInstance()->getVisibleSize().height - 15);

}

void Game::mapupdate(float dt)
{
	//auto sprite = this->getChildByTag(200);
	auto sprite = _tileMap->getChildByTag(200);
	auto pos = sprite->getPosition();
	setViewpointCenter(pos);
	if (IS_SHOP_OPEN) { listener->setPause(1); }
	else { listener->setPause(0); }
}

void Game::TimeRecorder(float dt)
{
	
	this->removeChild(TimerLabel);
	Time++;
	int Minute = Time / 60;
	int Second = Time % 60;
	std::string second_str = std::to_string(Second);
	std::string minute_str = std::to_string(Minute);
	std::string Second_str;
	std::string Minute_str;
	if (Second < 10)
	{
		Second_str = '0' + second_str;
	}
	else
		Second_str = second_str;

	if (Minute < 10)
	{
		Minute_str = '0' + minute_str;
	}
	else
		Minute_str = minute_str;
	std::string str = Minute_str + ':' + Second_str;
	TimerLabel = Label::createWithSystemFont(str, "Arial", 30);
	TimerLabel->setVisible(false);
	this->addChild(TimerLabel, 3);
	
}

void Game::createShopCallBack(cocos2d::Ref* pSender) {
	_player->stopAllActions();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (IS_SHOP_OPEN) { return; }
	_shopLayer = Layer::create();
	auto shopbg = Sprite::create("bg/shop.png");
	shopbg->setPosition(Vec2(
		visibleSize.width / 2,
		visibleSize.height / 2
	));
	//closebutton
	auto closeShopButton = MenuItemImage::create(
		"/button/back.png",
		"/button/back.png",
		CC_CALLBACK_1(Game::closeShopCallBack, this)
	);
	closeShopButton->setPosition(shopbg->getPosition() + Vec2(250, -200));

	//item
	auto itemShoe = MenuItemImage::create(
		"/item/shoe_normal.png",
		"/item/shoe_selected.png",
		CC_CALLBACK_1(Game::buyItemCallBack, this)
	);
	itemShoe->setPosition(shopbg->getPosition() + Vec2(-200, 0));
	auto itemHat = MenuItemImage::create(
		"item/hat_normal.png",
		"item/hat_selected.png",
		CC_CALLBACK_1(Game::buyItemCallBack, this)
	);
	itemHat->setPosition(shopbg->getPosition() + Vec2(0, 0));
	auto itemShield = MenuItemImage::create(
		"item/shield_normal.png",
		"item/shield_selected.png",
		CC_CALLBACK_1(Game::buyItemCallBack, this)
	);
	itemShield->setPosition(shopbg->getPosition() + Vec2(200, 0));


	auto mn = Menu::create(closeShopButton, itemShoe,itemHat,itemShield,NULL);

	mn->setPosition(Vec2::ZERO);
	_shopLayer->addChild(mn,2);
	_shopLayer->addChild(shopbg);
	this->addChild(_shopLayer, 5,133);
}

void Game::closeShopCallBack(cocos2d::Ref* pSender) {
	_shopLayer->removeFromParent();
}
