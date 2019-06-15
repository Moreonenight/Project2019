#pragma once

#include "cocos2d.h"

class YaseSkillScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	char*FontToUTF8(const char* font);
	// implement the "static create()" method manually
	CREATE_FUNC(YaseSkillScene);
};