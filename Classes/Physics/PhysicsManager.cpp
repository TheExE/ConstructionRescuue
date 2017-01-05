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
	cocos2d::log("Physics manager is initialized !");
	return true;
}

bool PhysicsManager::onContactBegin(cocos2d::PhysicsContact& contact)
{
	PhysicsBody* bodyA = contact.getShapeA()->getBody();
	PhysicsBody* bodyB = contact.getShapeB()->getBody();
	std::string bodyAName = bodyA->getNode()->getName();
	std::string bodyBName = bodyB->getNode()->getName();

	if ( (strcmp(bodyAName.c_str(), HOOK_NODE) == 0 && strcmp(bodyBName.c_str(), BRICK_NODE) == 0) ||
		(strcmp(bodyBName.c_str(), HOOK_NODE) == 0 && strcmp(bodyAName.c_str(), BRICK_NODE) == 0))
	{
		if (bodyA->getJoints().size() == 0)
		{
			PhysicsJointFixed::construct(bodyA, bodyB, Vec2(0, 0));
		}
	}

	
	return true;
}

void PhysicsManager::addBoxColider(Sprite* pSprite, bool bIsDynamic, bool bIsGravityEnabled)
{
	auto boxColider = PhysicsBody::createBox(pSprite->getContentSize(),
	PhysicsMaterial(0.1f, 0.1f, 0.3f));
	boxColider->setDynamic(bIsDynamic);
	boxColider->setGravityEnable(bIsGravityEnabled);
	boxColider->setContactTestBitmask(0xFFFFFFFF);
	pSprite->addComponent(boxColider);
}
void PhysicsManager::addCustomBox(cocos2d::Sprite* pSprite, cocos2d::Size size, bool bIsDynamic, bool bIsGravityEnabled)
{
	auto boxColider = PhysicsBody::createBox(size,
		PhysicsMaterial(0.1f, 0.1f, 0.3f));
	boxColider->setDynamic(bIsDynamic);
	boxColider->setGravityEnable(bIsGravityEnabled);
	boxColider->setContactTestBitmask(0xFFFFFFFF);
	pSprite->addComponent(boxColider);
}