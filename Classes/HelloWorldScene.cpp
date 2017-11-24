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
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pMouseListener, this);
	scheduleUpdate();

    return true;
}

void HelloWorld::update(float deltaTime)
{
	m_pCrane->update(deltaTime);
}

void HelloWorld::onMouseUp(cocos2d::Event* plainEvent)
{
	EventMouse* mouseEvent = (EventMouse*)plainEvent;

	// Check if the click is on specific button
	if (m_pUIDriveLeft->getBoundingBox().containsPoint(mouseEvent->getLocationInView())
		|| m_pUIDriveRight->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_pCrane->stopMovingCrane();
	}
	else if (m_pUICraneMoveUp->getBoundingBox().containsPoint(mouseEvent->getLocationInView())
		|| m_pUICraneMoveDown->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_pCrane->stopMovingRope();
	}
}

void HelloWorld::onMouseDown(cocos2d::Event* plainEvent)
{
	EventMouse* mouseEvent = (EventMouse*)plainEvent;
	Vec2 positionInView = mouseEvent->getLocationInView();
	Vec2 leftButtonPosition = m_pUIDriveLeft->getPosition();
	cocos2d::log("VIEW X:%d, Y:%d", positionInView.x, positionInView.y);
	cocos2d::log("Left Button X:%d, Y:%d", leftButtonPosition.x, leftButtonPosition.y);
	
	if (m_pUIDriveLeft->getBoundingBox().containsPoint(positionInView))
	{
		m_pCrane->startMovingCrane(-Crane::MOVE_SPEED);
	}
	else if (m_pUIDriveRight->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_pCrane->startMovingCrane(Crane::MOVE_SPEED);
	}
	else if (m_pUICraneMoveUp->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_pCrane->startMovingTheRope(Crane::ROPE_MOVE_SPEED);
	}
	else if (m_pUICraneMoveDown->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_pCrane->startMovingTheRope(Crane::ROPE_MOVE_SPEED);
	}
}

