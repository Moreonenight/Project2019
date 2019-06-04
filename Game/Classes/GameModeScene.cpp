#include "GameModeScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "Game1v1Scene.h"
#define CENTERX origin.x+visibleSize.width/2
#define CENTERY origin.y+visibleSize.height/2
USING_NS_CC;

Scene* GameMode::createScene()
{
	return GameMode::create();
}

bool GameMode::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//background
	auto bg = Sprite::create("/bg/ModeScene.png");
	bg->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2
	));

	this->addChild(bg, -1);
	//GameMode
	auto player_ai_1v1 = MenuItemImage::create(
		"/button/1v1ai.png",
		"/button/1v1ai.png",
		CC_CALLBACK_1(GameMode::menuStartCallback, this)
	);
	player_ai_1v1->setPosition(Vec2(
		origin.x + visibleSize.width / 2 - 200,
		origin.y + visibleSize.height / 2
	));

	auto player_1v1 = MenuItemImage::create(
		"/button/1v1.png",
		"/button/1v1.png",
		CC_CALLBACK_1(GameMode::Start1v1Callback, this)
	);
	player_1v1->setPosition(Vec2(
		origin.x + visibleSize.width / 2 + 200,
		origin.y + visibleSize.height / 2
	));

	//return button
	auto closeItem = MenuItemImage::create(
		"/button/closetoupper.png",
		"/button/closetoupper_selected.png",
		CC_CALLBACK_1(GameMode::menuItem1Callback, this));

	closeItem->setPosition(Vec2(
		origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2
	));
	auto mn = Menu::create(
		player_ai_1v1,
		player_1v1,
		closeItem,
		NULL
	);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn, 2);

	return true;
}

void GameMode::menuItem1Callback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

void GameMode::menuStartCallback(cocos2d::Ref* pSender) {
	auto GameScene = Game::createScene();
	Director::getInstance()->pushScene(GameScene);
}

void GameMode::Start1v1Callback(cocos2d::Ref* pSender) {
	auto Game1v1Scene = Game1v1::createScene();
	Director::getInstance()->pushScene(Game1v1Scene);
}