#ifndef __GAMEMODE_SCENE_H__
#define __GAMEMODE_SCENE_H__

#include "cocos2d.h"

class GameMode : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	// a selector callback
	void menuItem1Callback(cocos2d::Ref* pSender);
	void menuStartCallback(cocos2d::Ref* pSender);
	void Start1v1Callback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(GameMode);
};

#endif
