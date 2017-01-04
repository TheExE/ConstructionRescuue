#include "PhysicsManager.h"
#include "HelloWorldScene.h"
#include "../GameConsts.h"


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
	PhysicsBody* bodyA = contact.getShapeA()->getBody();
	PhysicsBody* bodyB = contact.getShapeB()->getBody();
	
	if (bodyA->getName() == HOOK_NODE && bodyB->getName() == BRICK_NODE)
	{
		//bodyB->getNode()->setParent(bodyA->getNode());
		PhysicsJointFixed::construct(bodyA, bodyB, Vec2(0, 0));
	}

	cocos2d::log("WHY ?????");
	return true;
}

void PhysicsManager::addBoxColider(Sprite* pSprite, bool bIsDynamic, bool bIsGravityEnabled)
{
	auto boxColider = PhysicsBody::createBox(pSprite->getContentSize(),
	PhysicsMaterial(0.1f, 0.1f, 0.3f));
	boxColider->setDynamic(bIsDynamic);
	boxColider->setGravityEnable(bIsGravityEnabled);
	pSprite->addComponent(boxColider);
}
void PhysicsManager::addCustomBox(cocos2d::Sprite* pSprite, cocos2d::Size size, bool bIsDynamic, bool bIsGravityEnabled)
{
	auto boxColider = PhysicsBody::createBox(size,
		PhysicsMaterial(0.1f, 0.1f, 0.3f));
	boxColider->setDynamic(bIsDynamic);
	boxColider->setGravityEnable(bIsGravityEnabled);
	pSprite->addComponent(boxColider);
}