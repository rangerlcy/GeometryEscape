#include "HelloWorldScene.h"
#include<iostream>
using namespace std;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
	auto _scene = Scene::createWithPhysics();
	//_scene = scene;
	_scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	/*设置重力
	Vec2 g(0, -10);
	scene->getPhysicsWorld()->setGravity(g);*/

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
	_scene->addChild(layer);

    // return the scene
	return _scene;
}


void HelloWorld::onEnter(){
	Layer::onEnter();
	
	this->getScene()->getPhysicsWorld()->setAutoStep(false);    //关闭自动模拟, 自动模拟会卡帧（按道理机器不至于），导致小球乱跳
	this->scheduleUpdate();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void HelloWorld::update(float delta){
	/*
	CCLOG只能输出char*类型的，要用标准输出要创建另外一个控制台
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	cout << delta << endl;*/
	this->getScene()->getPhysicsWorld()->step(0.05);			//步长越小模拟速度越快
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
	
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3.0);
	//body->setCategoryBitmask(0x0001);		//设置分类掩码， 默认为0xFFFFFFFF，int类型4字节共32位
	//body->setCollisionBitmask(0x0001);		//设置碰撞掩码，默认0xFFFFFFFF
	body->setContactTestBitmask(0x0001);		//设置接触测试掩码，默认0x00000000
											//如果物体A的分类掩码与B的碰撞掩码做逻辑与运算结果为0，则AB不发生碰撞，为1则碰撞
											//如果A的分类掩码与B的接触测试掩码做逻辑与运算结果为0，则不触发碰撞回调函数，为1则触发
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);

	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
    return true;
}


bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event){
	Vec2 pos = touch->getLocation();
	addSpriteAtPos(pos);
	return false;
}

bool HelloWorld::onContactBegin(PhysicsContact& contact){
	Sprite* sp = (Sprite*)contact.getShapeA()->getBody()->getNode();
	CCLOG("collsion!!!");
	return true;
}

void HelloWorld::addSpriteAtPos(Vec2 p){
	auto sp = Sprite::create("CloseNormal.png");
	

	//body默认有一个shape，可以用body->getShape(0)获得
	//body可以设置是否受重力影响、是否是静态刚体（静态刚体不受物理世界影响即不更新在物理世界里的状态，不做碰撞检测）
	//在形状类里可以设置物体的摩擦力、密度、弹性系数、质量等
	auto body = PhysicsBody::createCircle(sp->getContentSize().width/2);
	//physicsBody可以设置分类掩码和碰撞掩码
	//body->setCategoryBitmask(0x0001);
	//body->setCollisionBitmask(0x0001);
	body->setContactTestBitmask(0x0001);
	//body->setGravityEnable(false);

	sp->setPhysicsBody(body);
	sp->setPosition(p);
	this->addChild(sp);
}




//关闭的回调函数
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
