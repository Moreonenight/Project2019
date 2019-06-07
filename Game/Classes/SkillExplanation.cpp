#include "GameModeScene.h"
#include "SimpleAudioEngine.h"
#include "ChooseHeroScene.h"
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

	//return button
	auto closeItem = MenuItemImage::create(
		"/button/closetoupper.png",
		"/button/closetoupper_selected.png",
		CC_CALLBACK_1(GameMode::menuItem1Callback, this));

	closeItem->setPosition(Vec2(
		origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2
	));
	/*auto mn = Menu::create(
		player_ai_1v1,
		player_1v1,
		closeItem,
		NULL
	);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn, 2);*/

	return true;
}

void GameMode::menuItem1Callback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

