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

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.


    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "/button/CloseNormal.png",
                                           "/button/CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    // add a label shows "Hello World"
    // create and initialize a label


	//background
	auto bg = Sprite::create("/bg/bg.png");
	bg->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2
	));
	this->addChild(bg);
	

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(24);



	//create a start-up button
	auto StartButton = MenuItemImage::create(
		"/button/start.png",
		"/button/start.png",
		CC_CALLBACK_1(HelloWorld::menuStartCallback,this)
	);
	StartButton->setPosition(Vec2(
		origin.x+visibleSize.width/2,
		origin.y+visibleSize.height/3* 2
	));


	//create a Setting botton
	auto SettingButton = MenuItemFont::create(
		"Setting",
		CC_CALLBACK_1(HelloWorld::menuSettingCallback, this)
	);
	SettingButton->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2
	));
	//create a menu
	auto mn = Menu::create(
		StartButton,
		SettingButton,
		NULL
	);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn,2);

    /*auto label = Label::createWithTTF("nmd","fonts/Marker Felt.ttf", 36);
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2));

    // add the label as a child to this layer
    this->addChild(label, 1);
	*/
    // add "HelloWorld" splash screen"


	//music
	/*CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("/music/roomScene.mp3",true);
	*/

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::menuSettingCallback(Ref *pSender)
{
	auto sc =Setting::createScene();
	auto reScene = TransitionFadeTR::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}

void HelloWorld::menuStartCallback(cocos2d::Ref* pSender) {
	auto sc = Game::createScene();
	Director::getInstance()->pushScene(sc);
}
