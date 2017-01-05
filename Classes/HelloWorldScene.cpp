#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameConsts.h"

USING_NS_CC;

using namespace cocostudio::timeline;

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

// on "init" you need to initialize your instance
bool HelloWorld::init()
{   
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
	auto controlLayer = CSLoader::createNode("controlls.csb");
	rootNode->addChild(controlLayer);

	// World sprites
	m_Crane = new Crane();

	// Rope and hook are part of crane so they should be child of crane
	Sprite* craneSprite = (Sprite*)rootNode->getChildByName(CRANE_NODE);
	m_Crane->init(craneSprite, (Sprite*)craneSprite->getChildByName(ROPE_NODE),
		(Sprite*)craneSprite->getChildByName(HOOK_NODE));
	Sprite* ground = (Sprite*)rootNode->getChildByName(GROUND_NODE);
	Sprite* sky = (Sprite*)rootNode->getChildByName(SKY_NODE);
	sky->setGlobalZOrder(-2);
	
	// Init bricks
	m_Brick = new Brick();
	m_Brick->init((Sprite*)rootNode->getChildByName(BRICK_NODE));

	// Init physics
	m_PhysicsManager = new PhysicsManager();
	if (!m_PhysicsManager->init(this))
	{
		cocos2d::log("PhysicsManager: Failed to initialize !");
	}
	m_PhysicsManager->addBoxColider(ground, false);
	m_PhysicsManager->addBoxColider(m_Brick->getSprite(), true, true);
	Size craneSpriteSize = craneSprite->getContentSize();
	craneSpriteSize.width -= craneSpriteSize.width/1.37f;
	m_PhysicsManager->addCustomBox(craneSprite, craneSpriteSize, true, true);
	Size hookSpriteSize = m_Crane->getHookSprite()->getContentSize();
	hookSpriteSize.height = hookSpriteSize.height / 2.f;
	m_PhysicsManager->addCustomBox(m_Crane->getHookSprite(), hookSpriteSize, false);


	// UI elements
	m_UIDriveLeft = (Sprite*)controlLayer->getChildByName(DRIVE_LEFT_BUTTON);
	m_UIDriveRight = (Sprite*)controlLayer->getChildByName(DRIVE_RIGHT_BUTTON);
	m_UICraneLiftDown = (Sprite*)controlLayer->getChildByName(LOWER_CRANE_BUTTON);
	m_UICraneLiftUp = (Sprite*)controlLayer->getChildByName(HEIGHER_CRANE_BUTTON);
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
	if (m_UIDriveLeft->getBoundingBox().containsPoint(mouseEvent->getLocationInView())
		|| m_UIDriveRight->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_Crane->stopMovingCrane();
	}
	else if (m_UICraneLiftUp->getBoundingBox().containsPoint(mouseEvent->getLocationInView())
		|| m_UICraneLiftDown->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_Crane->stopMovingRope();
	}
}

void HelloWorld::onMouseDown(cocos2d::Event* plainEvent)
{
	EventMouse* mouseEvent = (EventMouse*)plainEvent;
	if (m_UIDriveLeft->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_Crane->startMovingCraneLeft(-20);
	}
	else if (m_UIDriveRight->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_Crane->startMovingCraneRight(20);
	}
	else if (m_UICraneLiftUp->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_Crane->startAscendingRope();
	}
	else if (m_UICraneLiftDown->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_Crane->startLoweringRope();
	}
}

void HelloWorld::addListenerWithSceneGraphPriority(cocos2d::EventListener* listener, cocos2d::Node* listeningNode)
{
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, listeningNode);
}