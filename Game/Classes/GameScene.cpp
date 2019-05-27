#pragma once
#include "GameScene.h"


USING_NS_CC;
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
	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(true);

	//获取地图设置出生点
	auto group = _tileMap->getObjectGroup("hero");
	auto spawnPoint = group->getObject("spawnpoint");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();


	//CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("HouYi/attack.plist");
	//初始化单位属性
	auto hero1data = new(unitdata);
	hero1data->initial(string("HouYi"));
	auto act = Animate::create(AnimationCache::getInstance()->getAnimation("HouYidown_stand"));
	auto hero1 = unit::create();
	hero1->initial(hero1data);
	hero1->runAction(act);


	//hero1->getActionManager()->addAction(act2, hero1, 0);


	//hero1->runAction(Animate::create(act));





	auto hero2 = unit::create();
	hero2->initial(hero1data);	
	hero2->setSpriteFrame("000140.png");

	


	//初始站姿设定过后会引起bug，不论是播放动画还是放一帧图片都会导致后边animation的bug
	//似乎可以通过
	//setSpriteFrame（AnimationCache-》getInstance（）-》getAnimation（“”）-》getSpriteFrames【0】））；
	//解决
	hero1->setPosition(Vec2(x, y));
	_tileMap->addChild(hero1, 2, 100);
	//初始化英雄
	auto _player = Sprite::create("Player/Player2.png");
	_player->setPosition(Vec2(x,y));
	_tileMap->addChild(_player, 2, 200);

	//初始化监听器
	listener = MouseController::create();
	listener->initListener(hero1);
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

	auto menu = Menu::create(closeItem, NULL);
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
	TimerLabel->setPosition(Director::getInstance()->getVisibleSize().width -45, Director::getInstance()->getVisibleSize().height - 15);

}

void Game::mapupdate(float dt)
{
	//auto sprite = this->getChildByTag(200);
	auto sprite = _tileMap->getChildByTag(200);
	auto pos = sprite->getPosition();
	setViewpointCenter(pos);
	
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
