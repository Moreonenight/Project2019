#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
	bool _VictoryorDefeat;
public:
	static cocos2d::Scene* createScene(bool VictoryorDefeat);
	bool initwithBool(bool VictoryorDefeat);
	virtual bool init();
	// a selector callback
	void menuItem1Callback(cocos2d::Ref* pSender);
	void menuStartCallback(cocos2d::Ref* pSender);
	void Start1v1Callback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(GameOverScene);
};

#endif