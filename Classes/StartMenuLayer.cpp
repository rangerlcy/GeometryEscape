#include "StartMenuLayer.h"
#include "MainLayer.h"

bool StartMenuLayer::init(){
	if (!Layer::init()){
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();

	auto menu = Menu::create();

	auto nameLabel = Label::create("Geometry Escape", "fonts/Marker Felt.ttf", 60);
	nameLabel->setPosition(Vec2(size.width / 2, size.height * 3 / 5));
	this->addChild(nameLabel);

	auto playLabel = Label::create("Play", "fonts/Marker Felt.ttf", 35);
	auto recodeLabel = Label::create("Record", "fonts/Marker Felt.ttf", 35);
	auto optionLabel = Label::create("Option", "fonts/Marker Felt.ttf", 35);

	auto menuItem1 = MenuItemLabel::create(recodeLabel, CC_CALLBACK_0(StartMenuLayer::recordClick, this));
	auto menuItem2 = MenuItemLabel::create(playLabel, CC_CALLBACK_0(StartMenuLayer::playClick, this));
	auto menuItem3 = MenuItemLabel::create(optionLabel, CC_CALLBACK_0(StartMenuLayer::optionClick, this));

	menu->addChild(menuItem1);
	menu->addChild(menuItem2);
	menu->addChild(menuItem3);

	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPosition(Vec2(size.width/2, size.height*1/5));

	this->addChild(menu);

	return true;
}


void StartMenuLayer::recordClick(){

}

void StartMenuLayer::playClick(){
	
	auto layer = MainLayer::create();
	this->_parent->addChild(layer);
	this->removeFromParent();
}

void StartMenuLayer::optionClick(){

}