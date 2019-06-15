#include "ChooseHeroScene.h"
#include "SimpleAudioEngine.h"

#define CENTERX origin.x+visibleSize.width/2
#define CENTERY origin.y+visibleSize.height/2
USING_NS_CC;

ChooseHeroScene* ChooseHeroScene::create(INT32 playerNumber, SocketClient* socket_client, INT32 mode)
{
	auto chooseHeroScene = new(std::nothrow)ChooseHeroScene;
	if (chooseHeroScene && chooseHeroScene->init(playerNumber, socket_client, mode))
	{
		chooseHeroScene->autorelease();
		return chooseHeroScene;
	}
	CC_SAFE_DELETE(chooseHeroScene);
	return nullptr;
}

bool ChooseHeroScene::init(INT32 playerNumber, SocketClient* socket_client, INT32 mode)
{
	if (!Scene::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (mode == CONNECT_TO_INTERNET)
	{
		_socket_client = socket_client;
		_mode = mode;
		_playerNumber = playerNumber;
	}
	if (mode == DISCONNECTED)
	{
		_socket_client = NULL;
		_mode = mode;
		_playerNumber = playerNumber;
	}
	//background
	auto bg = Sprite::create("/bg/ChooseHeroScene.jpg");
	bg->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2
	));
	this->addChild(bg, 0);
	////建立选择标签////
	auto label = Label::create(ChooseHeroScene::FontToUTF8("请选择你要出战的英雄"), "fonts/Hanzi.ttf", 50);
	label->setPosition(480, 500);
	label->enableGlow(Color4B::YELLOW);
	this->addChild(label);


	auto HouYi = MenuItemImage::create("HrHouYi/Choose.png", "HrHouYi/Choose.png");
	HouYi->setScale(0.5f);
	HouYi->setPosition(Vec2(210, 290));
	this->addChild(HouYi);
	auto HouYiLabel = Label::create(ChooseHeroScene::FontToUTF8("后羿"), "fonts/XingKai.TTF", 40);
	HouYiLabel->setPosition(190, 440);
	HouYiLabel->enableGlow(Color4B::GRAY);
	this->addChild(HouYiLabel);
	auto HouYiEnterLabel = Label::create(ChooseHeroScene::FontToUTF8("确认选择"), "fonts/XingKai.TTF", 40);
	auto HouYiEnterMenu = MenuItemLabel::create(HouYiEnterLabel, CC_CALLBACK_1(ChooseHeroScene::HouYiEnterCallback, this));
	HouYiEnterMenu->setPosition(Vec2(200, 160));
	auto HouYiSkillLabel = Label::create(ChooseHeroScene::FontToUTF8("技能说明"), "fonts/XingKai.TTF", 40);
	auto HouYiSkillMenu = MenuItemLabel::create(HouYiSkillLabel, CC_CALLBACK_1(ChooseHeroScene::HouyiSkillCallback, this));
	HouYiSkillMenu->setPosition(Vec2(200, 110));
	auto HouYiMenu = Menu::create(HouYiEnterMenu, HouYiSkillMenu, NULL);
	HouYiMenu->setPosition(Vec2::ZERO);
	this->addChild(HouYiMenu, 2);

	auto Yase = MenuItemImage::create("HrYase/Choose.png", "HrYase/Choose.png");
	Yase->setScale(0.5f);
	Yase->setPosition(Vec2(450, 300));
	this->addChild(Yase);
	auto YaseLabel = Label::create(ChooseHeroScene::FontToUTF8("亚瑟"), "fonts/XingKai.TTF", 40);
	YaseLabel->setPosition(450, 440);
	YaseLabel->enableGlow(Color4B::BLUE);
	this->addChild(YaseLabel);
	auto YaseEnterLabel = Label::create(ChooseHeroScene::FontToUTF8("确认选择"), "fonts/XingKai.TTF", 40);
	auto YaseEnterMenu = MenuItemLabel::create(YaseEnterLabel, CC_CALLBACK_1(ChooseHeroScene::YaseEnterCallback, this));
	YaseEnterMenu->setPosition(Vec2(450, 160));
	auto YaseSkillLabel = Label::create(ChooseHeroScene::FontToUTF8("技能说明"), "fonts/XingKai.TTF", 40);
	auto YaseSkillMenu = MenuItemLabel::create(YaseSkillLabel, CC_CALLBACK_1(ChooseHeroScene::YaseSkillCallback, this));
	YaseSkillMenu->setPosition(Vec2(450, 110));
	auto YaseMenu = Menu::create(YaseEnterMenu, YaseSkillMenu, NULL);
	YaseMenu->setPosition(Vec2::ZERO);
	this->addChild(YaseMenu, 2);


	auto Daji = MenuItemImage::create("HrDaji/Choose.png", "HrDaji/Choose.png");
	Daji->setScale(0.5f);
	Daji->setPosition(Vec2(710, 290));
	this->addChild(Daji);
	auto DajiLabel = Label::create(ChooseHeroScene::FontToUTF8("妲己"), "fonts/XingKai.TTF", 40);

	DajiLabel->setPosition(700, 440);
	DajiLabel->enableGlow(Color4B::ORANGE);
	this->addChild(DajiLabel);
	auto DajiEnterLabel = Label::create(ChooseHeroScene::FontToUTF8("确认选择"), "fonts/XingKai.TTF", 40);
	auto DajiEnterMenu = MenuItemLabel::create(DajiEnterLabel, CC_CALLBACK_1(ChooseHeroScene::DajiEnterCallback, this));
	DajiEnterMenu->setPosition(Vec2(700, 160));
	auto DajiSkillLabel = Label::create(ChooseHeroScene::FontToUTF8("技能说明"), "fonts/XingKai.TTF", 40);
	auto DajiSkillMenu = MenuItemLabel::create(DajiSkillLabel, CC_CALLBACK_1(ChooseHeroScene::DajiSkillCallback, this));
	DajiSkillMenu->setPosition(Vec2(700, 110));
	auto DajiMenu = Menu::create(DajiEnterMenu, DajiSkillMenu, NULL);
	DajiMenu->setPosition(Vec2::ZERO);
	this->addChild(DajiMenu, 2);

	//return button
	auto closeItem = MenuItemImage::create(
		"/button/closetoupper.png",
		"/button/closetoupper_selected.png",
		CC_CALLBACK_1(ChooseHeroScene::menuItem1Callback, this));

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


void ChooseHeroScene::YaseEnterCallback(cocos2d::Ref* pSender)
{
	if (_mode == CONNECT_TO_INTERNET) {
		_socket_client->my_hero = YASE;
		char WelData[24];
		recv(_socket_client->_socektClient, WelData, 24, 0);
		_socket_client->HeroMessage();
		auto GameScene = Game::createScene("HbYaSe", _socket_client->playerNumber, _socket_client, _mode);
		Director::getInstance()->pushScene(GameScene);
	}
	else {
		auto GameScene = Game::createScene("HbYaSe", 0, NULL, _mode);
		Director::getInstance()->pushScene(GameScene);
	}
}
void ChooseHeroScene::DajiEnterCallback(cocos2d::Ref* pSender)
{
	if (_mode == CONNECT_TO_INTERNET) {
		_socket_client->my_hero = DAJI;
		char WelData[24];
		recv(_socket_client->_socektClient, WelData, 24, 0);
		_socket_client->HeroMessage();
		auto GameScene = Game::createScene("HbDaJi", _socket_client->playerNumber, _socket_client, _mode);
		Director::getInstance()->pushScene(GameScene);
	}
	else {
		auto GameScene = Game::createScene("HbDaJi", 0, NULL, _mode);
		Director::getInstance()->pushScene(GameScene);
	}
}
void ChooseHeroScene::HouYiEnterCallback(cocos2d::Ref* pSender)
{
	if (_mode == CONNECT_TO_INTERNET) {
		_socket_client->my_hero = HOUYI;
		char WelData[24];
		recv(_socket_client->_socektClient, WelData, 24, 0);
		_socket_client->HeroMessage();
		auto GameScene = Game::createScene("HbHouYi", _socket_client->playerNumber, _socket_client, _mode);
		Director::getInstance()->pushScene(GameScene);
	}
	else {
		auto GameScene = Game::createScene("HbHouYi", 0, NULL, _mode);
		Director::getInstance()->pushScene(GameScene);
	}
}

void ChooseHeroScene::HouyiSkillCallback(cocos2d::Ref* pSender) {
	auto sc = HouyiSkillScene::createScene();
	Director::getInstance()->pushScene(sc);
}
void ChooseHeroScene::YaseSkillCallback(cocos2d::Ref* pSender) {
	auto sc = YaseSkillScene::createScene();
	Director::getInstance()->pushScene(sc);
}
void ChooseHeroScene::DajiSkillCallback(cocos2d::Ref* pSender) {
	auto sc = DajiSkillScene::createScene();
	Director::getInstance()->pushScene(sc);
}
void ChooseHeroScene::menuItem1Callback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

char *ChooseHeroScene::FontToUTF8(const char* font) {
	int len = MultiByteToWideChar(CP_ACP, 0, font, -1, NULL, 0);
	wchar_t *wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, font, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char *str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr)delete[] wstr;
	return str;
}