#include"DajiSkillScene.h"
USING_NS_CC;

Scene* DajiSkillScene::createScene()
{
	return DajiSkillScene::create();
}

bool DajiSkillScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();




	//background
	auto bg = Sprite::create("/bg/DajiSkillScene.jpg");
	bg->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2
	));
	addChild(bg, 0);

	//标签
	auto heroTitle = Label::create(DajiSkillScene::FontToUTF8("妲己技能介绍"), "fonts/Hanzi.ttf", 50);
	heroTitle->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - heroTitle->getContentSize().height / 2
	));
	heroTitle->enableGlow(Color4B::BLACK);
	addChild(heroTitle, 1);
	//Q技能
	auto skill_Q = Sprite::create("skills/HbDaJi_Sk1.png");
	skill_Q->setPosition(Vec2(
		origin.x + visibleSize.width / 2 - 250,
		origin.y + visibleSize.height / 2 + 85
	));
	auto sk1Line1 = Label::create(DajiSkillScene::FontToUTF8("Q技能"), "fonts/Hanzi.ttf", 30);
	auto sk1Line2 = Label::create(DajiSkillScene::FontToUTF8("点击敌方单位"), "fonts/Hanzi.ttf", 30);
	auto sk1Line3 = Label::create(DajiSkillScene::FontToUTF8("发射能量球造成伤害"), "fonts/Hanzi.ttf", 30);
	sk1Line1->setPosition(Vec2(40, -30));
	sk1Line2->setPosition(Vec2(40, -60));
	sk1Line3->setPosition(Vec2(40, -90));
	sk1Line1->enableGlow(Color4B::BLACK);
	sk1Line2->enableGlow(Color4B::BLACK);
	sk1Line3->enableGlow(Color4B::BLACK);
	skill_Q->addChild(sk1Line1);
	skill_Q->addChild(sk1Line2);
	skill_Q->addChild(sk1Line3);
	addChild(skill_Q, 1);
	//W技能
	auto skill_W = Sprite::create("skills/HbDaji_Sk2.png");
	skill_W->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + 85
	));
	auto sk2Line1 = Label::create(DajiSkillScene::FontToUTF8("W技能"), "fonts/Hanzi.ttf", 30);
	auto sk2Line2 = Label::create(DajiSkillScene::FontToUTF8("按下后点击地图"), "fonts/Hanzi.ttf", 30);
	auto sk2Line3 = Label::create(DajiSkillScene::FontToUTF8("闪现至点击地点"), "fonts/Hanzi.ttf", 30);
	sk2Line1->setPosition(Vec2(40, -30));
	sk2Line2->setPosition(Vec2(40, -60));
	sk2Line3->setPosition(Vec2(40, -90));
	sk2Line1->enableGlow(Color4B::BLACK);
	sk2Line2->enableGlow(Color4B::BLACK);
	sk2Line3->enableGlow(Color4B::BLACK);
	skill_W->addChild(sk2Line1);
	skill_W->addChild(sk2Line2);
	skill_W->addChild(sk2Line3);
	addChild(skill_W, 1);

	//E技能
	auto skill_E = Sprite::create("skills/HbDaJi_Sk3.png");
	skill_E->setPosition(Vec2(
		origin.x + visibleSize.width / 2 + 250,
		origin.y + visibleSize.height / 2 + 85
	));
	auto sk3Line1 = Label::create(DajiSkillScene::FontToUTF8("E技能"), "fonts/Hanzi.ttf", 30);
	auto sk3Line2 = Label::create(DajiSkillScene::FontToUTF8("为自己和附近友方"), "fonts/Hanzi.ttf", 30);
	auto sk3Line3 = Label::create(DajiSkillScene::FontToUTF8("进行不断AOE治疗"), "fonts/Hanzi.ttf", 30);
	auto sk3Line4 = Label::create(DajiSkillScene::FontToUTF8("过程持续两秒"), "fonts/Hanzi.ttf", 30);
	sk3Line1->setPosition(Vec2(40, -30));
	sk3Line2->setPosition(Vec2(40, -60));
	sk3Line3->setPosition(Vec2(40, -90));
	sk3Line4->setPosition(Vec2(40, -120));
	sk3Line1->enableGlow(Color4B::BLACK);
	sk3Line2->enableGlow(Color4B::BLACK);
	sk3Line3->enableGlow(Color4B::BLACK);
	sk3Line4->enableGlow(Color4B::BLACK);
	skill_E->addChild(sk3Line1);
	skill_E->addChild(sk3Line2);
	skill_E->addChild(sk3Line3);
	skill_E->addChild(sk3Line4);
	addChild(skill_E, 1);


	//return button
	auto closeItem = MenuItemImage::create(
		"/button/closetoupper.png",
		"/button/closetoupper_selected.png",
		CC_CALLBACK_1(DajiSkillScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(
		origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2
	));
	auto mn = Menu::create(
		closeItem,
		NULL
	);
	mn->setPosition(Vec2::ZERO);
	addChild(mn, 2);

	return true;
}

char *DajiSkillScene::FontToUTF8(const char* font)
{
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

void DajiSkillScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}