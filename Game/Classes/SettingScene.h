#ifndef __Setting_SCENE_H__
#define __Setting_SCENE_H__

#include "cocos2d.h"

#include "cocos2d.h"
class Setting: public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	// a selector callback
	void menuItem1Callback(cocos2d::Ref* pSender);
	void menuSoundToggleCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(Setting);
};

#endif
