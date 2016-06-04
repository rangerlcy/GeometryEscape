#include "ray.h"
USING_NS_CC;

bool ray::init(){
	if (!Node::init()){
		return false;
	}
	_trigger = 0;
	distance_from_trigger = 0;
	_node1 = nullptr;
	_node2 = nullptr;
	return true;
}

void ray::ray_trigger(){
	_trigger = 1;
	distance_from_trigger = 0;
}

void ray::ray_reset(){
	_trigger = 0;
	distance_from_trigger = 0;
}

bool ray::anyRay(PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data){
	*((Vec2*)data) = info.contact;
	return false;
}


bool ray1::init(){
	if (!ray::init()){
		return false;
	}
	_trigger = 0;		//光线不触发， =1时触发
	
	Size size = Director::getInstance()->getVisibleSize();

	category = 1;
	from1_1 = Vec2(10,10);
	end1_1 = Vec2(10, size.height);

	from1_2 = from1_1+Vec2(size.width, 0);
	end1_2 = end1_1+Vec2(size.width, 0);
	return true;
}



bool ray2::init(){
	if (!ray::init()){
		return false;
	}
	_trigger = 0;		//光线不触发， =1时触发
	

	Size size = Director::getInstance()->getVisibleSize();

	category = 2;
	from1_1 = Vec2(10, 10);
	end1_1 = Vec2(size.width, size.height);
	from1_2 = from1_1+Vec2(size.width , 0);
	end1_2 = end1_1 + Vec2(size.width, 0);

	from2_1 = Vec2(10, size.height-10);
	end2_1 = Vec2(size.width , 0);
	from2_2 = from2_1 + Vec2(size.width, 0);
	end2_2 = end2_1 + Vec2(size.width, 0);
	return true;
}