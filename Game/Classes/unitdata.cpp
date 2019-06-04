#include "unitdata.h"
#include <cstdio>
#include <string.h>



bool unitdata::initial(string &datapath)
{
	//unitdata* _data = new(unitdata);
	int index = 0, curDir = 0, order = 0;
	string currentPath,buf;
	char b[50] = { '\0' };
	FILE *data;
	unitid = datapath;
	for (order = 0; order < NUM_OF_KINDS; order++) {
		currentPath = "../Resources/" + datapath + "/" + kind[order] + ".txt";
		data = fopen(currentPath.c_str(), "r");
		if (data == NULL) {
			//cocos2d::CCLog((kind[order] + ".txtFailed").c_str());
			continue;
		}
		fgets(b, 100, data);
		buf = b;
		buf[buf.size()-1] = '\0';
		auto SFC = cocos2d::SpriteFrameCache::getInstance();
		SFC->addSpriteFramesWithFile((const string)buf);
		buf.erase(); memset(b, '\0', 50);
		for (curDir = 0; curDir < 4; curDir++) {				
			auto curani = cocos2d::Animation::create();
			for (index = 0; index < numOfFrames[order]; index++) {
				fgets(b, 100, data);
				buf = b;
				buf[buf.size() - 1] = '\0';
				curani->addSpriteFrame(SFC->getSpriteFrameByName(buf.c_str()));
				buf.erase(); memset(b, '\0', 50);
			}
			curani->setLoops(-1); curani->setDelayPerUnit(0.1f); 
			cocos2d::AnimationCache::getInstance()->addAnimation(curani, unitid + dir[curDir] + kind[order]);
		}
		fclose(data);
	}
	currentPath = datapath + "/integer.txt";
	data = fopen(currentPath.c_str(), "r");
	if (data == NULL) return false;
	index = 0;
	while (fgets(b, 100, data) != NULL) {
		b[strlen(b) - 1] = '\0';
		if (index){
			m2[buf] = atoi(b); index--; buf.erase(); memset(b, '\0', 50);
		}
		else {
			buf = b; index++; memset(b,'\0',50);
		}
	}
	maxHp = m2["maxHp"];
	maxMana = m2["maxMana"]; 
	damage = m2["damage"]; 
	ASPD = m2["ASPD"];/* epl = m2["epl"];*/ 
	//initLvl = m2["initLvl"];
	initGold = m2["initGold"];
	attackRange = m2["attackRange"]; 
	ammoSpeed = m2["ammoSpeed"];
	moveSpeed = m2["moveSpeed"];
	defenceOfPhysical = m2["defenceOfPhysical"];
	defenceOfMagic = m2["defenceOfMagic"];
	recoverOfHp = m2["recoverOfHp"];
	recoverOfMana = m2["recoverOfMana"];
	fclose(data);
	/*currentPath = datapath + "/float.txt";
	data = fopen(currentPath.c_str(), "r");
	while (fgets((char *)buf.c_str(), 100, data) != NULL) {
		m1[buf] = atof(fgets((char *)buf.c_str(), 100, data));
	}
	velocity = cocos2d::Vec2(m1["velocityX"], m1["velocityY"]);
	position = cocos2d::Vec2(m1["positionX"], m1["positionY"]);
	dpm = cocos2d::Vec2(m1["dpmP"], m1["dpmM"]);
	fclose(data);*/
	return true;
}

unitdata::~unitdata()
{
	delete(this);
}


