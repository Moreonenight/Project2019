#include "Game1v1Scene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#define CENTERX origin.x+visibleSize.width/2
#define CENTERY origin.y+visibleSize.height/2
USING_NS_CC;

Scene* Game1v1::createScene()
{
	return Game1v1::create();
}

bool Game1v1::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//background
	auto bg = Sprite::create("/bg/Game1v1Scene.jpg");
	bg->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2
	));
	this->addChild(bg, -1);

	//return button
	auto closeItem = MenuItemImage::create(
		"/button/closetoupper.png",
		"/button/closetoupper_selected.png",
		CC_CALLBACK_1(Game1v1::menuItem1Callback, this));

	closeItem->setPosition(Vec2(
		origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2
	));
	auto mn = Menu::create(
		closeItem,
		NULL
	);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn, 2);

	return true;
}


void Game1v1::menuItem1Callback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}