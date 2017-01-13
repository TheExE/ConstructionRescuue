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
	const char* bodyAName = bodyA->getNode()->getName().c_str();
	const char* bodyBName = bodyB->getNode()->getName().c_str();

	if ((strcmp(bodyAName, HOOK_NODE) == 0 && strcmp(bodyBName, BRICK_NODE) == 0) ||
		(strcmp(bodyBName, HOOK_NODE) == 0 && strcmp(bodyAName, BRICK_NODE) == 0))
	{

		if (!containsJoint(bodyA->getJoints(), HOOK_GRAB))
		{
			auto joint = PhysicsJointFixed::construct(bodyA, bodyB, Vec2(0,0));
			joint->setEnable(true);
			joint->setMaxForce(10000);
			joint->setTag(*HOOK_GRAB);
			bodyA->getWorld()->addJoint(joint);
		}
	}

	
	return true;
}

void PhysicsManager::addBoxColider(Sprite* pSprite, float mass, bool bIsDynamic, bool bIsGravityEnabled)
{
	auto boxColider = PhysicsBody::createBox(pSprite->getContentSize(),
	PhysicsMaterial(0.1f, 0.1f, 0.3f));
	boxColider->setDynamic(bIsDynamic);
	boxColider->setGravityEnable(bIsGravityEnabled);
	boxColider->setContactTestBitmask(0xFFFFFFFF);
	boxColider->setMass(mass);
	pSprite->addComponent(boxColider);
}
void PhysicsManager::addCustomBox(cocos2d::Sprite* pSprite, cocos2d::Size size, float mass, bool bIsDynamic, bool bIsGravityEnabled)
{
	auto boxColider = PhysicsBody::createBox(size,
		PhysicsMaterial(0.1f, 0.1f, 0.3f));
	boxColider->setDynamic(bIsDynamic);
	boxColider->setGravityEnable(bIsGravityEnabled);
	boxColider->setContactTestBitmask(0xFFFFFFFF);
	boxColider->setMass(mass);
	pSprite->addComponent(boxColider);
}
bool PhysicsManager::containsJoint(std::vector<cocos2d::PhysicsJoint*> joints, const char* jointTag) const
{
	bool isJointFound = false;
	for (int i = 0; i < joints.size(); i++)
	{
		if (joints.at(i)->getTag() == *jointTag)
		{
			isJointFound = true;
			break;
		}
	}

	return isJointFound;
}