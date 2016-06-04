#ifndef __UnlimitedParallaxLayer__
#define  __UnlimitedParallaxLayer__

#include "cocos2d.h"

USING_NS_CC;

class UnlimitedParallaxLayer:public Layer
{
public:
	CREATE_FUNC(UnlimitedParallaxLayer);
	virtual bool init();

	Layer* createBg(char* url);
	virtual void update(float delta);

private:
	Layer *bg1;
	Layer *bg2;
	Layer *bg3;
	Layer *bg4;
	float speed;
};



#endif // !__UnlimitedParallaxLayer