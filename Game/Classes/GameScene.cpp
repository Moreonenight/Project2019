#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

#include "MouseController.h"
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

	//地图的初始化
	_tileMap = TMXTiledMap::create("map/map1.tmx");
	addChild(_tileMap, 0, 100);
	auto group = _tileMap->getObjectGroup("hero");
	auto spawnPoint = group->getObject("spawnpoint");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	
	//英雄初始化
	auto _player = Hero::create();
	this->addChild(_player, 0);
	auto Hero1=_player->initWithRole(Vec2(x,y));
	//创建英雄并保存指针


	auto Listener = MouseController::create();
	Listener->initListener(Hero1);





	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(true);

	//return  button
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
	return true;
}


void Game::menuItem1Callback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

