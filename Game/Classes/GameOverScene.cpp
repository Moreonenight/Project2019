#include "GameModeScene.h"
#include "SimpleAudioEngine.h"
#include "ChooseHeroScene.h"
#include "GameOverScene.h"
#define CENTERX origin.x+visibleSize.width/2
#define CENTERY origin.y+visibleSize.height/2
USING_NS_CC;

Scene* GameOverScene::createScene(bool VictoryorDefeat)
{
	auto GameOverScene= GameOverScene::create();
	GameOverScene->initwithBool(VictoryorDefeat);
	return GameOverScene;
}

bool GameOverScene::initwithBool(bool VictoryorDefeat)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite* bg;
	//background
	if (VictoryorDefeat == true)
	{
		bg = Sprite::create("/bg/GameOverVictory.jpg");
		bg->setPosition(Vec2(
			origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 2
		));

	}
	else
	{
		bg = Sprite::create("/bg/GameOverDefeat.jpg");
		bg->setPosition(Vec2(
			origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 2
		));
	}
	bg->setScale(1.4f);
	this->addChild(bg, -1);
	//GameMode

	//return button
	auto closeItem = MenuItemImage::create(
		"/button/closetoupper.png",
		"/button/closetoupper_selected.png",
		CC_CALLBACK_1(GameOverScene::menuItem1Callback, this));

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

bool GameOverScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	return true;
}

void GameOverScene::menuItem1Callback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popToRootScene();
}

void GameOverScene::menuStartCallback(cocos2d::Ref* pSender) {
	//	auto ChooseHeroScene = ChooseHeroScene::create();
	//	Director::getInstance()->pushScene(ChooseHeroScene);
	Director::getInstance()->popToRootScene();
}

void GameOverScene::Start1v1Callback(cocos2d::Ref* pSender) {
	//auto Game1v1Scene = Game1v1::createScene();
	//Director::getInstance()->pushScene(Game1v1Scene);
}