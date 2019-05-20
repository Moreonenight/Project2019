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
	static Hero * create(const std::string& id, int role);//���ص��ô����ָ��
	bool init();
	Sprite* initWithRole(Vec2 Postion);//��ĳ���ض���ɫ���г�ʼ����

	int getSpeed();//��ȡӢ���ٶ�
	void setSpeed(int speed);//����Ӣ���ٶ�
	
	int getHP();//��ȡӢ�۵�ǰѪ��
	void setHP(int HP);//����Ӣ��Ѫ��

	int getATK();//��ȡӢ�۹�����
	void setATK(int ATK);//����Ӣ�۹�����

	int getDEF();//��ȡӢ�۷�����
	void setDEF(int DEF);//����Ӣ�۷�����

	void HeroDead();//����Ӣ������
	bool ifAlive();//�ж�Ӣ���Ƿ���

	
	void moveDirectionByKey(Direction direction,float x, float y, Sprite* Hero);//���ݷ����������
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