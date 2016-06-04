#ifndef _START_MENU_LAYER_H
#define _START_MENU_LAYER_H

#include "cocos2d.h"
USING_NS_CC;


class StartMenuLayer:public Layer
{
public:
	CREATE_FUNC(StartMenuLayer);
	bool init();

	void recordClick();
	void playClick();
	void optionClick();

};




#endif