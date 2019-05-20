#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "/button/CloseNormal.png",
                                           "/button/CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(24);
    
	auto bg = Sprite::create("/bg/bg.png");
	bg->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2
	));
	this->addChild(bg);
	
	//开始按钮
	auto StartButton = MenuItemImage::create(
		"/button/start.png",
		"/button/start.png",
		CC_CALLBACK_1(HelloWorld::menuStartCallback,this)
	);
	StartButton->setPosition(Vec2(
		origin.x+visibleSize.width/2,
		origin.y+visibleSize.height/3* 2
	));


	//Setting 按钮
	auto SettingButton = MenuItemFont::create(
		"Setting",
		CC_CALLBACK_1(HelloWorld::menuSettingCallback, this)
	);
	SettingButton->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2
	));
	//两个按钮合并成一个菜单
	auto mn = Menu::create(
		StartButton,
		SettingButton,
		NULL
	);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn,2);
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //关闭游戏场景并退出应用
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
//回调函数
void HelloWorld::menuSettingCallback(Ref *pSender)
{
	auto SettingScene = Setting::createScene();
	auto ReSettingScene = TransitionFadeTR::create(1.0f, SettingScene);//设置页面转换效果
	Director::getInstance()->pushScene(ReSettingScene);
}

void HelloWorld::menuStartCallback(cocos2d::Ref* pSender) {
	auto GameScence = Game::createScene();
	Director::getInstance()->pushScene(GameScence);
}
