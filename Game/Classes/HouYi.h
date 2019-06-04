#pragma once
#include "unit.h"

class HouYi {
private:
	unit* houyi;
	unitdata* houyiData;
	int level;
	int skill_1Level;
	int skill_2Level;
	int skill_3Level;
	int sk1Damage[6] = { 200,240,280,320,360,400 };
	int sk2Damage[6] = { 300,350,400,450,500,550 };
	float sk2Cd[6] = { 8.0,7.4,6.8,6.2,5.6,5 };
	int sk3Damage[3] = { 700,875,1050 };
	float sk3Cd[3] = { 45,40,35 };
public:
	void initial();
	unit* getUnit() { return houyi; }
	void useskill_1();
	void sk1End(float dt);
	void skill_1_cd(float dt);
	void useSkill_2(Vec2 pos);
	void useAlti();
};