#include "DescriptionScene.h"

#define CENTERX origin.x+visibleSize.width/2
#define CENTERY origin.y+visibleSize.height/2
USING_NS_CC;

Scene* DescriptionScene::createScene()
{
	return DescriptionScene::create();
}

bool DescriptionScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto Description = Sprite::create("bg/DescriptionScene.png");
	Description->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(Description);
	//return button
	auto closeItem = MenuItemImage::create(
		"/button/closetoupper.png",
		"/button/closetoupper_selected.png",
		CC_CALLBACK_1(DescriptionScene::menuItem1Callback, this));

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
void DescriptionScene::menuItem1Callback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}