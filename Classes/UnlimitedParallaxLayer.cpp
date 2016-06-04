#include "UnlimitedParallaxLayer.h"


bool UnlimitedParallaxLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	speed = 10;
	this->scheduleUpdate();
	
	bg1 = createBg("bgLayer.jpg");
	bg2 = createBg("bgLayer2.png");
	bg3 = createBg("bgLayer3.png");
	bg4 = createBg("bgLayer4.png");
	this->addChild(bg1);
	this->addChild(bg2);
	this->addChild(bg3);
	this->addChild(bg4);

	return true;
}

void UnlimitedParallaxLayer::update(float delta){
	Size size = Director::getInstance()->getVisibleSize();

	bg1->setPositionX(bg1->getPositionX() - speed*0.1);
	if (bg1->getPositionX() < -size.width){
		bg1->setPositionX(0);
	}

	bg2->setPositionX(bg2->getPositionX() - speed*0.25);
	if (bg2->getPositionX() < -size.width){
		bg2->setPositionX(0);
	}

	bg3->setPositionX(bg3->getPositionX() - speed*0.35);
	if (bg3->getPositionX() < -size.width){
		bg3->setPositionX(0);
	}

	bg4->setPositionX(bg4->getPositionX() - speed*0.55);
	if (bg4->getPositionX() < -size.width){
		bg4->setPositionX(0);
	}
}

Layer* UnlimitedParallaxLayer::createBg(char* url){
	auto layer = Layer::create();
	auto sp1 = Sprite::create(url);

	Size ss = sp1->getContentSize();

	sp1->setPosition(Vec2(ss.width/2, ss.height/2));
	layer->addChild(sp1);

	auto sp2 = Sprite::create(url);
	sp2->setPosition(Vec2(ss.width / 2, ss.height / 2) + Vec2(ss.width, 0));
	layer->addChild(sp2);

	return layer;
}