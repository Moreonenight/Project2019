#include "SettingScene.h"
#include "SimpleAudioEngine.h"
#define CENTERX origin.x+visibleSize.width/2
#define CENTERY origin.y+visibleSize.height/2
USING_NS_CC;

Scene *Setting::createScene()
{
	auto scene = Scene::create();

	auto layer = Setting::create();

	scene->addChild(layer);

	return scene;
}

bool Setting::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//background
	auto bg = Sprite::create("/bg/SettingScene.jpg");
	bg->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2
	));

	this->addChild(bg, -1);
	//Sound

	auto SoundOnMenuItem = MenuItemImage::create(
		"/button/checkbox_normal.png",
		"/button/checkbox_normal.png"
	);
	auto SoundOffMenuItem = MenuItemImage::create(
		"/button/checkbox_selected.png",
		"/button/checkbox_selected.png"
	);
	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(Setting::menuSoundToggleCallback, this),
		SoundOnMenuItem,
		SoundOffMenuItem,
		NULL
	);
	soundToggleMenuItem->setPosition(Vec2(
		origin.x + visibleSize.width / 2+40,
		origin.y + visibleSize.height / 2
	));
	auto SoundLabel = Label::createWithTTF(
		"Sound:  ", "fonts/Marker Felt.ttf", 24
	);
	SoundLabel->setPosition(Vec2(
		CENTERX - 20,
		CENTERY
	));
	this->addChild(SoundLabel);

	//return button
	auto closeItem = MenuItemImage::create(
		"/button/closetoupper.png",
		"/button/closetoupper_selected.png",
		CC_CALLBACK_1(Setting::menuItem1Callback, this));

	closeItem->setPosition(Vec2(
		origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2
	));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem,soundToggleMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	return true;
}

void Setting::menuItem1Callback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}
void Setting::menuSoundToggleCallback(cocos2d::Ref* pSender)
{
	auto audio=CocosDenshion::SimpleAudioEngine::getInstance();
	if (audio->isBackgroundMusicPlaying()) {
		audio->stopBackgroundMusic();
	}
	else {
		audio->playBackgroundMusic("/music/roomScene.mp3");
	}
}