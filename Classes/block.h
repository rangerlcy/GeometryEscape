#ifndef _BLOCK_H_
#define _BLOCK_H_


#include "cocos2d.h"
#include "publicVar.h"

USING_NS_CC;

#define BLOCK_MOVE_RIGHT_ACTION 777

//障碍物基类
class block :public Node{
public:
	/*block();
	~block();*/
	virtual bool init();
	CREATE_FUNC(block);

	void restart();
	void come();		//障碍物从init_pos开始出现
	void accelerateMoveRight();		//重新创建moveRightAndDestroy，使之加速

	PhysicsBody* body;
	Node* node;
	ActionInterval *act;
	ActionInterval *moveRightAndDestroy;
	Vec2 init_pos;
};

//成单使用的障碍
class block1 :public block{
public:
	virtual bool init();
	CREATE_FUNC(block1);
};

class block2 :public block{
public:
	virtual bool init();
	CREATE_FUNC(block2);
};

class block3 :public block{
public:
	virtual bool init();
	CREATE_FUNC(block3);
};


//成双使用的障碍
//平行两横杆
class double_block1_1 :public block{
public:
	virtual bool init();
	CREATE_FUNC(double_block1_1);
};

class double_block1_2 :public block{
public:
	virtual bool init();
	CREATE_FUNC(double_block1_2);
};


//平行两竖杆
class double_block2_1 :public block{
public:
	virtual bool init();
	CREATE_FUNC(double_block2_1);
};

class double_block2_2 :public block{
public:
	virtual bool init();
	CREATE_FUNC(double_block2_2);
};


//成三使用的障碍
//三个旋转杆
class triple_block1_1 :public block{
public:
	virtual bool init();
	CREATE_FUNC(triple_block1_1);
};

class triple_block1_2 :public block{
public:
	virtual bool init();
	CREATE_FUNC(triple_block1_2);
};

class triple_block1_3 :public block{
public:
	virtual bool init();
	CREATE_FUNC(triple_block1_3);
};


#endif