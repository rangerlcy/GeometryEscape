#ifndef _BLOCK_H_
#define _BLOCK_H_


#include "cocos2d.h"
#include "publicVar.h"

USING_NS_CC;

#define BLOCK_MOVE_RIGHT_ACTION 777

//�ϰ������
class block :public Node{
public:
	/*block();
	~block();*/
	virtual bool init();
	CREATE_FUNC(block);

	void restart();
	void come();		//�ϰ����init_pos��ʼ����
	void accelerateMoveRight();		//���´���moveRightAndDestroy��ʹ֮����

	PhysicsBody* body;
	Node* node;
	ActionInterval *act;
	ActionInterval *moveRightAndDestroy;
	Vec2 init_pos;
};

//�ɵ�ʹ�õ��ϰ�
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


//��˫ʹ�õ��ϰ�
//ƽ�������
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


//ƽ��������
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


//����ʹ�õ��ϰ�
//������ת��
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