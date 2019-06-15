#ifndef __CHOOSEHERO_SCENE_H__
#define __CHOOSEHERO_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "SocketClient.h"
#include "HouyiSkillScene.h"
#include "YaseSkillScene.h"
#include "DajiSkillScene.h"
class ChooseHeroScene : public cocos2d::Scene
{
private:
	Game* m_game;
public:
	static ChooseHeroScene* ChooseHeroScene::create(INT32 playerNumber, SocketClient* socket_client, INT32 mode);
	void menuItem1Callback(cocos2d::Ref* pSender);
	void YaseEnterCallback(cocos2d::Ref* pSender);
	void HouYiEnterCallback(cocos2d::Ref* pSender);
	void DajiEnterCallback(cocos2d::Ref* pSender);
	void HouyiSkillCallback(cocos2d::Ref* pSender);
	void YaseSkillCallback(cocos2d::Ref* pSender);
	void DajiSkillCallback(cocos2d::Ref* pSender);
	virtual bool init(INT32 playerNumber, SocketClient* socket_client, INT32 mode);
	char*FontToUTF8(const char* font);
	INT32 _playerNumber;
	SocketClient* _socket_client;
	INT32 _mode;
	//	CREATE_FUNC(ChooseHeroScene);
};
#endif