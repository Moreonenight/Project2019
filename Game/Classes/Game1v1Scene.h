#ifndef __GAME1V1_SCENE_H__
#define __GAME1V1_SCENE_H__

#include "cocos2d.h"

class Game1v1 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	void menuItem1Callback(cocos2d::Ref* pSender);
	virtual bool init();
	CREATE_FUNC(Game1v1);
};
#endif
