#pragma once


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
	Time = 0;
	//初始化地图
	_tileMap = TMXTiledMap::create("map/map1.tmx");
	addChild(_tileMap, 0, 100);

	//初始化碰撞层
	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(false);

	//获取地图设置出生点
	auto group = _tileMap->getObjectGroup("hero");
	auto spawnPoint = group->getObject("spawnpoint");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	//CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("HouYi/attack.plist");
   //初始化单位属性
	auto hero1data = new(unitdata);
	hero1data->initial(string("HouYi"));

	auto act = Animate::create(AnimationCache::getInstance()->getAnimation("HouYidown_attack"));
	myHero = unit::create();
	myHero->setPosition(Vec2(x, y));	
	myHero->initial(hero1data,_tileMap,&unitsOnMap);
	myHero->runAction(act);
	addToMap(myHero, 2, 200);
	myHero->setScale(0.6);



	//初始化监听器
	listener = MouseController::create();
	listener->initListener(myHero,getUnits());
	listener->changeOffset(Vec2::ZERO);
	//////////////////////////
	/*
	
	auto hp2 = Sprite::create("/HP/bloodrect.png");
	auto hp3 = Sprite::create("/HP/GreenBlood.png");
	_tileMap->addChild(hp3, 10);
	_tileMap->addChild(hp2, 9);
	hp3->setScale(20);
	hp2->setScale(10);
	hp2->setPosition(x, y);
	hp3->setPosition(x + 200, y + 250);*/
	auto hero2 = unit::create();hero2->initial(hero1data,_tileMap, &unitsOnMap);
	hero2->setPosition(Vec2(x+600, y+500));	// + 200, y + 200)); 
	hero2->changeid("Ta");
	addToMap(hero2, 2, 202);
	hero2->setScale(0.5);
	hero2->runAction(act);
	/////////////////////////
	//初始化时间标签
	TimerLabel = Label::createWithSystemFont("00:00", "Arial", 30);
	this->addChild(TimerLabel, 3);


	//初始化退出按钮
	auto closeItem = MenuItemImage::create(
		"/button/closetoupper.png",
		"/button/closetoupper_selected.png",
		CC_CALLBACK_1(Game::menuItem1Callback, this));

	closeItem->setPosition(Vec2(
		origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2
	));


	////  商店界面  ////

	//进入按钮
	auto shopButton = MenuItemImage::create(
		"/button/Money.png",
		"/button/Money.png",
		CC_CALLBACK_1(Game::createShopCallBack, this));

	shopButton->setPosition(30, visibleSize.height / 2 + 25);
	shopButton->setScale(0.8f);


	auto menu = Menu::create(closeItem, shopButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);

	//////////  循环更新  /////////
	this->schedule(schedule_selector(Game::mapupdate), 1.0f / 60);
	this->schedule(schedule_selector(Game::TimeRecorder), 1.0f);
	this->schedule(schedule_selector(Game::GoldRecorder), 1.0f/60);
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
	//_tileMap->
	//当前中心点
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//得到精灵走后地图移动的目标位置
	x = MIN(x, MapWidth - visibleSize.width / 2);
	y = MIN(y, MapHeight - visibleSize.height / 2);
	Vec2 pointB = Vec2(x, y);
	//需要调整的方位
	Vec2 offset = pointA - pointB;
	_tileMap->setPosition(offset);
	listener->changeOffset(offset);
	///skillListener->changeOffset(offset);
	TimerLabel->setVisible(true);
	TimerLabel->setPosition(Director::getInstance()->getVisibleSize().width-50, Director::getInstance()->getVisibleSize().height - 15);

}

void Game::mapupdate(float dt)
{
	//auto sprite = this->getChildByTag(200);
	//auto sprite = _tileMap->getChildByTag(200);
	auto pos = myHero->getPosition();
	setViewpointCenter(pos);

	if (IS_SHOP_OPEN) { listener->setPause(1); }
	else { listener->setPause(0); }

	//check crash
	Vec2 tileCoord = this->tileCoordFromPosition(pos);
	int tileGid = _collidable->getTileGIDAt(tileCoord);
	if (tileGid) {
		myHero->stopAllActions();
		myHero->setPosition(myHero->getBeforePos());
	}
	else {
		myHero->setBeforePos(pos);
	}
}

void Game::TimeRecorder(float dt)
{

	TimerLabel->removeFromParentAndCleanup(true);
	Time++;
	myHero->changeGold(50);
	int Minute = Time / 60;
	int Second = Time % 60;
	std::string second_str = std::to_string(Second);
	std::string minute_str = std::to_string(Minute);
	std::string Second_str;
	std::string Minute_str;
	if (Second < 10)
	{
		Second_str = '0' + second_str;
	}
	else
		Second_str = second_str;

	if (Minute < 10)
	{
		Minute_str = '0' + minute_str;
	}
	else
		Minute_str = minute_str;
	std::string str = Minute_str + ':' + Second_str;
	TimerLabel = Label::createWithSystemFont(str, "Arial", 30);
	TimerLabel->setVisible(false);
	this->addChild(TimerLabel, 3);
	return;
}

void Game::GoldRecorder(float dt)
{
	if (goldLabel != nullptr) {
		goldLabel->removeFromParentAndCleanup(true);
	}
	std::string gold_str = "$: "+std::to_string(myHero->getGold());
	goldLabel = Label::createWithSystemFont(gold_str, "Arial", 30);
	goldLabel->setPosition(Vec2(10,250));
	goldLabel->setAnchorPoint(Vec2(0, 0.5f));
	this->addChild(goldLabel, 3);
	return;
}

cocos2d::Vec2 Game::tileCoordFromPosition(cocos2d::Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height*_tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x, y);
}

Vector<unit*>* Game::getUnits()
{
	return &unitsOnMap;
}

void Game::addToMap(unit* unit, int zorder, int tag) {
	unitsOnMap.pushBack(unit);
	_tileMap->addChild(unit, zorder, tag);
}

void Game::createShopCallBack(cocos2d::Ref* pSender) {
	myHero->stopAllActions();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (IS_SHOP_OPEN) { return; }
	auto _shopLayer = Layer::create();
	auto shopbg = Sprite::create("bg/shop.png");
	shopbg->setPosition(Vec2(
		visibleSize.width / 2,
		visibleSize.height / 2
	));
	//closebutton
	auto closeShopButton = MenuItemImage::create(
		"/button/back.png",
		"/button/back.png",
		CC_CALLBACK_1(Game::closeShopCallBack, this)
	);
	closeShopButton->setPosition(shopbg->getPosition() + Vec2(250, -200));

	//item
	auto itemShoe = MenuItemImage::create(
		"/item/shoe_normal.png",
		"/item/shoe_selected.png",
		CC_CALLBACK_1(Game::buyShoeCallBack, this)
	);
	itemShoe->setPosition(shopbg->getPosition() + Vec2(-200, 0));
	auto itemHat = MenuItemImage::create(
		"item/helmet_normal.png",
		"item/helmet_selected.png",
		CC_CALLBACK_1(Game::buyHelmetCallBack, this)
	);
	itemHat->setPosition(shopbg->getPosition() + Vec2(0, 0));
	auto itemSword = MenuItemImage::create(
		"item/sword_nomal.jpg",
		"item/sword_selected.jpg",
		CC_CALLBACK_1(Game::buySwordCallBack, this)
	);
	itemSword->setPosition(shopbg->getPosition() + Vec2(200, 0));


	auto mn = Menu::create(closeShopButton, itemShoe,itemHat,itemSword,NULL);

	mn->setPosition(Vec2::ZERO);
	_shopLayer->addChild(mn,1);
	_shopLayer->addChild(shopbg);
	this->addChild(_shopLayer, 2,133);
}

void Game::closeShopCallBack(cocos2d::Ref* pSender) {
	this->getChildByTag(133)->removeFromParentAndCleanup(true);
}

void Game::createSkillLayerCallBack(cocos2d::Ref * pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (this->getChildByTag(250)) { return; }
	_skillLayer = Layer::create();
	auto shopbg = Sprite::create("bg/shop.png");
	shopbg->setPosition(Vec2(
		visibleSize.width / 2,
		visibleSize.height / 2
	));
	//closebutton
	auto undoSkillButton = MenuItemImage::create(
		"/button/back.png",
		"/button/back.png",
		CC_CALLBACK_1(Game::undoSkillCallBack, this)
	);
	undoSkillButton->setPosition(shopbg->getPosition() + Vec2(300, 250));
	///skillListener = MouseController::create();
	///skillListener->initListener(unit* hero1);
	///skillListener->changeOffset(Vec2::ZERO);
}

void Game::undoSkillCallBack(cocos2d::Ref * pSender)
{
	_skillLayer->removeFromParent();
}

void Game::buyShoeCallBack(cocos2d::Ref* pSender) { 
	if (!IS_SHOP_OPEN) { return; }
	myHero->addEquipment("Shoe"); 
}
void Game::buyHelmetCallBack(cocos2d::Ref* pSender) { 
	if (!IS_SHOP_OPEN) { return; }
	myHero->addEquipment("Helmet");
	myHero->getHp()->changeCur(600000);
}
void Game::buySwordCallBack(cocos2d::Ref* pSender) {
	if (!IS_SHOP_OPEN) { return; }
	myHero->addEquipment("Sword");
}

//找到id对应Unit
/*unit* Game::getUnitWithId(std::string id)
{
	auto it = unitsOnMap.begin();
	for (; it < unitsOnMap.end(); ++it) {
		if ((*it)->getid()[0] != 'H') { continue; }
		else if ((*it)->getid() == id) {
			return (*it);
		}
	}
	return nullptr;
}
*/

