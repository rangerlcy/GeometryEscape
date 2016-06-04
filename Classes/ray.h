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

	int category;		//光线类别，只用到一组起点终点，还是用到两组起点终点
	DrawNode* _node1;
	DrawNode* _node2;
	int _trigger;
	float distance_from_trigger;		//从触发起，移动的距离。每次触发都要归零
	//第一组起点终点
	Vec2 from1_1;
	Vec2 from1_2;
	Vec2 end1_1;
	Vec2 end1_2;
	//第二组起点终点
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