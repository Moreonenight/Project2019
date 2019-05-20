#ifndef __Game_SCENE_H__
#define __Game_SCENE_H__

#include "cocos2d.h"

class Game : public cocos2d::Layer
{
private:
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::Sprite* _player;
	cocos2d::TMXLayer* _collidable;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	cocos2d::Vec2 Hero_init_Postion();

	//check
	void setPlayerPosition(cocos2d::Vec2 position);

	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);

	// a selector callback
	void menuItem1Callback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(Game);
};

#endif
