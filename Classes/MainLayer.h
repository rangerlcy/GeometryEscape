#ifndef __MainLayer__
#define __MainLayer__


#include "cocos2d.h"
#include <vector>

#define PLAYER 100

#include "block.h"
#include "ray.h"
#include "shoot.h"
#include "publicVar.h"

using namespace cocos2d;

class MainLayer:public Layer
{
public:
	virtual bool init();
	virtual void onEnter();
	virtual void update(float delta);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	bool onContactBegin(PhysicsContact& contact);

	void run();		//��Ϸ��ʼ

	void setGravityVector(Vec2 pos);
	void initBlock();					//�ϰ����ʼ��
	void runBlock(float dt);			//�ϰ�����ӵ���ʾ�ڵ��ϲ�ִ�ж���
	void initRay();
	void runRay(float dt);
	void initShoot();
	void runShoot(float dt);

	void deleteBullet(Node *bullet);
	CREATE_FUNC(MainLayer);

	void globe_manager();
	void timeCount(float dt);

	static std::vector<block*> block_array;
	static std::vector<block*> double_block_array;
	static std::vector<block*> triple_block_array;
	static std::vector<ray*> ray_array;
	static std::vector<shoot*> shoot_array;

private:
	Node *player;
	std::thread *game_manager;

	Label *time;
	int mins;
	int sec;
	int msec;

	int level;			//�Ѷȵȼ�ÿ��һ��ʱ������
}; 

#endif 