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
bool PhysicsManager::onContactBegin(PhysicsContact& contact)
{	
	PhysicsBody* bodyA = contact.getShapeA()->getBody();
	PhysicsBody* bodyB = contact.getShapeB()->getBody();
	const char* bodyAName = bodyA->getNode()->getName().c_str();
	const char* bodyBName = bodyB->getNode()->getName().c_str();

	// If contact contains some of the listener names then inform the listeners
	for(int i = 0; i < (int)m_contactListeners.size(); i++)
	{
		PhysicsContactListener& currentListener = m_contactListeners[i];
		if (strcmp(bodyAName, currentListener.name) == 0)
		{
			currentListener.onContactCallback(PhysicsContactInformation(bodyA, bodyB));			
		}
		else if(strcmp(bodyBName, currentListener.name) == 0)
		{
			currentListener.onContactCallback(PhysicsContactInformation(bodyB, bodyA));			
		}
	}
	
	return true;
}

/*
* Add box colider using sprite size.
*/
void PhysicsManager::addBoxColider(Sprite* pSprite, float mass,
	bool bIsDynamic, bool bIsGravityEnabled)
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
void PhysicsManager::addCustomBox(cocos2d::Sprite* pSprite, cocos2d::Size size, 
	float mass, bool bIsDynamic, bool bIsGravityEnabled)
{
	auto boxColider = PhysicsBody::createBox(size,
		DEFAULT_PHYSICS_MATERIAL);
	boxColider->setDynamic(bIsDynamic);
	boxColider->setGravityEnable(bIsGravityEnabled);
	boxColider->setContactTestBitmask(CONTACT_COLLISION_MASK);
	boxColider->setMass(mass);
	pSprite->addComponent(boxColider);
}

/*
 * Add body name for which to listen for
 * contact event.
 */
void PhysicsManager::addContactListener(const char* bodyName,
	ContactCallback onContactBegin)
{	
	m_contactListeners.push_back(PhysicsContactListener(bodyName, onContactBegin));
}

bool PhysicsManager::containsJoint(std::vector<cocos2d::PhysicsJoint*> joints, 
	const char* jointTag) const
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