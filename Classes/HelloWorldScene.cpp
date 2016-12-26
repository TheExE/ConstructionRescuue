#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameConsts.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
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
	m_Crane->init((Sprite*)rootNode->getChildByName("crane"));
	Sprite* ground = (Sprite*)rootNode->getChildByName("ground");
	
	// Create physics body for ground
	auto groundBody = PhysicsBody::createBox(ground->getContentSize(),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	groundBody->setDynamic(false);
	ground->addComponent(groundBody);



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
}

void HelloWorld::onMouseDown(cocos2d::Event* plainEvent)
{
	EventMouse* mouseEvent = (EventMouse*)plainEvent;
	if (m_UIDriveLeft->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_Crane->startMovingCraneLeft(-10);
	}
	else if (m_UIDriveRight->getBoundingBox().containsPoint(mouseEvent->getLocationInView()))
	{
		m_Crane->startMovingCraneRight(10);
	}
}
