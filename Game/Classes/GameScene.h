#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__

#include "cocos2d.h"

#include "cocos2d.h"
class Game : public cocos2d::Layer
{
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::Sprite* _player;
	cocos2d::TMXLayer* _collidable;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	//check
	void setPlayerPosition(cocos2d::Vec2 position);

	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);

	// a selector callback
	void menuItem1Callback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(Game);
};

#endif
