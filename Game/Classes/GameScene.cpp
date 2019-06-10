#pragma once


#include "GameScene.h"

USING_NS_CC;
#define IS_SHOP_OPEN this->getChildByTag(133)
Scene* Game::createScene(string HeroName)
{
	auto scene = Scene::create();
	auto layer = Game::create();
	layer->initwithRole(HeroName);
	scene->addChild(layer);
	return scene;
}

void Game::initwithRole(string HeroName)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Time = 0;
	//初始化地图
	_tileMap = TMXTiledMap::create("map/map1.tmx");
	addChild(_tileMap, 0, 100);

	//获取碰撞层
	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(false);



	
	//获取地图上英雄的出生点
	auto group = _tileMap->getObjectGroup("hero");
	auto blueSpawnPoint = group->getObject("BlueSpawnpoint");
	auto redSpawnPoint = group->getObject("RedSpawnpoint");
	float bluex = blueSpawnPoint["x"].asFloat();
	float bluey = blueSpawnPoint["y"].asFloat();
	float redx = redSpawnPoint["x"].asFloat();
	float redy = redSpawnPoint["y"].asFloat();
	_ammoLayer = Layer::create();
	_tileMap->addChild(_ammoLayer,2);

	//我方英雄根据选择进行初始化
	if (HeroName == string("HbHouYi"))
	{
		hero1 = HouYi::create();
		((HouYi*)hero1)->initwithRole(HeroName,_tileMap, hero1, Vec2(bluex, bluey),(&unitsOnMap), _ammoLayer);
		addToMap(hero1, 0, 100);
		MyUnit.pushBack(hero1);
	}
	else if (HeroName == string("HbDaJi"))
	{
		hero1 = DaJi::create();
		((DaJi*)hero1)->initwithRole(HeroName,_tileMap, hero1, Vec2(bluex, bluey), (&unitsOnMap), _ammoLayer);
		addToMap(hero1, 0, 200);
		MyUnit.pushBack(hero1);

	}
	else if (HeroName == string("HbYaSe"))
	{
		hero1 = YaSe::create();
		((YaSe*)hero1)->initwithRole(HeroName, _tileMap, hero1, Vec2(bluex, bluey), (&unitsOnMap), _ammoLayer);
		addToMap(hero1, 0, 300);
		MyUnit.pushBack(hero1);
	}
	//我方英雄技能图标初始化
	InitSkillButton(HeroName);
	//随机产生一名敌方AI英雄并初始化
	srand(time(NULL));
	int RandNumber = rand() % 100;
	if (RandNumber >= 0 && RandNumber <= 33)
	{
		hero2 = HouYi::create();
        ((HouYi*)hero2)->initwithRole(string("HrHouYi"), _tileMap, hero2, Vec2(redx, redy), (&unitsOnMap), _ammoLayer);
        hero2->setPosition(500, 500);
        addToMap(hero2, 0, 200);
        EnemeyUnit.pushBack(hero2);
	}
	else if (RandNumber <= 66)
	{
		hero2 = DaJi::create();
		((DaJi*)hero2)->initwithRole(string("HrDaJi"), _tileMap, hero2, Vec2(redx, redy), (&unitsOnMap), _ammoLayer);
		hero2->setPosition(500, 500);
		addToMap(hero2, 0, 200);
		EnemeyUnit.pushBack(hero2);
	}
	else if (RandNumber <= 99)
	{
		hero2 = YaSe::create();
		((YaSe*)hero2)->initwithRole(string("HrYaSe"), _tileMap, hero2, Vec2(redx, redy), (&unitsOnMap), _ammoLayer);
		hero2->setPosition(500, 500);
		EnemeyUnit.pushBack(hero2);
	}

	//我方塔敌方塔初始化
	auto MyTower1 = Tower::create();
	MyTower1->InitWithRole(string("Tb1"), _tileMap, (&unitsOnMap), _ammoLayer);
	addToMap(MyTower1, 0, 200);MyTower.pushBack(MyTower1); 
	auto MyTower2 = Tower::create();
	MyTower2->InitWithRole(string("Tb2"), _tileMap, (&unitsOnMap), _ammoLayer);
	addToMap(MyTower2, 0, 200);MyTower.pushBack(MyTower2); 
	auto MyTower3 = Tower::create();
	MyTower3->InitWithRole(string("Tb3"), _tileMap, (&unitsOnMap), _ammoLayer);
	addToMap(MyTower3, 0, 200); MyTower.pushBack(MyTower3);
	auto EnemeyTower1 = Tower::create();
	EnemeyTower1->InitWithRole(string("Tr1"), _tileMap, (&unitsOnMap), _ammoLayer);
	addToMap(EnemeyTower1, 0, 200); EnemeyTower.pushBack(EnemeyTower1); 
	auto EnemeyTower2 = Tower::create();
	EnemeyTower2->InitWithRole(string("Tr2"), _tileMap, (&unitsOnMap), _ammoLayer);
	addToMap(EnemeyTower2, 0, 200); EnemeyTower.pushBack(EnemeyTower2); 
	auto EnemeyTower3 = Tower::create();
	EnemeyTower3->InitWithRole(string("Tr3"), _tileMap,(&unitsOnMap), _ammoLayer);
	addToMap(EnemeyTower3, 0, 200); MyTower.pushBack(MyTower3);
	//由于在逻辑上，我们先判断一塔的可攻击情况，所以顺序不可改
	MyTower.pushBack(MyTower3);
	MyUnit.pushBack(MyTower2);
	MyUnit.pushBack(MyTower1);
	EnemeyUnit.pushBack(EnemeyTower3);
	EnemeyUnit.pushBack(EnemeyTower2);
	EnemeyUnit.pushBack(EnemeyTower1);


	//监听器初始化
	listener = MouseController::create();
	if (hero1->getid()[2] == 'H') {
		listener->initListener(((HouYi*)hero1), getUnits());
	}
	if (hero1->getid()[2] == 'D') {
		listener->initListener(hero1, getUnits());
	}
	if (hero1->getid()[2] == 'Y') {
		listener->initListener(hero1, getUnits());
	}
	listener->changeOffset(Vec2::ZERO);
	//战绩页面初始化
	InitTabListener(hero1->getid(),hero2->getid());

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

	/////////////////////////

	TimerLabel = Label::createWithSystemFont("00:00", "Arial", 30);
	this->addChild(TimerLabel, 3);

	auto closeItem = MenuItemImage::create(
		"/button/closetoupper.png",
		"/button/closetoupper_selected.png",
		CC_CALLBACK_1(Game::menuItem1Callback, this));

	closeItem->setPosition(Vec2(
		origin.x + closeItem->getContentSize().width / 2,
		origin.y + visibleSize.height - closeItem->getContentSize().height / 2
	));


	
	auto shopButton = MenuItemImage::create(
		"/button/Money.png",
		"/button/Money.png",
		CC_CALLBACK_1(Game::createShopCallBack, this));

	shopButton->setPosition(30, visibleSize.height / 2 + 25);
	shopButton->setScale(0.8f);


	auto menu = Menu::create(closeItem, shopButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	_equipmentlLayer = Layer::create();
	this->addChild(_equipmentlLayer, 0, 138);
	auto Equipmentbg = Sprite::create("bg/Equipment.png");
	Equipmentbg->setAnchorPoint(Vec2(1, 0));
	Equipmentbg->setScale(0.85f);
	Equipmentbg->setPosition(960, 0);
	_equipmentlLayer->addChild(Equipmentbg);
	


	this->schedule(schedule_selector(Game::mapupdate), 1.0f / 45);
	this->schedule(schedule_selector(Game::TimeRecorder), 1.0f);
	this->schedule(schedule_selector(Game::GoldRecorder), 1.0f / 45);
	this->schedule(schedule_selector(Game::LevelUpdate), 1.0f/10);
}
bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}
void Game::InitTabListener(string Hero1Name,string Hero2Name)
{
	auto GradeLayer = Layer::create();
	this->addChild(GradeLayer,3,138);
	auto Gradebg = Sprite::create("bg/GradeScene.jpg");
	Gradebg->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	GradeLayer->addChild(Gradebg, 0); Gradebg->setScale(0.5f); GradeLayer->setVisible(false);
	auto LabelTitle = Label::create("Military Exploits", "fonts/Marker Felt.ttf", 35);
	LabelTitle->setPosition(480, 440); LabelTitle->enableGlow(Color4B::MAGENTA);
	auto LabelHero = Label::create("Your Hero", "fonts/Marker Felt.ttf", 30);
	LabelHero->setPosition(250, 410); LabelHero->enableGlow(Color4B::GREEN);
	GradeLayer->addChild(LabelHero, 1);
	auto YourHero = Sprite::create(Hero1Name + "/Choose.png"); YourHero->setScale(0.25f); YourHero->setPosition(250, 340);
	GradeLayer->addChild(YourHero, 1);
	GradeLayer->addChild(LabelTitle, 1);
	auto EnemeyHero = Sprite::create(Hero2Name + "/Choose.png"); EnemeyHero->setScale(0.25f); EnemeyHero->setPosition(250, 180);
	GradeLayer->addChild(EnemeyHero, 1);
	auto LabelHero2 = Label::create("Enemey Hero", "fonts/Marker Felt.ttf", 30);
	LabelHero2->setPosition(250, 240); LabelHero2->enableGlow(Color4B::RED);
	GradeLayer->addChild(LabelHero2, 1);
	auto TabListener = EventListenerKeyboard::create();
	TabListener->onKeyPressed = [this,Gradebg, GradeLayer](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_TAB)
		{
			GradeLayer->setVisible(true);
		}
		if (GradeLayer->getChildByTag(312) != nullptr) { GradeLayer->removeChildByTag(312); }
		if (GradeLayer->getChildByTag(313) != nullptr) { GradeLayer->removeChildByTag(313); }
		if (GradeLayer->getChildByTag(314) != nullptr) { GradeLayer->removeChildByTag(314); }
		if (GradeLayer->getChildByTag(315) != nullptr) { GradeLayer->removeChildByTag(315); }
		if (GradeLayer->getChildByTag(316) != nullptr) { GradeLayer->removeChildByTag(316); }
		if (GradeLayer->getChildByTag(317) != nullptr) { GradeLayer->removeChildByTag(317); }
		if (GradeLayer->getChildByTag(318) != nullptr) { GradeLayer->removeChildByTag(318); }
		if (GradeLayer->getChildByTag(319) != nullptr) { GradeLayer->removeChildByTag(319); }
		if (GradeLayer->getChildByTag(320) != nullptr) { GradeLayer->removeChildByTag(320); }
		if (GradeLayer->getChildByTag(321) != nullptr) { GradeLayer->removeChildByTag(321); }
		if (GradeLayer->getChildByTag(322) != nullptr) { GradeLayer->removeChildByTag(322); }
		if (GradeLayer->getChildByTag(323) != nullptr) { GradeLayer->removeChildByTag(323); }
		auto LabelLevel = Label::create("LV"+to_string(hero1->getExp()->getLevel()), "fonts/arial.ttf", 50);
		LabelLevel->setPosition(650, 330); LabelLevel->setAnchorPoint(Vec2(0, 0)); LabelLevel->enableGlow(Color4B::GREEN);
		auto LabelKill = Label::create("Number of kills:" + to_string(hero1->getKillHero()), "fonts/arial.ttf", 25);
		LabelKill->setPosition(340, 390); LabelKill->setAnchorPoint(Vec2(0, 0)); LabelKill->enableGlow(Color4B::GREEN);
		auto LabelDead = Label::create("Number of deaths:" + to_string(hero1->getDeath()) , "fonts/arial.ttf", 25);
		LabelDead->setPosition(340, 360); LabelDead->setAnchorPoint(Vec2(0, 0)); LabelDead->enableGlow(Color4B::GREEN);
		auto LabelKillSoldier = Label::create("Number of killsoldiers:" + to_string(hero1->getKillSoldiers()), "fonts/arial.ttf", 25);
		LabelKillSoldier->setPosition(340, 330); LabelKillSoldier->setAnchorPoint(Vec2(0, 0)); LabelKillSoldier->enableGlow(Color4B::GREEN);
		auto Labeldamage = Label::create("Current Damage:"+ to_string(hero1->getDamage()), "fonts/arial.ttf", 25);
		Labeldamage->setPosition(340, 300); Labeldamage->setAnchorPoint(Vec2(0, 0)); Labeldamage->enableGlow(Color4B::GREEN);
		auto LabelBlood = Label::create("Current Max HP:" + to_string(hero1->getMaxHp()), "fonts/arial.ttf", 25);
		LabelBlood->setPosition(340, 270); LabelBlood->setAnchorPoint(Vec2(0, 0)); LabelBlood->enableGlow(Color4B::GREEN);
		auto LabelLevel2 = Label::create("LV"+to_string(hero2->getExp()->getLevel()), "fonts/arial.ttf", 50);
		LabelLevel2->setPosition(650, 180); LabelLevel2->setAnchorPoint(Vec2(0, 0));
		auto LabelKill2 = Label::create("Number of kills:" + to_string(hero2->getKillHero()), "fonts/arial.ttf", 25);LabelLevel2->enableGlow(Color4B::RED);
		LabelKill2->setPosition(340, 240); LabelKill2->setAnchorPoint(Vec2(0, 0)); LabelKill2->enableGlow(Color4B::RED);
		auto LabelDead2 = Label::create("Number of deaths:" + to_string(hero2->getDeath()), "fonts/arial.ttf", 25);
		LabelDead2->setPosition(340, 210); LabelDead2->setAnchorPoint(Vec2(0, 0)); LabelDead2->enableGlow(Color4B::RED);
		auto LabelKillSoldier2 = Label::create("Number of killsoldiers:" + to_string(hero2->getKillSoldiers()), "fonts/arial.ttf", 25);
		LabelKillSoldier2->setPosition(340, 180); LabelKillSoldier2->setAnchorPoint(Vec2(0, 0)); LabelKillSoldier2->enableGlow(Color4B::RED);
		auto Labeldamage2 = Label::create("Current Damage:"+to_string(hero2->getDamage()), "fonts/arial.ttf", 25);
		Labeldamage2->setPosition(340, 150); Labeldamage2->setAnchorPoint(Vec2(0, 0)); Labeldamage2->enableGlow(Color4B::RED);
		auto LabelBlood2 = Label::create("Current Max HP:" + to_string(hero2->getMaxHp()), "fonts/arial.ttf", 25);
		LabelBlood2->setPosition(340, 120); LabelBlood2->setAnchorPoint(Vec2(0, 0)); LabelBlood2->enableGlow(Color4B::RED);
		GradeLayer->addChild(LabelKill, 1,312); GradeLayer->addChild(LabelDead, 1, 313); GradeLayer->addChild(LabelKillSoldier, 1, 314);
		GradeLayer->addChild(Labeldamage, 1, 315); GradeLayer->addChild(LabelBlood, 1, 316);
		GradeLayer->addChild(LabelLevel, 1, 317);
		GradeLayer->addChild(LabelKill2, 1, 318); GradeLayer->addChild(LabelDead2, 1, 319); GradeLayer->addChild(LabelKillSoldier2, 1, 320);
		GradeLayer->addChild(Labeldamage2, 1, 321); GradeLayer->addChild(LabelBlood2,1, 322);
		GradeLayer->addChild(LabelLevel2, 1, 323);

	};
	TabListener->onKeyReleased = [this, Gradebg, GradeLayer](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_TAB)
		{
			GradeLayer->setVisible(false);
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(TabListener, this);
}

//技能
void Game::InitSkillButton(string HeroName)
{
	auto Skill1Button = CCSprite::create("Skills/" + HeroName + "_Sk1.png");
	auto Skill2Button = CCSprite::create("Skills/" + HeroName + "_Sk2.png");
	auto Skill3Button = CCSprite::create("Skills/" + HeroName + "_Sk3.png");
	auto Skill4Button = CCSprite::create("Skills/" + HeroName + "_Sk4.png");
	Skill1Button->setScale(0.7f); Skill2Button->setScale(0.7f); Skill3Button->setScale(0.7f); Skill4Button->setScale(0.7f);
	Skill1Button->setPosition(330, Skill1Button->getContentSize().height / 2);
	Skill2Button->setPosition(430, Skill2Button->getContentSize().height / 2);
	Skill3Button->setPosition(530, Skill3Button->getContentSize().height / 2);
	Skill4Button->setPosition(630, Skill4Button->getContentSize().height / 2);
	Skill1Button->setOpacity(80);
	Skill2Button->setOpacity(80);
	Skill3Button->setOpacity(80);
	Skill4Button->setOpacity(80);
	this->addChild(Skill1Button,0,1); this->addChild(Skill2Button,0,2); this->addChild(Skill3Button,0,3); this->addChild(Skill4Button,0,4);
}


//返回主页面
void Game::menuItem1Callback(cocos2d::Ref* pSender)
{
	SpriteFrameCache::getInstance()->removeSpriteFrames();
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
	TimerLabel->setPosition(Director::getInstance()->getVisibleSize().width-50, Director::getInstance()->getVisibleSize().height - 15);

}

void Game::mapupdate(float dt)
{
	//auto sprite = this->getChildByTag(200);
	//auto sprite = _tileMap->getChildByTag(200);
	auto pos = hero1->getPosition();
	setViewpointCenter(pos);

	if (IS_SHOP_OPEN) { listener->setPause(1); }
	else { listener->setPause(0); }

	//check crash
	Vec2 tileCoord = this->tileCoordFromPosition(pos);
	int tileGid = _collidable->getTileGIDAt(tileCoord);
	if (tileGid) {
		hero1->stopAllActions();
		hero1->setPosition(hero1->getBeforePos());
	}
	else {
		hero1->setBeforePos(pos);
	}
	if (!EnemeySoldier.empty())
	{
		for (auto it = EnemeySoldier.begin(); it != EnemeySoldier.end(); it++)
		{
			for (auto it2 = MyUnit.begin(); it2 != MyUnit.end(); it2++)
			{
				auto ID = (*it2)->getid();
				if (ID[0] == 'B')
				{
					auto DIS = ((*it)->getPosition() - (*it2)->getPosition()).length();
					if (DIS < 300 && (*it2)->GetAlreadydead() == false)
					{
						(*it)->ChangeCanAttackSoldier(true);
					}
					else
					{
						(*it)->ChangeCanAttackSoldier(false);
					}
					if ((*it)->GetCanAttackSoldier() == true)
					{
						(*it)->changeAttackingTarget(*it2);
					}
				}
				if (ID[0] == 'T')
				{
					auto DIS = ((*it)->getPosition() - (*it2)->getPosition()).length();
					if (DIS < 350)
					{
						(*it)->ChangeCanAttackTower(true);
					}
					else
					{
						(*it)->ChangeCanAttackTower(false);
					}
					if ((*it)->GetCanAttackSoldier() == false&&(*it)->GetCanAttackTower() == true)
					{
						(*it)->changeAttackingTarget(*it2);
					}
				}
				if (ID[0] == 'H')
				{
					auto DIS = ((*it)->getPosition() - (*it2)->getPosition()).length();
					if (DIS < 200)
					{
						(*it)->ChangeCanAttackHero(true);
					}
					else
					{
						(*it)->ChangeCanAttackHero(false);
					}
					if ((*it)->GetCanAttackSoldier() == false && (*it)->GetCanAttackTower() == false && (*it)->GetCanAttackHero() == true)
					{
						(*it)->changeAttackingTarget(*it2);
					}
				}
				if ((*it)->GetCanAttackTower() == false && (*it)->GetCanAttackHero() == false && (*it)->GetCanAttackSoldier() == false)
				{
					(*it)->changeAttackingTarget(nullptr);
				}


			}
		}
	}
	if (!MySoldier.empty())
	{
		for (auto it = MySoldier.begin(); it != MySoldier.end(); it++)
		{
			for (auto it2 = EnemeyUnit.begin(); it2 != EnemeyUnit.end(); it2++)
			{

				auto ID = (*it2)->getid();
				if (ID[0] == 'B')
				{
					auto DIS = ((*it)->getPosition() - (*it2)->getPosition()).length();
					
					if(DIS < 300&& (*it2)->GetAlreadydead() == false)
					{
						(*it)->ChangeCanAttackSoldier(true);
					}
					else
					{
						(*it)->ChangeCanAttackSoldier(false);
					}
					if ((*it)->GetCanAttackSoldier() == true)
					{
						(*it)->changeAttackingTarget(*it2);
					}
				}
				if (ID[0] == 'T')
				{
					auto DIS = ((*it)->getPosition() - (*it2)->getPosition()).length();
					if (DIS < 350)
					{
						(*it)->ChangeCanAttackTower(true);
					}
					else
					{
						(*it)->ChangeCanAttackTower(false);
					}
					if ((*it)->GetCanAttackSoldier() == false && (*it)->GetCanAttackTower() == true)
					{
						(*it)->changeAttackingTarget(*it2);
					}
				}
				if (ID[0] == 'H')
				{
					auto DIS = ((*it)->getPosition() - (*it2)->getPosition()).length();
					if (DIS < 200)
					{
						(*it)->ChangeCanAttackHero(true);
					}
					else
					{
						(*it)->ChangeCanAttackHero(false);
					}
					if ((*it)->GetCanAttackSoldier() == false && (*it)->GetCanAttackTower() == false && (*it)->GetCanAttackHero() == true)
					{
						(*it)->changeAttackingTarget(*it2);
					}
				}
				if ((*it)->GetCanAttackTower() == false && (*it)->GetCanAttackHero() == false && (*it)->GetCanAttackSoldier() == false)
				{
					(*it)->changeAttackingTarget(nullptr);
				}


			}
		}
	}
	if (!EnemeyTower.empty())
	{
		for (auto it = EnemeyTower.begin(); it != EnemeyTower.end(); it++)
		{
			for (auto it2 = MyUnit.begin(); it2 != MyUnit.end(); it2++)
			{
				auto ID = (*it2)->getid();
				if (ID[0] == 'B')
				{
					auto DIS = ((*it)->getPosition() - (*it2)->getPosition()).length();
					if (DIS < 500)
					{
						(*it)->ChangeCanAttackSoldier(true);
					}
					else
					{
						(*it)->ChangeCanAttackSoldier(false);
					}
					if ((*it)->GetCanAttackSoldier() == true)
					{
						(*it)->changeAttackingTarget(*it2);
					}
				}
				if (ID[0] == 'H')
				{
					auto DIS = ((*it)->getPosition() - (*it2)->getPosition()).length();
					if (DIS < 500)
					{
						(*it)->ChangeCanAttackHero(true);
					}
					else
					{
						(*it)->ChangeCanAttackHero(false);
					}
					if ((*it)->GetCanAttackSoldier() == false && (*it)->GetCanAttackHero() == true)
					{
						(*it)->changeAttackingTarget(*it2);
					}
				}
				if ((*it)->GetCanAttackHero() == false && (*it)->GetCanAttackSoldier() == false)
				{
					(*it)->changeAttackingTarget(nullptr);
				}
				}
			}
		}
	if (!MyTower.empty())
	{
		for (auto it = MyTower.begin(); it != MyTower.end(); it++)
		{
			for (auto it2 = EnemeyUnit.begin(); it2 != EnemeyUnit.end(); it2++)
			{
				auto ID = (*it2)->getid();
				if (ID[0] == 'B')
				{
					auto DIS = ((*it)->getPosition() - (*it2)->getPosition()).length();
					if (DIS < 200)
					{
						(*it)->ChangeCanAttackSoldier(true);
					}
					else
					{
						(*it)->ChangeCanAttackSoldier(false);
					}
					if ((*it)->GetCanAttackSoldier() == true)
					{
						(*it)->changeAttackingTarget(*it2);
					}
				}
				if (ID[0] == 'H')
				{
					auto DIS = ((*it)->getPosition() - (*it2)->getPosition()).length();
					if (DIS < 200)
					{
						(*it)->ChangeCanAttackHero(true);
					}
					else
					{
						(*it)->ChangeCanAttackHero(false);
					}
					if ((*it)->GetCanAttackSoldier() == false && (*it)->GetCanAttackHero() == true)
					{
						(*it)->changeAttackingTarget(*it2);
					}
				}
				if ((*it)->GetCanAttackHero() == false && (*it)->GetCanAttackSoldier() == false)
				{
					(*it)->changeAttackingTarget(nullptr);
				}
			}
		}
	}
}
void Game::TimeRecorder(float dt)
{
	TimerLabel->removeFromParentAndCleanup(true);
	Time++;
	hero1->changeGold(100);
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
	
	this->addChild(TimerLabel, 3);
	if (Time % 2 == 0)
	{
		for (auto it = _ammoLayer->getChildren().begin(); it!=_ammoLayer->getChildren().end(); it++)
		{
			(*it)->setPosition(-2000, -2000);
			((ammo*)*it)->changeTargetPosition(Vec2(-2000, -2000));
		}
	}//暂时修复有时子弹无法消失的bug
	if (Time==5||Time%40==0)
	{
		auto Br1_1 = Soldier::create();
		Br1_1->Soldierinit("Br1",1, _tileMap, (&unitsOnMap), _ammoLayer);
		addToMap(Br1_1, 0,Time+10001); EnemeySoldier.pushBack(Br1_1); EnemeyUnit.pushBack(Br1_1);
		auto Br2_1 = Soldier::create();
		Br2_1->Soldierinit("Br2",1, _tileMap, (&unitsOnMap), _ammoLayer);
		addToMap(Br2_1, 0,Time+10002); EnemeySoldier.pushBack(Br2_1); EnemeyUnit.pushBack(Br2_1);
		auto Br3_1 = Soldier::create();
		Br3_1->Soldierinit("Br3",1, _tileMap, (&unitsOnMap), _ammoLayer);
		addToMap(Br3_1, 0, Time + 10003); EnemeySoldier.pushBack(Br3_1); EnemeyUnit.pushBack(Br3_1);
		auto Br1_2 = Soldier::create();
		Br1_2->Soldierinit("Br1", 2, _tileMap, (&unitsOnMap), _ammoLayer);
		addToMap(Br1_2, 0, Time + 10004); EnemeySoldier.pushBack(Br1_2); EnemeyUnit.pushBack(Br1_2);
		auto Br2_2 = Soldier::create();
		Br2_2->Soldierinit("Br2", 2, _tileMap, (&unitsOnMap), _ammoLayer);
		addToMap(Br2_2, 0, Time + 10005); EnemeySoldier.pushBack(Br2_2); EnemeyUnit.pushBack(Br2_2);
		auto Br3_2 = Soldier::create();
		Br3_2->Soldierinit("Br3", 2, _tileMap, (&unitsOnMap), _ammoLayer);
		addToMap(Br3_2, 0, Time + 10006); EnemeySoldier.pushBack(Br3_2); EnemeyUnit.pushBack(Br3_2);
		auto Bb1_1 = Soldier::create();
		Bb1_1->Soldierinit("Bb1", 1, _tileMap, (&unitsOnMap), _ammoLayer);
		addToMap(Bb1_1, 0, Time + 10007); MySoldier.pushBack(Bb1_1); MyUnit.pushBack(Bb1_1);
		auto Bb2_1 = Soldier::create();
		Bb2_1->Soldierinit("Bb2", 1, _tileMap, (&unitsOnMap), _ammoLayer);
		addToMap(Bb2_1, 0, Time + 10008); MySoldier.pushBack(Bb2_1); MyUnit.pushBack(Bb2_1);
		auto Bb3_1 = Soldier::create();
		Bb3_1->Soldierinit("Bb3", 1, _tileMap, (&unitsOnMap), _ammoLayer);
		addToMap(Bb3_1, 0, Time + 10009); MySoldier.pushBack(Bb3_1); MyUnit.pushBack(Bb3_1);
		auto Bb1_2 = Soldier::create();
		Bb1_2->Soldierinit("Bb1", 2, _tileMap, (&unitsOnMap), _ammoLayer);
		addToMap(Bb1_2, 0, Time + 10010); MySoldier.pushBack(Bb1_2); MyUnit.pushBack(Bb1_2);
		auto Bb2_2 = Soldier::create();
		Bb2_2->Soldierinit("Bb2", 2, _tileMap, (&unitsOnMap), _ammoLayer);
		addToMap(Bb2_2, 0, Time + 10011); MySoldier.pushBack(Bb2_2); MyUnit.pushBack(Bb2_2);
		auto Bb3_2 = Soldier::create();
		Bb3_2->Soldierinit("Bb3", 2, _tileMap, (&unitsOnMap), _ammoLayer);
		addToMap(Bb3_2, 0, Time + 10012); MySoldier.pushBack(Bb3_2); MyUnit.pushBack(Bb3_2);
	}
	if (!MySoldier.empty())
	{
		for (auto it = MySoldier.begin(); it != MySoldier.end(); it++)
		{
			(*it)->AttackingJudgeAI();
		}
	}
	if (!EnemeySoldier.empty())
	{
		for (auto it = EnemeySoldier.begin(); it != EnemeySoldier.end(); it++)
		{
			(*it)->AttackingJudgeAI();
		}
	}
	if (!EnemeyTower.empty())
	{
		for (auto it = EnemeyTower.begin(); it != EnemeyTower.end(); it++)
		{
			(*it)->AttackingJudgeAI();
		}
	}
	/*if (!MyTower.empty())
	{
		for (auto it = MyTower.begin(); it != MyTower.end(); it++)
		{
			(*it)->AttackingJudgeAI();
		}
	}*/
	return;
}

void Game::GoldRecorder(float dt)
{
	if (goldLabel != nullptr) {
		goldLabel->removeFromParentAndCleanup(true);
	}
	std::string gold_str = "$: "+std::to_string(hero1->getGold());
	goldLabel = Label::createWithSystemFont(gold_str, "Arial", 30);
	goldLabel->setPosition(Vec2(10,250));
	goldLabel->setAnchorPoint(Vec2(0, 0.5f));
	this->addChild(goldLabel, 3);
	return;
}
void Game::LevelUpdate(float dt)
{
	switch ((hero1->getid())[2]) {
	case 'H': {
		auto hero = static_cast<HouYi*>(hero1);
		if (hero->getSk1Level() > 0) {
			(this->getChildByTag(1))->setOpacity(255);
			if (hero->getSk1CdLeft() > 0) {
				(this->getChildByTag(1))->setOpacity(140);
			}
			if ((this->getChildByTag(11)) != nullptr)this->removeChildByTag(11);
			auto Label1 = Label::createWithSystemFont("Lv." + std::to_string(hero->getSk1Level()), "Arial", 20);
			Label1->enableGlow(Color4B::BLACK);
			Label1->setPosition(Vec2(310, 20));
			this->addChild(Label1, 0, 11);
		}
		if (hero->getSk2Level() > 0) {
			(this->getChildByTag(2))->setOpacity(255);
			if (hero->getSk2CdLeft() > 0) {
				(this->getChildByTag(2))->setOpacity(140);
			}
			if ((this->getChildByTag(22)) != nullptr)this->removeChildByTag(22);
			auto Label2 = Label::createWithSystemFont("Lv." + std::to_string(hero->getSk2Level()), "Arial", 20);
			Label2->setPosition(Vec2(410, 20));
			Label2->enableGlow(Color4B::BLACK);
			this->addChild(Label2, 0, 22);
		}
		if (hero->getSk3Level() > 0) {
			(this->getChildByTag(3))->setOpacity(255);
			if (hero->getSk3CdLeft() > 0) {
				(this->getChildByTag(3))->setOpacity(140);
			}
			if ((this->getChildByTag(33)) != nullptr)this->removeChildByTag(33);
			auto Label3 = Label::createWithSystemFont("Lv." + std::to_string(hero->getSk3Level()), "Arial", 20);
			Label3->setPosition(Vec2(510, 20));
			Label3->enableGlow(Color4B::BLACK);
			this->addChild(Label3, 0, 33);
		}
		if (hero->getSkillPoint() == 0) {
			if (this->getChildByTag(1111) != nullptr) { this->removeChildByTag(1111); }
			if (this->getChildByTag(2222) != nullptr) { this->removeChildByTag(2222); }
			if (this->getChildByTag(3333) != nullptr) { this->removeChildByTag(3333); }
		}
		else {
			if (this->getChildByTag(1111) == nullptr&&hero->getSk1Level()<3) {
				auto Skill1Lock = Sprite::create("button/lock.png");
				Skill1Lock->setPosition(Vec2(350, 40));
				this->addChild(Skill1Lock, 0, 1111);
			}
			if (this->getChildByTag(2222) == nullptr&&hero->getSk2Level() < 3) {
				auto Skill2Lock = Sprite::create("button/lock.png");
				Skill2Lock->setPosition(Vec2(450, 40));
				this->addChild(Skill2Lock, 0, 2222);
			}
			if (this->getChildByTag(3333) == nullptr&&hero->getSk3Level() < 2) {
				auto Skill3Lock = Sprite::create("button/lock.png");
				Skill3Lock->setPosition(Vec2(550, 40));
				this->addChild(Skill3Lock, 0, 3333);
			}
		}
	};
	case 'D': {

	};
	case 'Y': {

	};
	}
	
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
	hero1->stopAllActions();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (IS_SHOP_OPEN) { return; }
	_shopLayer = Layer::create();
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
	//shoe
	auto ShoeLabel1 = Label::createWithSystemFont("FastShoe:$200", "Arial", 20);
	auto ShoeLabel2 = Label::createWithSystemFont("Speed+100", "Arial", 20);
	ShoeLabel1->setPosition(Vec2(37, -15));
	ShoeLabel2->setPosition(Vec2(37, -38));
	itemShoe->addChild(ShoeLabel1);
	itemShoe->addChild(ShoeLabel2);
	itemShoe->setPosition(shopbg->getPosition() + Vec2(-200, 100));
	//hat
	auto itemHat = MenuItemImage::create(
		"item/hat_normal.png",
		"item/hat_selected.png",
		CC_CALLBACK_1(Game::buyHatCallBack, this)
	);
	auto HatLabel1 = Label::createWithSystemFont("TankHat:$200", "Arial", 20);
	auto HatLabel2 = Label::createWithSystemFont("MaxHp+10000", "Arial", 20);
	HatLabel1->setPosition(Vec2(37, -15));
	HatLabel2->setPosition(Vec2(37, -38));
	itemHat->addChild(HatLabel1);
	itemHat->addChild(HatLabel2);
	itemHat->setPosition(shopbg->getPosition() + Vec2(0, 100));
	//sword
	auto itemSword = MenuItemImage::create(
		"item/shield_normal.png",
		"item/shield_selected.png",
		CC_CALLBACK_1(Game::buySwordCallBack, this)
	);
	auto SwordLabel1 = Label::createWithSystemFont("UglySword:$200", "Arial", 20);
	auto SwordLabel2 = Label::createWithSystemFont("Damage+400", "Arial", 20);
	SwordLabel1->setPosition(Vec2(37, -15));
	SwordLabel2->setPosition(Vec2(37, -38));
	itemSword->addChild(SwordLabel1);
	itemSword->addChild(SwordLabel2);
	itemSword->setPosition(shopbg->getPosition() + Vec2(200, 100));

	
	auto eqbg1 = Sprite::create("bg/EquipmentChoose.png");
	eqbg1->setScale(0.8f);
	eqbg1->setPosition(290,150);
	_shopLayer->addChild(eqbg1,1);
	auto Notice = Label::create("You can sell your equipment here,\nbut it will be sold at half the purchase price", "fonts/Arial.ttf",20);
	Notice->enableGlow(Color4B::BLACK); Notice->setPosition(350, 60);
	_shopLayer->addChild(Notice, 1);
	auto Sell1 = MenuItemImage::create("bg/Sell1.png","bg/Sell11.png",CC_CALLBACK_1(Game::sell1CallBack, this));
	Sell1->setPosition(460, 200);
	auto Sell2 = MenuItemImage::create("bg/Sell2.png", "bg/Sell22.png", CC_CALLBACK_1(Game::sell2CallBack, this));
	Sell2->setPosition(560, 200);
	auto Sell3 = MenuItemImage::create("bg/Sell3.png", "bg/Sell33.png", CC_CALLBACK_1(Game::sell3CallBack, this));
	Sell3->setPosition(460, 150);
	auto Sell4 = MenuItemImage::create("bg/Sell4.png", "bg/Sell44.png", CC_CALLBACK_1(Game::sell4CallBack, this));
	Sell4->setPosition(560, 150);
	auto Sell5 = MenuItemImage::create("bg/Sell5.png", "bg/Sell55.png", CC_CALLBACK_1(Game::sell5CallBack, this));
	Sell5->setPosition(460, 100);
	auto Sell6 = MenuItemImage::create("bg/Sell6.png", "bg/Sell66.png", CC_CALLBACK_1(Game::sell6CallBack, this));
	Sell6->setPosition(560, 100);
	auto mn = Menu::create(closeShopButton, itemShoe,itemHat,itemSword,Sell1, Sell2,Sell3,Sell4,Sell5,Sell6,NULL);
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

void Game::buyShoeCallBack(cocos2d::Ref* pSender) 
{
	if (!IS_SHOP_OPEN) { return; }
	hero1->addEquipment("Shoe", _equipmentlLayer,_shopLayer);
}
void Game::buyHatCallBack(cocos2d::Ref* pSender)
{
	if (!IS_SHOP_OPEN) { return; }
	hero1->addEquipment("Hat", _equipmentlLayer, _shopLayer);
}
void Game::buySwordCallBack(cocos2d::Ref* pSender)
{
	if (!IS_SHOP_OPEN) { return; }
	hero1->addEquipment("Sword",_equipmentlLayer, _shopLayer);
}
void Game::sell1CallBack(cocos2d::Ref* pSender)
{
	if (!IS_SHOP_OPEN) { return; }
	hero1->sellEquipment(0, _equipmentlLayer, _shopLayer);
}
void Game::sell2CallBack(cocos2d::Ref* pSender)
{
	if (!IS_SHOP_OPEN) { return; }
	hero1->sellEquipment(1, _equipmentlLayer, _shopLayer);
}
void Game::sell3CallBack(cocos2d::Ref* pSender)
{
	if (!IS_SHOP_OPEN) { return; }
	hero1->sellEquipment(2, _equipmentlLayer, _shopLayer);
}
void Game::sell4CallBack(cocos2d::Ref* pSender)
{
	if (!IS_SHOP_OPEN) { return; }
	hero1->sellEquipment(3, _equipmentlLayer, _shopLayer);
}
void Game::sell5CallBack(cocos2d::Ref* pSender)
{
	if (!IS_SHOP_OPEN) { return; }
	hero1->sellEquipment(4, _equipmentlLayer, _shopLayer);
}
void Game::sell6CallBack(cocos2d::Ref* pSender)
{
	if (!IS_SHOP_OPEN) { return; }
	hero1->sellEquipment(5, _equipmentlLayer, _shopLayer);
}
