#ifndef _RAY_H_
#define _RAY_H_


#include "cocos2d.h"

USING_NS_CC;

class ray :public Node{
public:
	virtual bool init() override;
	CREATE_FUNC(ray);

	virtual void ray_trigger();
	virtual void ray_reset();
	virtual bool anyRay(PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data);

	int category;		//�������ֻ�õ�һ������յ㣬�����õ���������յ�
	DrawNode* _node1;
	DrawNode* _node2;
	int _trigger;
	float distance_from_trigger;		//�Ӵ������ƶ��ľ��롣ÿ�δ�����Ҫ����
	//��һ������յ�
	Vec2 from1_1;
	Vec2 from1_2;
	Vec2 end1_1;
	Vec2 end1_2;
	//�ڶ�������յ�
	Vec2 from2_1;
	Vec2 from2_2;
	Vec2 end2_1;
	Vec2 end2_2;
};


class ray1:public ray
{
public:

	virtual bool init() override;
	CREATE_FUNC(ray1);

};


class ray2:public ray
{
public:
	virtual bool init() override;
	CREATE_FUNC(ray2);
};



#endif