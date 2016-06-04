#ifndef _SHOOT_H_
#define _SHOOT_H_


#include "cocos2d.h"

USING_NS_CC;

class shoot :public Node{
public:
	bool init();
	CREATE_FUNC(shoot);

	int _trigger;			//触发炮台移动标志
	int bullet_shoot_gap;	//子弹发射的间隔

	void move_trigger();		//触发炮台移动
	void reset();

	Vec2 get_shoot_pos();


	Vec2 player_pos;			//需要从MainLayer传入
	Vec2 init_pos;				//最初的基座位置
	Vec2 shoot_base_pos;		//射击的基座位置

	float distance_from_trigger;	//从触发起，移动的距离。每次触发都要归零
	float shoot_length;		//炮管长度
	float offset;		//最初超过屏幕宽度的量

	float rad;			//旋转的弧度

	DrawNode *node1;	//基座
	Node* node2;		//炮管

};

#endif