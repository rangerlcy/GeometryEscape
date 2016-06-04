#include "MainLayer.h"
#include "UnlimitedParallaxLayer.h"
#include "StartMenuLayer.h"

USING_NS_CC;

void MainLayer::onEnter(){
	Layer::onEnter();

	this->getScene()->getPhysicsWorld()->setAutoStep(false);    //关闭自动模拟, 自动模拟会卡帧（按道理机器不至于），导致小球乱跳
	this->scheduleUpdate();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MainLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

//静态变量初始化
std::vector<block*> MainLayer::block_array = std::vector<block*>();
std::vector<block*> MainLayer::double_block_array = std::vector<block*>();
std::vector<block*> MainLayer::triple_block_array = std::vector<block*>();
std::vector<ray*> MainLayer::ray_array = std::vector<ray*>();
std::vector<shoot*> MainLayer::shoot_array = std::vector<shoot*>();

bool MainLayer::init(){
	if (!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	
	
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3.0); 
	body->setCategoryBitmask(0x0001);
	body->setCollisionBitmask(0x0001);
	body->setContactTestBitmask(0x0000);
	body->getShape(0)->setRestitution(0.0);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);

	//玩家精灵
	auto sp = Sprite::create("CloseNormal.png");
	sp->setTag(PLAYER);
	auto sp_body = PhysicsBody::createCircle(sp->getContentSize().width / 2);
	sp_body->setCategoryBitmask(0x0007);
	sp_body->setCollisionBitmask(0x0007);
	sp_body->setContactTestBitmask(0x0001);
	sp->setPhysicsBody(sp_body);
	sp->setPosition(visibleSize / 2);
	this->addChild(sp);
	player = sp;

	//游戏进度管理线程，随着游戏得分增加，难度加大
	level = 1;
	time = Label::createWithTTF("0:0.0", "fonts/arial.ttf", 25);
	time->setPosition(visibleSize / 2);
	this->addChild(time);
	game_manager = new std::thread(&MainLayer::globe_manager, this);


	initShoot();
	schedule(schedule_selector(MainLayer::runShoot), 4.0f, CC_REPEAT_FOREVER, 0.0f);

	initRay();
	schedule(schedule_selector(MainLayer::runRay), 4.0f, CC_REPEAT_FOREVER, 0.0f);

	initBlock();
	schedule(schedule_selector(MainLayer::runBlock), 3.0f, CC_REPEAT_FOREVER, 0.0f);


	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	return true;
}

bool MainLayer::onContactBegin(PhysicsContact& contact){
	//Sprite* sp = (Sprite*)contact.getShapeA()->getBody()->getNode();
	int mask1 = contact.getShapeA()->getCategoryBitmask();
	int mask2 = contact.getShapeB()->getCategoryBitmask();
	if (mask1 == 7 || mask2 == 7){
		CCLOG("collsion!!!");
	}
	
	return true;
}

bool MainLayer::onTouchBegan(Touch *touch, Event *unused_event){
	Vec2 pos = touch->getLocation();
	//setGravityVector(pos);
	player->setPosition(pos);
	return false;
}

void MainLayer::setGravityVector(Vec2 pos){
	Vec2 sp_pos = this->getChildByTag(PLAYER)->getPosition();
	this->getScene()->getPhysicsWorld()->setGravity((pos-sp_pos)*0.1);
}

void MainLayer::update(float delta){

	this->getScene()->getPhysicsWorld()->step(0.03);
	Size size = Director::getInstance()->getVisibleSize();
	//光线障碍的更新
	for (int i = 0; i < ray_array.size(); i++){
		if (ray_array[i]->_trigger == 1 && level>2){			//难度为3以上时才出现
			
			float dis = ray_array[i]->distance_from_trigger;

			if (dis > ray_array[i]->from1_2.x - ray_array[i]->from1_1.x){			//满足条件则说明光线移动完毕
				ray_array[i]->ray_reset();
				removeChild(ray_array[i]->_node1);
				removeChild(ray_array[i]->_node2);
				continue;
			}

			//光线种类1
			if (ray_array[i]->category == 1){
				removeChild(ray_array[i]->_node1);
				ray_array[i]->_node1 = DrawNode::create();

				Vec2 point1 = ray_array[i]->from1_1 + Vec2(dis, 0);
				Vec2 point2 = ray_array[i]->end1_1 + Vec2(dis,0);
				Vec2 point3 = point2;

				auto func = CC_CALLBACK_3(ray::anyRay, ray_array[i]);
				this->getScene()->getPhysicsWorld()->rayCast(func, point1, point2, &point3);
				ray_array[i]->_node1->drawDot(point1, 5, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
				ray_array[i]->_node1->drawSegment(point1, point3, 1.5, Color4F(1.0f, 0.0f, 0.0f, 1.0f));
				if (point2 != point3)
				{
					ray_array[i]->_node1->drawDot(point3, 5, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
				}
				addChild(ray_array[i]->_node1);
				ray_array[i]->distance_from_trigger += 1;
				

				//如果point3落在player的范围内，说明光线射中了player
				float dx = 0;
				float dd = (player->getContentSize().width / 2) * (player->getContentSize().width / 2);
				Vec2 a = player->getPosition();
				Vec2 b = point3;
				dx = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
				if (dx < dd){
					CCLOG("ray shoot your");
				}
			}

			//光线种类2
			if (ray_array[i]->category == 2){
				removeChild(ray_array[i]->_node1);
				removeChild(ray_array[i]->_node2);
				ray_array[i]->_node1 = DrawNode::create();
				ray_array[i]->_node2 = DrawNode::create();

				//其中一条光线
				Vec2 point1 = ray_array[i]->from1_1 + Vec2(dis, 0);
				Vec2 point2 = ray_array[i]->end1_1 + Vec2(dis, 0);
				Vec2 point3 = point2;
				
				auto func = CC_CALLBACK_3(ray::anyRay, ray_array[i]);
				this->getScene()->getPhysicsWorld()->rayCast(func, point1, point2, &point3);
				ray_array[i]->_node1->drawSegment(point1, point3, 1.5, Color4F(1.0f, 0.0f, 0.0f, 1.0f));
				ray_array[i]->_node1->drawDot(point1, 5, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
				if (point2 != point3)
				{
					ray_array[i]->_node1->drawDot(point3, 5, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
				}
				addChild(ray_array[i]->_node1);

				//另外一条光线
				Vec2 point7 = ray_array[i]->from2_1 + Vec2(dis, 0);
				Vec2 point8 = ray_array[i]->end2_1 + Vec2(dis, 0);
				Vec2 point9 = point8;

				this->getScene()->getPhysicsWorld()->rayCast(func, point7, point8, &point9);
				ray_array[i]->_node2->drawSegment(point7, point8, 1.5, Color4F(1.0f, 0.0f, 0.0f, 1.0f));
				ray_array[i]->_node2->drawDot(point7, 5, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
				if (point9 != point8)
				{
					ray_array[i]->_node2->drawDot(point9, 5, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
				}
				addChild(ray_array[i]->_node2);

				ray_array[i]->distance_from_trigger += RayMoveDistancePerFrame;		//每帧向右移动 RayMoveDistancePerFlame
			}
		}
	}

	//炮台的更新
	for (int i = 0; i < shoot_array.size();i++)
	{
		if (shoot_array[i]->_trigger == 1 && level>3){			//难度为4以上时才出现
			float dis = shoot_array[i]->distance_from_trigger;

			if (dis > size.width*1.5){			//满足条件则说明炮台移动完毕
				shoot_array[i]->reset();
				removeChild(shoot_array[i]->node1);
				continue;
			}

			removeChild(shoot_array[i]->node1);
			shoot_array[i]->node1 = DrawNode::create();			//炮台基座擦了后重画

			Node* player = getChildByTag(PLAYER);
			Vec2 player_pos = player->getPosition();
			shoot_array[i]->shoot_base_pos = shoot_array[i]->init_pos + Vec2(-dis, 0);
			Vec2 point = player_pos - shoot_array[i]->shoot_base_pos;

			shoot_array[i]->player_pos = player_pos;
			shoot_array[i]->rad = atan2(point.y, point.x);
			shoot_array[i]->node2->setRotation(-CC_RADIANS_TO_DEGREES(shoot_array[i]->rad));			//炮管更新旋转角度和位置
			shoot_array[i]->node2->setPosition(shoot_array[i]->shoot_base_pos);

			shoot_array[i]->node1->drawDot(shoot_array[i]->shoot_base_pos, 15, Color4F(1.0f, 1.0f, 1.0f, 1.0f));
			this->addChild(shoot_array[i]->node1);

			if (dis > shoot_array[i]->offset && dis< shoot_array[i]->offset+size.width){		//炮台已经进入屏幕视野范围内
				int dd = dis - shoot_array[i]->offset;
				if (dd % shoot_array[i]->bullet_shoot_gap ==0)			//发射子弹
				{
					float ra = shoot_array[i]->rad;
					
					auto body = PhysicsBody::createCircle(5);			//子弹刚体
					body->setCategoryBitmask(0x0003);
					body->setCollisionBitmask(0x0004);
					body->setContactTestBitmask(0x0001);
					body->setGravityEnable(false);

					auto node = Node::create();			//子弹节点
					node->setPhysicsBody(body);
					Vec2 pos = shoot_array[i]->shoot_base_pos + Vec2((shoot_array[i]->shoot_length + 10)*cosf(ra), (shoot_array[i]->shoot_length + 10)*sinf(ra));
					node->setPosition(pos);
					this->addChild(node);

					//移动子弹的动作
					float len = size.width + size.height;
					Vec2 to = Vec2(len*cosf(ra), len*sinf(ra));
					auto step1 = MoveBy::create(BulletMoveSecond, to);
					auto act = Sequence::create(step1, CallFunc::create(CC_CALLBACK_0(MainLayer::deleteBullet, this, node)), nullptr);		//移动完毕后执行回调删除
					node->runAction(act);

					/*float sec = size.width / 60;
					auto act2 = MoveBy::create(sec, Vec2(-size.width, 0));
					node->runAction(act2);*/
				}
			}

			shoot_array[i]->distance_from_trigger += shootMoveDistancePerFrame;
		}
	}

}

void MainLayer::initShoot(){
	shoot* s1 = shoot::create();
	s1->retain();

	shoot_array.push_back(s1);

	this->addChild(s1->node2);
}


//光线的用法与一般的node不同，是在update函数里添加到layer中的
void MainLayer::initRay(){

	ray* r1 = ray1::create();
	r1->retain();
	ray_array.push_back(r1);

	/*ray* r2 = ray2::create();
	r2->retain();
	ray_array.push_back(r2);*/
}



void MainLayer::initBlock(){
	block* b1 = block1::create();
	block* b2 = block2::create();
	block* b3 = block3::create();
	block* double_b1_1 = double_block1_1::create();
	block* double_b1_2 = double_block1_2::create();
	block* double_b2_1 = double_block2_1::create();
	block* double_b2_2 = double_block2_2::create();
	block* triple_b1_1 = triple_block1_1::create();
	block* triple_b1_2 = triple_block1_2::create();
	block* triple_b1_3 = triple_block1_3::create();

	b1->retain();
	b2->retain();
	b3->retain();
	double_b1_1->retain();
	double_b1_2->retain();
	double_b2_1->retain();
	double_b2_2->retain();
	triple_b1_1->retain();
	triple_b1_2->retain();
	triple_b1_3->retain();

	block_array.push_back(b1);
	block_array.push_back(b2);
	block_array.push_back(b3);
	double_block_array.push_back(double_b1_1);
	double_block_array.push_back(double_b1_2);
	double_block_array.push_back(double_b2_1);
	double_block_array.push_back(double_b2_2);
	triple_block_array.push_back(triple_b1_1);
	triple_block_array.push_back(triple_b1_2);
	triple_block_array.push_back(triple_b1_3);

	this->addChild(b1->node);
	this->addChild(b2->node);
	this->addChild(b3->node);
	this->addChild(double_b1_1->node);
	this->addChild(double_b1_2->node);
	this->addChild(double_b2_1->node);
	this->addChild(double_b2_2->node);
	this->addChild(triple_b1_1->node);
	this->addChild(triple_b1_2->node);
	this->addChild(triple_b1_3->node);
}

void MainLayer::runBlock(float dt){
	Size size = Director::getInstance()->getVisibleSize();

	int rando = floor(CCRANDOM_0_1() * 3);
	if (rando == 3){
		rando -= 1;
	}

	int len, rand;
	block* b1, *b2, *b3;
	//rando = 2;
	switch (rando)
	{
	case 0:			//单个使用的障碍
		len = block_array.size();
		rand = floor(CCRANDOM_0_1()*len);
		if (rand == len){
			rand -= 1;
		}

		b1 = block_array[rand];
		if (b1->node->getActionByTag(BLOCK_MOVE_RIGHT_ACTION)){
			return;
		}
		b1->come();
		break;
	case 1:			//成对使用的障碍
		len = double_block_array.size()/2;
		rand = floor(CCRANDOM_0_1()*len);
		if (rand == len){
			rand -= 1;
		}

		b1 = double_block_array[rand*2];
		b2 = double_block_array[rand * 2+1];
		if (b1->node->getActionByTag(BLOCK_MOVE_RIGHT_ACTION) || b2->node->getActionByTag(BLOCK_MOVE_RIGHT_ACTION)){
			return;
		}
		b1->come();
		b2->come();
		break;
	case 2:			//成三使用的障碍
		if (level < 2){		//level大于2解锁该障碍
			return;
		}
		len = triple_block_array.size() / 3;
		rand = floor(CCRANDOM_0_1()*len);
		if (rand == len){
			rand -= 1;
		}

		b1 = triple_block_array[rand * 3];
		b2 = triple_block_array[rand * 3 + 1];
		b3 = triple_block_array[rand * 3 + 2];
		if (b1->node->getActionByTag(BLOCK_MOVE_RIGHT_ACTION) || b2->node->getActionByTag(BLOCK_MOVE_RIGHT_ACTION) || b3->node->getActionByTag(BLOCK_MOVE_RIGHT_ACTION)){
			return;
		}
		b1->come();
		b2->come();
		b3->come();
		break;
	default:
		break;
	}	
}

void MainLayer::runRay(float dt){
	for (int i = 0; i < ray_array.size(); i++){
		if (ray_array[i]->_trigger == 0){
			ray_array[i]->ray_trigger();
			break;
		}
	}
}


void MainLayer::runShoot(float dt){
	for (int i = 0; i < shoot_array.size(); i++){
		if (shoot_array[i]->_trigger == 0){
			shoot_array[i]->move_trigger();
			break;
		}
	}
}

void MainLayer::deleteBullet(Node *bullet){
	removeChild(bullet);
}

//游戏正式开始, 另开一个线程管理游戏进度
void MainLayer::run(){
	auto visibleSize = Director::getInstance()->getVisibleSize();

	
}

void MainLayer::globe_manager(){
	mins = 0;
	sec = 0;
	msec = 0;
	schedule(schedule_selector(MainLayer::timeCount), 0.1, CC_REPEAT_FOREVER, 0);
}


void MainLayer::timeCount(float dt){
	msec += 10;
	if (msec >= 100){
		sec += 1;
		msec = 0;
	}

	if (sec >= 60){
		mins += 1;
		sec = 0;
	}
	std::ostringstream o;
	int mm = msec / 10;
	o<< mins <<":" << sec<<"."<<mm;
	std::string str = o.str();
	time->setString(str);

	if (sec > 15 && level <= 1){		//n秒后难度+1
		level++;
	}
	if (sec>30 && level<=2)
	{
		level++;
	}
	if (sec > 50 && level <= 3){
		level++;
	}

	//1:10秒后开始加速
	if (sec+mins*60 > 70 && level<=4){		

		level++;
		CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
		pScheduler->setTimeScale(1.5f);			//全局加速1.5
		/*SceneMoveSecond -= 4;
		BulletMoveSecond -= 3;
		RayMoveDistancePerFrame += 5;
		for (int i = 0; i < block_array.size();i++)
		{
			block_array[i]->accelerateMoveRight();
		}*/
	}

	if (sec + mins * 60 > 120 && level <= 5){
		level++;
		CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
		pScheduler->setTimeScale(2.0f); //全局加速2倍

	}

	if (sec + mins * 60 > 200 && level <=6){
		level++;
		CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
		pScheduler->setTimeScale(3.0f); 

	}
}