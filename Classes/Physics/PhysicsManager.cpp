#include "PhysicsManager.h"
#include "HelloWorldScene.h"


using namespace cocos2d;

PhysicsManager::PhysicsManager()
{

}

bool PhysicsManager::init(HelloWorld* mainScene)
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PhysicsManager::onContactBegin, this);
	mainScene->addListenerWithSceneGraphPriority(contactListener, mainScene);
	return true;
}

bool PhysicsManager::onContactBegin(PhysicsContact& contact)
{
	return true;
}

void PhysicsManager::addBoxColider(Sprite* pSprite, bool bIsDynamic)
{
	auto boxColider = PhysicsBody::createBox(pSprite->getContentSize(),
	PhysicsMaterial(0.1f, 1.0f, 0.0f));
	boxColider->setDynamic(bIsDynamic);
	pSprite->addComponent(boxColider);
}