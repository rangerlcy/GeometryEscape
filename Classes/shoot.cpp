#include "shoot.h"

bool shoot::init(){
	if (!Node::init()){
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();
	_trigger = 0;
	distance_from_trigger = 0;
	bullet_shoot_gap = 80;
	rad = 0.0;			//��ת�Ļ���
	offset = 100;
	shoot_length = 28;
	init_pos = Vec2(size.width +offset, 0);
	shoot_base_pos = Vec2(size.width +offset, 0);		//�����λ��

	node1 = nullptr;

	auto body2 = PhysicsBody::createEdgeSegment(Vec2::ZERO, Vec2::ZERO + Vec2(shoot_length, 0), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	body2->setCategoryBitmask(0x0003);
	body2->setCollisionBitmask(0x0004);
	body2->setContactTestBitmask(0x0001);
	node2 = Node::create();
	node2->setAnchorPoint(Vec2(0, 0.5));
	node2->setPhysicsBody(body2);
	node2->setPosition(init_pos);
	node2->setRotation(0);

	return true;
}


Vec2 shoot::get_shoot_pos(){
	return shoot_base_pos + Vec2((shoot_length + 10)*cosf(rad), (shoot_length + 10)*sinf(rad));		//sinf cosf����ȥ���ǻ���
}

void shoot::move_trigger(){
	_trigger = 1;
	distance_from_trigger = 0;
}

void shoot::reset(){
	Size size = Director::getInstance()->getVisibleSize();

	_trigger = 0;
	distance_from_trigger = 0;
	//λ�ø�λ
	node1->setPosition(init_pos);
	node2->setPosition(init_pos); 
}
