#ifndef _SHOOT_H_
#define _SHOOT_H_


#include "cocos2d.h"

USING_NS_CC;

class shoot :public Node{
public:
	bool init();
	CREATE_FUNC(shoot);

	int _trigger;			//������̨�ƶ���־
	int bullet_shoot_gap;	//�ӵ�����ļ��

	void move_trigger();		//������̨�ƶ�
	void reset();

	Vec2 get_shoot_pos();


	Vec2 player_pos;			//��Ҫ��MainLayer����
	Vec2 init_pos;				//����Ļ���λ��
	Vec2 shoot_base_pos;		//����Ļ���λ��

	float distance_from_trigger;	//�Ӵ������ƶ��ľ��롣ÿ�δ�����Ҫ����
	float shoot_length;		//�ڹܳ���
	float offset;		//���������Ļ��ȵ���

	float rad;			//��ת�Ļ���

	DrawNode *node1;	//����
	Node* node2;		//�ڹ�

};

#endif