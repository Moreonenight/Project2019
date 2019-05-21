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

	//获取地图设置出生点
	auto group = _tileMap->getObjectGroup("hero");
	auto spawnPoint = group->getObject("spawnpoint");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	//英雄初始化
	auto _player = Sprite::create("mysprite.png");
	_player->setPosition(Vec2(x,y));
	this->addChild(_player, 2, 200);

	//创建英雄并保存指针

	auto Listener = MouseController::create();
	Listener->initListener(_player);


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


	//////////  循环更新  /////////
	this->schedule(schedule_selector(Game::mapupdate), 1.0f / 60);

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

	//当前中心点
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//得到精灵走后地图移动的目标位置
	x = MIN(x, MapWidth - visibleSize.width / 2);
	y = MIN(y, MapHeight - visibleSize.height / 2);
	Vec2 pointB = Vec2(x, y);
	//需要调整的方位
	Vec2 offset = pointA - pointB;

	this->setPosition(offset);
}

void Game::mapupdate(float dt)
{
	auto sprite = this->getChildByTag(200);
	auto pos = sprite->getPosition();
	setViewpointCenter(pos);
}