#include"YaseSkillScene.h"
USING_NS_CC;

Scene* YaseSkillScene::createScene()
{
	return YaseSkillScene::create();
}

bool YaseSkillScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();




	//background
	auto bg = Sprite::create("/bg/YaseSkillScene.jpg");
	bg->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2
	));
	addChild(bg, 0);

	//��ǩ
	auto heroTitle = Label::create(YaseSkillScene::FontToUTF8("��ɪ���ܽ���"), "fonts/Hanzi.ttf", 50);
	heroTitle->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - heroTitle->getContentSize().height / 2
	));
	addChild(heroTitle, 1);
	//Q����
	auto skill_Q = Sprite::create("skills/HbYaSe_Sk1.png");
	skill_Q->setPosition(Vec2(
		origin.x + visibleSize.width / 2 - 250,
		origin.y + visibleSize.height / 2 + 85
	));
	auto sk1Line1 = Label::create(YaseSkillScene::FontToUTF8("Q����"), "fonts/Hanzi.ttf", 30);
	auto sk1Line2 = Label::create(YaseSkillScene::FontToUTF8("����з���λ"), "fonts/Hanzi.ttf", 30);
	auto sk1Line3 = Label::create(YaseSkillScene::FontToUTF8("���п���ײ��"), "fonts/Hanzi.ttf", 30);
	auto sk1Line4 = Label::create(YaseSkillScene::FontToUTF8("��ɴ����˺�"), "fonts/Hanzi.ttf", 30);
	sk1Line1->setPosition(Vec2(40, -30));
	sk1Line2->setPosition(Vec2(40, -60));
	sk1Line3->setPosition(Vec2(40, -90));
	sk1Line4->setPosition(Vec2(40, -120));
	skill_Q->addChild(sk1Line1);
	skill_Q->addChild(sk1Line2);
	skill_Q->addChild(sk1Line3);
	skill_Q->addChild(sk1Line4);
	addChild(skill_Q, 1);
	//W����
	auto skill_W = Sprite::create("skills/HbYaSe_Sk2.png");
	skill_W->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + 85
	));
	auto sk2Line1 = Label::create(YaseSkillScene::FontToUTF8("W����"), "fonts/Hanzi.ttf", 30);
	auto sk2Line2 = Label::create(YaseSkillScene::FontToUTF8("���º�����ͼ"), "fonts/Hanzi.ttf", 30);
	auto sk2Line3 = Label::create(YaseSkillScene::FontToUTF8("����������ص�"), "fonts/Hanzi.ttf", 30);
	sk2Line1->setPosition(Vec2(40, -30));
	sk2Line2->setPosition(Vec2(40, -60));
	sk2Line3->setPosition(Vec2(40, -90));
	skill_W->addChild(sk2Line1);
	skill_W->addChild(sk2Line2);
	skill_W->addChild(sk2Line3);
	addChild(skill_W, 1);

	//E����
	auto skill_E = Sprite::create("skills/HbYaSe_Sk3.png");
	skill_E->setPosition(Vec2(
		origin.x + visibleSize.width / 2 + 250,
		origin.y + visibleSize.height / 2 + 85
	));
	auto sk3Line1 = Label::create(YaseSkillScene::FontToUTF8("E����"), "fonts/Hanzi.ttf", 30);
	auto sk3Line2 = Label::create(YaseSkillScene::FontToUTF8("��ɨһ��"), "fonts/Hanzi.ttf", 30);
	auto sk3Line3 = Label::create(YaseSkillScene::FontToUTF8("��һ����Χ�з���λ"), "fonts/Hanzi.ttf", 30);
	auto sk3Line4 = Label::create(YaseSkillScene::FontToUTF8("�����������˺�"), "fonts/Hanzi.ttf", 30);
	sk3Line1->setPosition(Vec2(40, -30));
	sk3Line2->setPosition(Vec2(40, -60));
	sk3Line3->setPosition(Vec2(40, -90));
	sk3Line4->setPosition(Vec2(40, -120));
	skill_E->addChild(sk3Line1);
	skill_E->addChild(sk3Line2);
	skill_E->addChild(sk3Line3);
	skill_E->addChild(sk3Line4);
	addChild(skill_E, 1);


	//return button
	auto closeItem = MenuItemImage::create(
		"/button/closetoupper.png",
		"/button/closetoupper_selected.png",
		CC_CALLBACK_1(YaseSkillScene::menuCloseCallback, this));

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

char *YaseSkillScene::FontToUTF8(const char* font)
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

void YaseSkillScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}