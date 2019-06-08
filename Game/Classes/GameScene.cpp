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
	auto spawnPoint = group->getObject("spawnpoint");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	//我方英雄根据选择进行初始化
	if (HeroName == string("HbHouYi"))
	{
		hero1 = HouYi::create();
		((HouYi*)hero1)->initwithRole(HeroName, _tileMap, Vec2(x, y),(&unitsOnMap));
		addToMap(hero1, 0, 200);
		MyUnit.pushBack(hero1);
	}
	else if (HeroName == string("HbDaJi"))
	{
		hero1 = DaJi::create();
		((DaJi*)hero1)->initwithRole(HeroName, _tileMap, Vec2(x, y), (&unitsOnMap));
		addToMap(hero1, 0, 200);
		MyUnit.pushBack(hero1);

	}
	else if (HeroName == string("HbYaSe"))
	{
		hero1 = YaSe::create();
		((YaSe*)hero1)->initwithRole(HeroName, _tileMap, Vec2(x, y), (&unitsOnMap));
		addToMap(hero1, 0, 200);
		MyUnit.pushBack(hero1);
	}
	//我方英雄技能图标初始化
	InitSkillButton(HeroName);
	//敌方AI英雄初始化
	/*auto hero2 = HouYi::create();
	((HouYi*)hero2)->initwithRole(string("HrHouYi"), _tileMap, Vec2(x, y), (&unitsOnMap));
	hero2->setPosition(500, 500);

	addToMap(hero2, 0, 200);
	EnemeyUnit.pushBack(hero2);*/

	//我方塔敌方塔初始化
	auto MyTower1 = Tower::create();
	MyTower1->InitWithRole(string("Tb1"), _tileMap, (&unitsOnMap));
	addToMap(MyTower1, 0, 200); MyTower.pushBack(MyTower1); MyUnit.pushBack(MyTower1);
	auto MyTower2 = Tower::create();
	MyTower2->InitWithRole(string("Tb2"), _tileMap, (&unitsOnMap));
	addToMap(MyTower2, 0, 200); MyTower.pushBack(MyTower2); MyUnit.pushBack(MyTower2);
	auto MyTower3 = Tower::create();
	MyTower3->InitWithRole(string("Tb3"), _tileMap, (&unitsOnMap));
	addToMap(MyTower3, 0, 200); MyTower.pushBack(MyTower3);
	auto EnemeyTower1 = Tower::create();
	EnemeyTower1->InitWithRole(string("Tr1"), _tileMap, (&unitsOnMap));
	addToMap(EnemeyTower1, 0, 200); EnemeyTower.pushBack(EnemeyTower1); EnemeyUnit.pushBack(EnemeyTower1);
	auto EnemeyTower2 = Tower::create();
	EnemeyTower2->InitWithRole(string("Tr2"), _tileMap, (&unitsOnMap));
	addToMap(EnemeyTower2, 0, 200); EnemeyTower.pushBack(EnemeyTower2); EnemeyUnit.pushBack(EnemeyTower2);
	auto EnemeyTower3 = Tower::create();
	EnemeyTower3->InitWithRole(string("Tr3"), _tileMap,(&unitsOnMap));
	addToMap(EnemeyTower3, 0, 200);EnemeyUnit.pushBack(EnemeyTower3);

	//监听器初始化
	listener = MouseController::create();
	listener->initListener(hero1, getUnits());
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

	/////////////////////////


	/*
	auto hero2data = new(unitdata);
	hero2data->initial(string("HrHouYi"));
	auto act2 = Animate::create(AnimationCache::getInstance()->getAnimation("HrHouYiup_stand"));
	auto hero2 = HouYi::create(); hero2->initwithRole(hero2data, _tileMap);
	hero2->setPosition(Vec2(x + 600, y + 500));	// + 200, y + 200));
	addToMap(hero2, 2, 202);
	hero2->setScale(0.5);
	hero2->runAction(act2);*/
	/*auto fileUtiles = FileUtils::getInstance();
	auto fragmentGrayFullPath = fileUtiles->fullPathForFilename("gray.fsh");
	auto fragSource = fileUtiles->getStringFromFile(fragmentGrayFullPath);
	auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
	auto grayGLProgrameState = GLProgramState::getOrCreateWithGLProgram(glprogram);
	grayGLProgrameState->retain();

	auto fragmentColorFullPath = fileUtiles->fullPathForFilename("color.fsh");
	auto fragColorSource = fileUtiles->getStringFromFile(fragmentColorFullPath);
	auto Colorglprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
	auto ColorGLProgrameState = GLProgramState::getOrCreateWithGLProgram(glprogram);
	ColorGLProgrameState->retain();*/
	//Skill1Button->setGLProgramState(ColorGLProgrameState);


	
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

	
	this->schedule(schedule_selector(Game::mapupdate), 1.0f / 60);
	this->schedule(schedule_selector(Game::TimeRecorder), 1.0f);
	this->schedule(schedule_selector(Game::GoldRecorder), 1.0f / 60);
}
bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}
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
	this->addChild(Skill1Button); this->addChild(Skill2Button); this->addChild(Skill3Button); this->addChild(Skill4Button);
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
				if (ID[0] == 'T')
				{
					auto DIS = ((*it)->getPosition() - (*it2)->getPosition()).length();
					if (DIS < 200)
					{
						(*it)->ChangeCanAttackTower(true);
					}
					else
					{
						(*it)->ChangeCanAttackTower(false);
					}
					if ((*it)->GetCanAttackTower() == true)
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
					if ((*it)->GetCanAttackTower() == false&&(*it)->GetCanAttackHero() == true)
					{
						(*it)->changeAttackingTarget(*it2);
					}
				}
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
					if ((*it)->GetCanAttackTower() == false && (*it)->GetCanAttackHero() == false && (*it)->GetCanAttackSoldier() == true)
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
				if (ID[0] == 'T')
				{
					auto DIS = ((*it)->getPosition() - (*it2)->getPosition()).length();
					if (DIS < 200)
					{
						(*it)->ChangeCanAttackTower(true);
					}
					else
					{
						(*it)->ChangeCanAttackTower(false);
					}
					if ((*it)->GetCanAttackTower() == true)
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
					if ((*it)->GetCanAttackTower() == false && (*it)->GetCanAttackHero() == true)
					{
						(*it)->changeAttackingTarget(*it2);
					}
				}
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
					if ((*it)->GetCanAttackTower() == false && (*it)->GetCanAttackHero() == false && (*it)->GetCanAttackSoldier() == true)
					{
						(*it)->changeAttackingTarget(*it2);
					}
				}
				if ((*it)->GetCanAttackTower() == true && (*it)->GetCanAttackHero() == false && (*it)->GetCanAttackSoldier() == true)
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
	hero1->changeGold(1);
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

	if (Time == 2)
	{
		auto Br1_1 = Soldier::create();
		Br1_1->Soldierinit("Br1",1, _tileMap, (&unitsOnMap));
		addToMap(Br1_1, 0, 233); EnemeySoldier.pushBack(Br1_1); EnemeyUnit.pushBack(Br1_1);
		auto Br2_1 = Soldier::create();
		Br2_1->Soldierinit("Br2",1, _tileMap, (&unitsOnMap));
		addToMap(Br2_1, 0, 234); EnemeySoldier.pushBack(Br2_1); EnemeyUnit.pushBack(Br2_1);
		auto Br3_1 = Soldier::create();
		Br3_1->Soldierinit("Br3",1, _tileMap, (&unitsOnMap));
		addToMap(Br3_1, 0, 235); EnemeySoldier.pushBack(Br3_1); EnemeyUnit.pushBack(Br3_1);
		auto Br1_2 = Soldier::create();
		Br1_2->Soldierinit("Br1", 2, _tileMap, (&unitsOnMap));
		addToMap(Br1_2, 0, 236); EnemeySoldier.pushBack(Br1_2); EnemeyUnit.pushBack(Br1_2);
		auto Br2_2 = Soldier::create();
		Br2_2->Soldierinit("Br2", 2, _tileMap, (&unitsOnMap));
		addToMap(Br2_2, 0, 237); EnemeySoldier.pushBack(Br2_2); EnemeyUnit.pushBack(Br2_2);
		auto Br3_2 = Soldier::create();
		Br3_2->Soldierinit("Br3", 2, _tileMap, (&unitsOnMap));
		addToMap(Br3_2, 0, 238); EnemeySoldier.pushBack(Br3_2); EnemeyUnit.pushBack(Br3_2);
		auto Bb1_1 = Soldier::create();
		Bb1_1->Soldierinit("Bb1", 1, _tileMap, (&unitsOnMap));
		addToMap(Bb1_1, 0, 239); MySoldier.pushBack(Bb1_1); MyUnit.pushBack(Bb1_1);
		auto Bb2_1 = Soldier::create();
		Bb2_1->Soldierinit("Bb2", 1, _tileMap, (&unitsOnMap));
		addToMap(Bb2_1, 0, 240); MySoldier.pushBack(Bb2_1); MyUnit.pushBack(Bb2_1);
		auto Bb3_1 = Soldier::create();
		Bb3_1->Soldierinit("Bb3", 1, _tileMap, (&unitsOnMap));
		addToMap(Bb3_1, 0, 241); MySoldier.pushBack(Bb3_1); MyUnit.pushBack(Bb3_1);
		auto Bb1_2 = Soldier::create();
		Bb1_2->Soldierinit("Bb1", 2, _tileMap, (&unitsOnMap));
		addToMap(Bb1_2, 0, 239); MySoldier.pushBack(Bb1_2); MyUnit.pushBack(Bb1_2);
		auto Bb2_2 = Soldier::create();
		Bb2_2->Soldierinit("Bb2", 2, _tileMap, (&unitsOnMap));
		addToMap(Bb2_2, 0, 240); MySoldier.pushBack(Bb2_2); MyUnit.pushBack(Bb2_2);
		auto Bb3_2 = Soldier::create();
		Bb3_2->Soldierinit("Bb3", 2, _tileMap, (&unitsOnMap));
		addToMap(Bb3_2, 0, 241); MySoldier.pushBack(Bb3_2); MyUnit.pushBack(Bb3_2);
		//Br1->moveDirectionByKey(Br1->getDir(Br1->getPosition(), Vec2(1000, 1000)), Vec2(1000, 1000));

		//Bb1->moveDirectionByKey(Bb1->getDir(Bb1->getPosition(), Vec2(0, 0)), Vec2(0, 0));
		//Bb2->moveDirectionByKey(Bb2->getDir(Bb2->getPosition(), Vec2(0, 0)), Vec2(0, 0));
		//Bb3->moveDirectionByKey(Bb3->getDir(Bb3->getPosition(), Vec2(0, 0)), Vec2(0, 0));
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
	if (!MyTower.empty())
	{
		for (auto it = EnemeySoldier.begin(); it != EnemeySoldier.end(); it++)
		{
			(*it)->AttackingJudgeAI();
		}
	}
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
		CC_CALLBACK_1(Game::buyHatCallBack, this)
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
	hero1->addEquipment("Shoe"); 
}
void Game::buyHatCallBack(cocos2d::Ref* pSender) { 
	if (!IS_SHOP_OPEN) { return; }
	hero1->addEquipment("Helmet");
	hero1->getHp()->changeCur(600000);
}
void Game::buySwordCallBack(cocos2d::Ref* pSender) {
	if (!IS_SHOP_OPEN) { return; }
	hero1->addEquipment("Sword");
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

