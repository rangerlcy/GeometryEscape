#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;
class HelloWorld : public cocos2d::Layer
{
public:
    static Scene* createScene();
	
    virtual bool init();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onEnter();
	virtual void update(float delta);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	bool onContactBegin(PhysicsContact& contact);
	void addSpriteAtPos(Vec2 p);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

};

#endif // __HELLOWORLD_SCENE_H__
