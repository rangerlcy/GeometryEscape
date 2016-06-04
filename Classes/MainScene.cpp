#include "MainScene.h"
#include "MainLayer.h"
#include "UnlimitedParallaxLayer.h"
#include "StartMenuLayer.h"
USING_NS_CC;

Scene* MainScene::createScene(){
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);

	//auto layer = MainLayer::create();
	auto layer = StartMenuLayer::create();
	scene->addChild(layer,0);

	//ÊÓ²î±³¾°
	auto bgLayer = UnlimitedParallaxLayer::create();
	scene->addChild(bgLayer, -1);

	return scene;
}