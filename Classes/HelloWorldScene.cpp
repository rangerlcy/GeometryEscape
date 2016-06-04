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

	/*��������
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
	
	this->getScene()->getPhysicsWorld()->setAutoStep(false);    //�ر��Զ�ģ��, �Զ�ģ��Ῠ֡����������������ڣ�������С������
	this->scheduleUpdate();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void HelloWorld::update(float delta){
	/*
	CCLOGֻ�����char*���͵ģ�Ҫ�ñ�׼���Ҫ��������һ������̨
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	cout << delta << endl;*/
	this->getScene()->getPhysicsWorld()->step(0.05);			//����ԽСģ���ٶ�Խ��
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
	//body->setCategoryBitmask(0x0001);		//���÷������룬 Ĭ��Ϊ0xFFFFFFFF��int����4�ֽڹ�32λ
	//body->setCollisionBitmask(0x0001);		//������ײ���룬Ĭ��0xFFFFFFFF
	body->setContactTestBitmask(0x0001);		//���ýӴ��������룬Ĭ��0x00000000
											//�������A�ķ���������B����ײ�������߼���������Ϊ0����AB��������ײ��Ϊ1����ײ
											//���A�ķ���������B�ĽӴ������������߼���������Ϊ0���򲻴�����ײ�ص�������Ϊ1�򴥷�
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
	

	//bodyĬ����һ��shape��������body->getShape(0)���
	//body���������Ƿ�������Ӱ�졢�Ƿ��Ǿ�̬���壨��̬���岻����������Ӱ�켴�������������������״̬��������ײ��⣩
	//����״����������������Ħ�������ܶȡ�����ϵ����������
	auto body = PhysicsBody::createCircle(sp->getContentSize().width/2);
	//physicsBody�������÷����������ײ����
	//body->setCategoryBitmask(0x0001);
	//body->setCollisionBitmask(0x0001);
	body->setContactTestBitmask(0x0001);
	//body->setGravityEnable(false);

	sp->setPhysicsBody(body);
	sp->setPosition(p);
	this->addChild(sp);
}




//�رյĻص�����
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
