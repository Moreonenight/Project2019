#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "cocos2d.h"

USING_NS_CC;

struct Command
{
	Vec2 CurrentLocation;
	Vec2 BeforePos;
	INT32 SkillNumber;
	INT32 SkillUpNumber;
	bool now_attack;
	bool now_move;
	INT32 buyNumber;
	INT32 sellNumber;
	bool now_back;
};

#endif 