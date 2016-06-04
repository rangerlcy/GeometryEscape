#include "block.h"

USING_NS_CC;
//class  block...block1...block2...block3...
bool block::init(){
	if (!Node::init()){
		return false;
	}
	return true;
}

//block类里的node进行重新设置成初始状态，但不向右移动
void block::restart(){
	Size size = Director::getInstance()->getVisibleSize();
	//action = action->clone();
	//moveRightAndDestroy = moveRightAndDestroy->clone();
	node->stopAllActions();
	node->setPosition(init_pos);
}

void block::come(){
	Size size = Director::getInstance()->getVisibleSize();
	node->runAction(act);
	node->runAction(moveRightAndDestroy);
}

void block::accelerateMoveRight(){
	Size size = Director::getInstance()->getVisibleSize();
	moveRightAndDestroy->release();		//旧的动作release

	auto moveRight = MoveBy::create(SceneMoveSecond, Vec2(-size.width*1.5, 0));
	moveRightAndDestroy = Sequence::create(moveRight, CallFunc::create(CC_CALLBACK_0(block1::restart, this)), nullptr);
	moveRightAndDestroy->setTag(BLOCK_MOVE_RIGHT_ACTION);
	moveRightAndDestroy->retain();
}


bool block1::init(){
	if (!block::init()){
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();
	Size box_size(size.height / 3.5, size.height / 3.5);
	body = PhysicsBody::createBox(box_size);
	body->setCategoryBitmask(0x0003);
	body->setCollisionBitmask(0x0004);
	body->setContactTestBitmask(0x0001);
	body->setGravityEnable(false);

	node = Node::create();
	node->setPhysicsBody(body);
	init_pos = Vec2(size.width*1.2, 0);
	node->setPosition(init_pos);

	auto step1 = MoveBy::create(0.5f, Vec2(0, size.height));
	auto gap1 = MoveBy::create(1.0f, Vec2(0, 0));
	auto step2 = MoveBy::create(0.5f, Vec2(0, -size.height));
	auto gap2 = MoveBy::create(1.0f, Vec2(0, 0));
	auto seq = Sequence::create(step1, gap1, step2, gap2, nullptr);
	auto re = RepeatForever::create(seq);
	act = re;
	act->retain();

	auto moveRight = MoveBy::create(SceneMoveSecond, Vec2(-size.width*1.5, 0));
	moveRightAndDestroy = Sequence::create(moveRight, CallFunc::create(CC_CALLBACK_0(block1::restart, this)), nullptr);
	moveRightAndDestroy->setTag(BLOCK_MOVE_RIGHT_ACTION);
	moveRightAndDestroy->retain();

	return true;
}

bool block2::init(){
	if (!block::init()){
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();
	Size box_size(size.width / 32, size.height / 2);
	body = PhysicsBody::createBox(box_size);
	body->setCategoryBitmask(0x0003);
	body->setCollisionBitmask(0x0004);
	body->setContactTestBitmask(0x0001);
	body->setGravityEnable(false);

	node = Node::create();
	node->setPhysicsBody(body);
	init_pos = Vec2(size.width*1.2, 0);
	node->setPosition(init_pos);

	auto step1 = MoveBy::create(1.5f, Vec2(0, size.height));
	auto step2 = MoveBy::create(1.5f, Vec2(0, -size.height));
	auto seq = Sequence::create(step1, step2, nullptr);
	act = RepeatForever::create(seq);
	act->retain();

	auto moveRight = MoveBy::create(SceneMoveSecond, Vec2(-size.width*1.5, 0));
	moveRightAndDestroy = Sequence::create(moveRight, CallFunc::create(CC_CALLBACK_0(block2::restart, this)), nullptr);
	moveRightAndDestroy->setTag(BLOCK_MOVE_RIGHT_ACTION);
	moveRightAndDestroy->retain();
	return true;
}

bool block3::init(){
	if (!block::init()){
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();
	Size box_size(size.height / 4, size.height / 50);
	body = PhysicsBody::createBox(box_size);
	body->setCategoryBitmask(0x0003);
	body->setCollisionBitmask(0x0004);
	body->setContactTestBitmask(0x0001);
	body->setGravityEnable(false);

	node = Node::create();
	node->setPhysicsBody(body);
	init_pos = Vec2(size.width*1.2, size.height / 2);
	node->setPosition(init_pos);
	node->setAnchorPoint(node->getContentSize() / 2);

	auto ro = RotateBy::create(5.0, 360);
	auto re = RepeatForever::create(ro);
	act = re;
	act->retain();

	auto moveRight = MoveBy::create(SceneMoveSecond, Vec2(-size.width*1.5, 0));
	moveRightAndDestroy = Sequence::create(moveRight, CallFunc::create(CC_CALLBACK_0(block3::restart, this)), nullptr);
	moveRightAndDestroy->setTag(BLOCK_MOVE_RIGHT_ACTION);
	moveRightAndDestroy->retain();
	return true;
}


//平行两横杆
bool double_block1_1::init(){
	block::init();

	Size size = Director::getInstance()->getVisibleSize();
	Size box_size(size.height / 3, size.height / 30);
	body = PhysicsBody::createBox(box_size);
	body->setCategoryBitmask(0x0003);
	body->setCollisionBitmask(0x0004);
	body->setContactTestBitmask(0x0001);
	body->setGravityEnable(false);

	node = Node::create();
	node->setPhysicsBody(body);
	init_pos = Vec2(size.width*1.2, size.height * 3 / 5);
	node->setPosition(init_pos);

	auto step1 = MoveBy::create(1.0f, Vec2(0, 0));		//固定障碍，没有动作,为了保证接口一致，原地踏步的动作
	act = RepeatForever::create(step1);
	act->retain();

	auto moveRight = MoveBy::create(SceneMoveSecond, Vec2(-size.width*1.5, 0));
	moveRightAndDestroy = Sequence::create(moveRight, CallFunc::create(CC_CALLBACK_0(double_block1_1::restart, this)), nullptr);
	moveRightAndDestroy->setTag(BLOCK_MOVE_RIGHT_ACTION);
	moveRightAndDestroy->retain();
	return true;
}

bool double_block1_2::init(){
	block::init();

	Size size = Director::getInstance()->getVisibleSize();
	Size box_size(size.height / 3, size.height / 30);
	body = PhysicsBody::createBox(box_size);
	body->setCategoryBitmask(0x0003);
	body->setCollisionBitmask(0x0004);
	body->setContactTestBitmask(0x0001);
	body->setGravityEnable(false);

	node = Node::create();
	node->setPhysicsBody(body);
	init_pos = Vec2(size.width*1.4, size.height * 2 / 5);
	node->setPosition(init_pos);

	auto step1 = MoveBy::create(1.0f, Vec2(0, 0));		//固定障碍，没有动作,为了保证接口一致，原地踏步的动作
	act = RepeatForever::create(step1);
	act->retain();

	auto moveRight = MoveBy::create(SceneMoveSecond, Vec2(-size.width*1.5, 0));
	moveRightAndDestroy = Sequence::create(moveRight, CallFunc::create(CC_CALLBACK_0(double_block1_2::restart, this)), nullptr);
	moveRightAndDestroy->setTag(BLOCK_MOVE_RIGHT_ACTION);
	moveRightAndDestroy->retain();
	return true;
}



//平行两竖杆
bool double_block2_1::init(){
	block::init();

	Size size = Director::getInstance()->getVisibleSize();
	Size box_size(size.height / 30, size.height / 3);
	body = PhysicsBody::createBox(box_size);
	body->setCategoryBitmask(0x0003);
	body->setCollisionBitmask(0x0004);
	body->setContactTestBitmask(0x0001);
	body->setGravityEnable(false);

	node = Node::create();
	node->setPhysicsBody(body);
	init_pos = Vec2(size.width*1.2, size.height * 2 / 5);
	node->setPosition(init_pos);

	auto step1 = MoveBy::create(1.0f, Vec2(0, 0));		//固定障碍，没有动作,为了保证接口一致，原地踏步的动作
	act = RepeatForever::create(step1);
	act->retain();

	auto moveRight = MoveBy::create(SceneMoveSecond, Vec2(-size.width*1.5, 0));
	moveRightAndDestroy = Sequence::create(moveRight, CallFunc::create(CC_CALLBACK_0(double_block2_1::restart, this)), nullptr);
	moveRightAndDestroy->setTag(BLOCK_MOVE_RIGHT_ACTION);
	moveRightAndDestroy->retain();
	return true;
}

bool double_block2_2::init(){
	block::init();

	Size size = Director::getInstance()->getVisibleSize();
	Size box_size(size.height / 30, size.height / 3);
	body = PhysicsBody::createBox(box_size);
	body->setCategoryBitmask(0x0003);
	body->setCollisionBitmask(0x0004);
	body->setContactTestBitmask(0x0001);
	body->setGravityEnable(false);

	node = Node::create();
	node->setPhysicsBody(body);
	init_pos = Vec2(size.width*1.5, size.height * 3 / 5);
	node->setPosition(init_pos);

	auto step1 = MoveBy::create(1.0f, Vec2(0, 0));		//固定障碍，没有动作,为了保证接口一致，原地踏步的动作
	act = RepeatForever::create(step1);
	act->retain();

	auto moveRight = MoveBy::create(SceneMoveSecond, Vec2(-size.width*1.5, 0));
	moveRightAndDestroy = Sequence::create(moveRight, CallFunc::create(CC_CALLBACK_0(double_block2_2::restart, this)), nullptr);
	moveRightAndDestroy->setTag(BLOCK_MOVE_RIGHT_ACTION);
	moveRightAndDestroy->retain();
	return true;
}



//三个旋转杆
bool triple_block1_1::init(){
	block::init();

	Size size = Director::getInstance()->getVisibleSize();
	Size box_size(size.height / 50, size.height / 3);
	body = PhysicsBody::createBox(box_size);
	body->setCategoryBitmask(0x0003);
	body->setCollisionBitmask(0x0004);
	body->setContactTestBitmask(0x0001);
	body->setGravityEnable(false);

	node = Node::create();
	node->setPhysicsBody(body);
	init_pos = Vec2(size.width*1.5, size.height * 3.7 / 5);
	node->setPosition(init_pos);

	auto ro = RotateBy::create(5.0, 360);
	auto re = RepeatForever::create(ro);
	act = re;
	act->retain();

	auto moveRight = MoveBy::create(SceneMoveSecond, Vec2(-size.width*2.0, 0));
	moveRightAndDestroy = Sequence::create(moveRight, CallFunc::create(CC_CALLBACK_0(triple_block1_1::restart, this)), nullptr);
	moveRightAndDestroy->setTag(BLOCK_MOVE_RIGHT_ACTION);
	moveRightAndDestroy->retain();
	return true;
}

bool triple_block1_2::init(){
	block::init();

	Size size = Director::getInstance()->getVisibleSize();
	Size box_size(size.height / 50, size.height / 3);		//障碍物尺寸
	body = PhysicsBody::createBox(box_size);
	body->setCategoryBitmask(0x0003);
	body->setCollisionBitmask(0x0004);
	body->setContactTestBitmask(0x0001);
	body->setGravityEnable(false);

	node = Node::create();
	node->setPhysicsBody(body);
	init_pos = Vec2(size.width*1.3, size.height * 1.3 / 5);		//障碍物位置
	node->setPosition(init_pos);

	auto ro = RotateBy::create(5.0, 360);
	auto re = RepeatForever::create(ro);
	act = re;
	act->retain();

	auto moveRight = MoveBy::create(SceneMoveSecond, Vec2(-size.width*2.0, 0));
	moveRightAndDestroy = Sequence::create(moveRight, CallFunc::create(CC_CALLBACK_0(triple_block1_2::restart, this)), nullptr);
	moveRightAndDestroy->setTag(BLOCK_MOVE_RIGHT_ACTION);
	moveRightAndDestroy->retain();
	return true;
}

bool triple_block1_3::init(){
	block::init();

	Size size = Director::getInstance()->getVisibleSize();
	Size box_size(size.height / 50, size.height / 3);
	body = PhysicsBody::createBox(box_size);
	body->setCategoryBitmask(0x0003);
	body->setCollisionBitmask(0x0004);
	body->setContactTestBitmask(0x0001);
	body->setGravityEnable(false);

	node = Node::create();
	node->setPhysicsBody(body);
	init_pos = Vec2(size.width*1.7, size.height * 1.3 / 5);
	node->setPosition(init_pos);

	auto ro = RotateBy::create(5.0, 360);
	auto re = RepeatForever::create(ro);
	act = re;
	act->retain();

	auto moveRight = MoveBy::create(SceneMoveSecond, Vec2(-size.width*2.0, 0));
	moveRightAndDestroy = Sequence::create(moveRight, CallFunc::create(CC_CALLBACK_0(triple_block1_3::restart, this)), nullptr);
	moveRightAndDestroy->setTag(BLOCK_MOVE_RIGHT_ACTION);
	moveRightAndDestroy->retain();
	return true;
}