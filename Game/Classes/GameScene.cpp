#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
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

	//tiledMap
	_tileMap = TMXTiledMap::create("map/map1.tmx");
	addChild(_tileMap, 0, 100);

	auto group = _tileMap->getObjectGroup("hero");
	auto spawnPoint = group->getObject("spawnpoint");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	_player = Sprite::create("mysprite.png");
	_player->setPosition(Vec2(x, y));
	addChild(_player, 2, 200);

	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(false);

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

	
	//control Sprite
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	return true;
}


void Game::menuItem1Callback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

bool Game::onTouchBegan(Touch* touch, Event* event)
{
	log("onTouchBegan");
	return true;
}

void Game::onTouchMoved(Touch* touch, Event* event) 
{
	log("onTouchMoved");
}

void Game::onTouchEnded(Touch* touch, Event* event)
{
	log("onTouchEnded");

	Vec2 touchLocation = touch->getLocation();

	Vec2 playerPos = _player->getPosition();
	Vec2 diff = touchLocation - playerPos;
	
	if (diff.x > 0) {
		playerPos.x += _tileMap->getTileSize().width;
	}
	else {
		playerPos.x -= _tileMap->getTileSize().width;
		_player->runAction(FlipX::create(true));
	}
	auto MoveBy = MoveBy::create(0.4f, diff);
	_player->runAction(MoveBy);
}
