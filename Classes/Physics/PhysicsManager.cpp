#include "PhysicsManager.h"


using namespace cocos2d;
// Create physics body for ground /*  CAUSED CRASH */
/*auto groundBody = PhysicsBody::createBox(ground->getContentSize(),
PhysicsMaterial(0.1f, 1.0f, 0.0f));
groundBody->setDynamic(false);
ground->addComponent(groundBody);*/

bool PhysicsManager::init(HelloWorld* mainScene)
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PhysicsManager::onContactBegin, this);
	mainScene->addListenerWithSceneGraphPriority(contactListener, mainScene);
	return true;
}

bool PhysicsManager::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}