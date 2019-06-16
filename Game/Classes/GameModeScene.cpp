#include "GameModeScene.h"
#include "SimpleAudioEngine.h"
#include "ChooseHeroScene.h"
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
	auto ChooseHeroScene = ChooseHeroScene::create(0, NULL, DISCONNECTED);
	Director::getInstance()->pushScene(ChooseHeroScene);
	//auto Game1v1Scene = Game1v1::createScene();
	//Director::getInstance()->pushScene(Game1v1Scene);
}

void GameMode::Start1v1Callback(cocos2d::Ref* pSender) {
	SocketClient* _fff = new SocketClient;
	//	_fff->connectServer("106.52.125.87", 26543);
	fstream _file;
	_file.open("./Local_server/ip_config.txt", ios::in);
	if (!_file) {
		_file.close();
		_file.open("./Local_server/ip_config.txt", ios::out);
		_file << "127.0.0.1" << " " << "26543" << endl;
	}
	std::string ip;
	int port;
	if (_file.is_open() == true) {
	_file >> ip >> port;
	}
	else {
		ip = "127.0.0.1";
		port = 26543;
	}
    _fff->connectServer(ip.c_str(), port);
	auto ChooseHeroScene = ChooseHeroScene::create(0, _fff, CONNECT_TO_INTERNET);
	Director::getInstance()->pushScene(ChooseHeroScene);
}
