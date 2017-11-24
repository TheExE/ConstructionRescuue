#include "PhysicsManager.h"
#include "HelloWorldScene.h"
#include "../GameConsts.h"

using namespace cocos2d;

PhysicsManager::PhysicsManager()
{

}

PhysicsManager* PhysicsManager::getInstance()
{
	static PhysicsManager manager;
	return &manager;
}

bool PhysicsManager::setContactListenerContext(Node* pNode)
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PhysicsManager::onContactBegin, this);
	pNode->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, pNode);
	return true;
}

/*
 * Callback for when 2 object goes into contact.
*/
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
			auto joint = PhysicsJointFixed::construct(bodyA, bodyB, Vec2::ZERO);
			joint->setEnable(true);
			joint->setMaxForce(Crane::HOOK_MAX_FORCE);
			joint->setTag(*HOOK_GRAB);
			bodyA->getWorld()->addJoint(joint);
		}
	}

	
	return true;
}

/*
* Add box colider using sprite size.
*/
void PhysicsManager::addBoxColider(Sprite* pSprite, float mass, bool bIsDynamic, bool bIsGravityEnabled)
{
	auto boxColider = PhysicsBody::createBox(pSprite->getContentSize(),
		DEFAULT_PHYSICS_MATERIAL);
	boxColider->setDynamic(bIsDynamic);
	boxColider->setGravityEnable(bIsGravityEnabled);
	boxColider->setContactTestBitmask(CONTACT_COLLISION_MASK);
	boxColider->setMass(mass);
	pSprite->addComponent(boxColider);
}

/*
 * Add box colider with custom size.
*/
void PhysicsManager::addCustomBox(cocos2d::Sprite* pSprite, cocos2d::Size size, float mass, bool bIsDynamic, bool bIsGravityEnabled)
{
	auto boxColider = PhysicsBody::createBox(size,
		DEFAULT_PHYSICS_MATERIAL);
	boxColider->setDynamic(bIsDynamic);
	boxColider->setGravityEnable(bIsGravityEnabled);
	boxColider->setContactTestBitmask(CONTACT_COLLISION_MASK);
	boxColider->setMass(mass);
	pSprite->addComponent(boxColider);
}

bool PhysicsManager::containsJoint(std::vector<cocos2d::PhysicsJoint*> joints, const char* jointTag) const
{
	bool isJointFound = false;
	for (int i = 0; i < (int)joints.size(); i++)
	{
		if (joints.at(i)->getTag() == *jointTag)
		{
			isJointFound = true;
			break;
		}
	}

	return isJointFound;
}