#include "unitdata.h"
#include <cstdio>
#include <string.h>

bool unitdata::initial(string &datapath)
{
	//unitdata* _data = new(unitdata);
	int index = 0, curDir = 0, order = 0;
	string currentPath,buf;
	FILE *data;
	unitid = datapath;
	for (order = 0; order < NUM_OF_KINDS; order++) {
		currentPath = datapath + "/" + kind[order] + ".txt";
		data = fopen(currentPath.c_str(), "r");
		if (data == NULL) {
			//cocos2d::CCLog((kind[order] + ".txtFailed").c_str());
			continue;
		}
		fgets((char*)buf.c_str(), 100, data);
		auto SFC = cocos2d::SpriteFrameCache::getInstance();
		SFC->addSpriteFramesWithFile((const string)buf);
		buf.erase();
		for (curDir = 0; curDir < 4; curDir++) {
			for (index = 0; index < numOfFrames[order]; index++) {
				fgets((char*)buf.c_str(), 100, data);
				if (numOfFrames[order] == 1) continue;
				else (&animations[order][curDir])->addSpriteFrame(SFC->getSpriteFrameByName(buf.c_str()));
				buf.erase();
				}
			cocos2d::AnimationCache::getInstance()->addAnimation(&animations[order][curDir], unitid + dir[curDir] + kind[order]);
			}
		fclose(data);
	}
	currentPath = datapath + "/integer.txt";
	data = fopen(currentPath.c_str(), "r");
	while (fgets((char *)buf.c_str(), 100, data) != NULL) {
		m2[buf] = atoi(fgets((char *)buf.c_str(), 100, data));
	}
	maxHp = m2["maxHp"];
	maxMana = m2["maxMana"]; 
	damage = m2["damage"]; 
	ASPD = m2["ASPD"];/* epl = m2["epl"];*/ 
	initLvl = m2["initLvl"];
	initGold = m2["initGold"];
	attackRange = m2["attackRange"]; 
	ammoSpeed = m2["ammoSpeed"];
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


