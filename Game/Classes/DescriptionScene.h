#ifndef __DESCRIPTION_SCENE_H__
#define __DESCRIPTION_SCENE_H__

#include "cocos2d.h"

class DescriptionScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	// a selector callback
	void menuItem1Callback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(DescriptionScene);
};

#endif
