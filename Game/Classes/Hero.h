#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;

class Hero : public cocos2d::Sprite
{
public:
	Game* game;
	Sprite* _player;
	enum class Direction :int
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		NONE
	};
	static Hero * create(const std::string& id, int role);//返回调用此类的指针
	bool init();
	Sprite* initWithRole(Vec2 Postion);//对某个特定角色进行初始化？

	int getSpeed();//获取英雄速度
	void setSpeed(int speed);//设置英雄速度
	
	int getHP();//获取英雄当前血量
	void setHP(int HP);//设置英雄血量

	int getATK();//获取英雄攻击力
	void setATK(int ATK);//设置英雄攻击力

	int getDEF();//获取英雄防御力
	void setDEF(int DEF);//设置英雄防御力

	void HeroDead();//设置英雄死亡
	bool ifAlive();//判断英雄是否存活

	
	void moveDirectionByKey(Direction direction,float x, float y, Sprite* Hero);//根据方向调整动画
	Hero::Direction getDirection();



	//void setDirectionByKey(Direction direction);
	//void updateDirection();
	//void setDirection(Direction direction);
	CREATE_FUNC(Hero);


private:
	Direction direction;
	std::string roleName;
	int Speed;
	int HP;
	int ATK;
	int DEF;
};