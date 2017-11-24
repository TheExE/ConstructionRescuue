#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameConsts.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	// Load layout
	Node* rootNode = Node::create();
	

	// Create the world
	//m_Crane = new Crane();

	// Rope and hook are part of crane so they should be child of crane
	/*Sprite* craneSprite = (Sprite*)rootNode->getChildByName(CRANE_NODE);
	craneSprite->setPosition(Vec2(100, 222));
	rootNode->addChild(craneSprite);
	m_Crane->init(craneSprite, Sprite::create("res/white-pixel.png"),
		(Sprite*)craneSprite->getChildByName(HOOK_NODE));
	Sprite* ground = (Sprite*)rootNode->getChildByName(GROUND_NODE);
	Sprite* sky = (Sprite*)rootNode->getChildByName(SKY_NODE);
	sky->setRotation(0);
	sky->setGlobalZOrder(SKY_ORDER_LAYER);

	// Init bricks
	m_Brick = new Brick();
	m_Brick->init((Sprite*)rootNode->getChildByName(BRICK_NODE));

	// Init physics
	m_PhysicsManager = new PhysicsManager();
	if (!m_PhysicsManager->init(this))
	{
		cocos2d::log("PhysicsManager: Failed to initialize !");
	}*/
	/*m_PhysicsManager->addBoxColider(ground, PHYSICS_INFINITY, false);
	m_PhysicsManager->addBoxColider(m_Brick->getSprite(), BRICK_MASS, true, true);
	Size craneSpriteSize = craneSprite->getContentSize();
	craneSpriteSize.width -= craneSpriteSize.width / 1.37f;
	m_PhysicsManager->addCustomBox(craneSprite, craneSpriteSize, CRANE_MASS, true, true);
	Size hookSpriteSize = m_Crane->getHookSprite()->getContentSize();
	hookSpriteSize.height = hookSpriteSize.height / 2.f;
	m_PhysicsManager->addCustomBox(m_Crane->getHookSprite(), hookSpriteSize, HOOK_MASS, false);*/

	// UI elements
	/*m_UIDriveLeft = (Sprite*)controlLayer->getChildByName(DRIVE_LEFT_BUTTON);
	m_UIDriveRight = (Sprite*)controlLayer->getChildByName(DRIVE_RIGHT_BUTTON);
	m_UICraneMoveDown = (Sprite*)controlLayer->getChildByName(LOWER_CRANE_BUTTON);
	m_UICraneMoveUp = (Sprite*)controlLayer->getChildByName(HEIGHER_CRANE_BUTTON);*/
	addChild(rootNode);

	// Init input
	m_MouseListener = EventListenerMouse::create();
	m_MouseListener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	m_MouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_MouseListener, this);
	scheduleUpdate();

    return true;
}

void HelloWorld::update(float deltaTime)
{
	m_Crane->update(deltaTime);
}

void HelloWorld::onMouseUp(cocos2d::Event* plainEvent)
{
	EventMouse* mouseEvent = (EventMouse*)plainEvent;

	// Check if the click is on specific button
	if (m_UIDriveLeft->getBoundingBox().containsPoint(mouseEvent->getLocationInView())
		|| m_UIDriveRight->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_Crane->stopMovingCrane();
	}
	else if (m_UICraneMoveUp->getBoundingBox().containsPoint(mouseEvent->getLocationInView())
		|| m_UICraneMoveDown->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_Crane->stopMovingRope();
	}
}

void HelloWorld::onMouseDown(cocos2d::Event* plainEvent)
{
	EventMouse* mouseEvent = (EventMouse*)plainEvent;
	if (m_UIDriveLeft->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_Crane->startMovingCrane(-CRANE_MOVE_SPEED);
	}
	else if (m_UIDriveRight->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_Crane->startMovingCrane(CRANE_MOVE_SPEED);
	}
	else if (m_UICraneMoveUp->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_Crane->startMovingTheRope(ROPE_MOVE_SPEED);
	}
	else if (m_UICraneMoveDown->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_Crane->startMovingTheRope(ROPE_MOVE_SPEED);
	}
}

void HelloWorld::addListenerWithSceneGraphPriority(cocos2d::EventListener* listener, cocos2d::Node* listeningNode)
{
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, listeningNode);
}

