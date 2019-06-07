#ifndef __CHOOSEHERO_SCENE_H__
#define __CHOOSEHERO_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
class ChooseHeroScene : public cocos2d::Scene
{
private:
	Game* m_game;
public:
	static cocos2d::Scene* createScene();
	void menuItem1Callback(cocos2d::Ref* pSender);
	void YaseEnterCallback(cocos2d::Ref* pSender);
	void HouYiEnterCallback(cocos2d::Ref* pSender);
	void DajiEnterCallback(cocos2d::Ref* pSender);
	virtual bool init();
	char*FontToUTF8(const char* font);
	CREATE_FUNC(ChooseHeroScene);
};
#endif
