#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameConsts.h"
#include "Nodes/StaticBackground/StaticBackground.h"
#include "Layers/ControlsLayer.h"

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

	// Display fps info
	Director::getInstance()->setDisplayStats(false);

	// Load layout
	Node* rootNode = Node::create();
	
	// Create the world
	StaticBackground* pBackground = StaticBackground::create();
	if (pBackground->initStaticBackground())
	{
		rootNode->addChild(pBackground);
	}
	else
	{
		cocos2d::log("StaticBacground: Failed to initialize !");
	}
	
	m_pCrane = Crane::create();
	if (m_pCrane->initCrane())
	{
		rootNode->addChild(m_pCrane);
	}
	else
	{
		cocos2d::log("Crane: failed to initialize !");
	}

	// Init brick
	m_pBrick = new Brick();
	if (m_pBrick->initBrick())
	{
		rootNode->addChild(m_pBrick);
	}
	else
	{
		cocos2d::log("Brick: Failed to initialize !");
	}

	// Add the scene root
	addChild(rootNode);

	// Set physics contact listener context
	PhysicsManager::getInstance()->setContactListenerContext(this);

	// UI elements
	ControlsLayer* pControlsLayer = ControlsLayer::create();
	if (pControlsLayer->initControlsLayer())
	{		
		m_pUIDriveLeft = (Sprite*)pControlsLayer->getChildByName(BUTTON_LEFT);
		m_pUIDriveRight = (Sprite*)pControlsLayer->getChildByName(BUTTON_RIGHT);
		m_pUICraneMoveDown = (Sprite*)pControlsLayer->getChildByName(BUTTON_DOWN);
		m_pUICraneMoveUp = (Sprite*)pControlsLayer->getChildByName(BUTTON_UP);
		m_pUIToggleMagnet = (Sprite*)pControlsLayer->getChildByName(BUTTON_ACTION);
		if (m_pUIDriveLeft == nullptr)
		{
			cocos2d::log("HelloWorldScene: Failed to find UIDriveLeft button !");
		}
		if (m_pUIDriveRight == nullptr)
		{
			cocos2d::log("HelloWorldScene: Failed to find UIDriveRight button !");
		}
		if (m_pUICraneMoveUp == nullptr)
		{
			cocos2d::log("HelloWorldScene: Failed to find UICraneMoveUp button !");
		}
		if (m_pUICraneMoveDown == nullptr)
		{
			cocos2d::log("HelloWorldScene: Failed to find UICraneMoveDown button !");
		}
		if (m_pUIToggleMagnet == nullptr)
		{
			cocos2d::log("HelloWorldScene: Failed to find UIToggleMagnet button !");
		}
		addChild(pControlsLayer);
	}
	else
	{
		cocos2d::log("ControlsLayer: Failed to initialize !");
	}

	// Init input
	m_pMouseListener = EventListenerMouse::create();
	m_pMouseListener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	m_pMouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
	_eventDispatcher->addEventListenerWithFixedPriority(m_pMouseListener, 1);
	scheduleUpdate();

    return true;
}

void HelloWorld::update(float deltaTime)
{
	m_pCrane->update(deltaTime);
}

void HelloWorld::onMouseUp(Event* plainEvent)
{
	EventMouse* mouseEvent = (EventMouse*)plainEvent;
	const Vec2 mouseClickPosition = mouseEvent->getLocationInView();

	// Check if the click is on specific button
	if (m_pUIDriveLeft->getBoundingBox().containsPoint(mouseClickPosition)
		|| m_pUIDriveRight->getBoundingBox().containsPoint(mouseClickPosition))
	{
		m_pCrane->stopMovingCrane();
	}
	else if (m_pUICraneMoveUp->getBoundingBox().containsPoint(mouseClickPosition)
		|| m_pUICraneMoveDown->getBoundingBox().containsPoint(mouseClickPosition))
	{
		m_pCrane->stopMovingRope();
	}
	else if (m_pUIToggleMagnet->getBoundingBox().containsPoint(mouseClickPosition))
	{
		m_pCrane->toggleMagnet();
	}
}

void HelloWorld::onMouseDown(Event* plainEvent)
{
	EventMouse* mouseEvent = (EventMouse*)plainEvent;
	const Vec2 mouseClickPosition = mouseEvent->getLocationInView();
	
	if (m_pUIDriveLeft->getBoundingBox().containsPoint(mouseClickPosition))
	{
		m_pCrane->startMovingCrane(-Crane::MOVE_SPEED);
	}
	else if (m_pUIDriveRight->getBoundingBox().containsPoint(mouseClickPosition))
	{
		m_pCrane->startMovingCrane(Crane::MOVE_SPEED);
	}
	else if (m_pUICraneMoveUp->getBoundingBox().containsPoint(mouseClickPosition))
	{
		m_pCrane->startMovingTheRope(-Crane::CHAIN_MOVE_SPEED);
	}
	else if (m_pUICraneMoveDown->getBoundingBox().containsPoint(mouseClickPosition))
	{
		m_pCrane->startMovingTheRope(Crane::CHAIN_MOVE_SPEED);
	}
}

