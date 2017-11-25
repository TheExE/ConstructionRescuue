#pragma once

#include "cocos2d.h"

struct PhysicsContactInformation;
typedef std::function<bool(PhysicsContactInformation& contact)> ContactCallback;
struct PhysicsContactListener
{
	const char* name;
	ContactCallback onContactCallback;

	PhysicsContactListener(const char* name, ContactCallback onContactCallback)
	{
		this->name = name;
		this->onContactCallback = onContactCallback;
	}
};
struct PhysicsContactInformation
{
	cocos2d::PhysicsBody* pListenerShape;
	cocos2d::PhysicsBody* pTheOtherShape;
	
	PhysicsContactInformation(cocos2d::PhysicsBody* pListenerShape,
		cocos2d::PhysicsBody* pTheOtherShape)
	{
		this->pListenerShape = pListenerShape;
		this->pTheOtherShape = pTheOtherShape;		
	}
};

class PhysicsManager
{
public:
	static PhysicsManager* getInstance();		
	bool setContactListenerContext(cocos2d::Node* node);
	void addBoxColider(cocos2d::Sprite* pSprite, float mass, bool bIsDynamic, bool bIsGravityEnabled = false);
	void addCustomBox(cocos2d::Sprite* pSprite, cocos2d::Size size, float mass, bool bIsDynamic, bool bIsGravityEnabled = false);
	void addContactListener(const char* bodyName, ContactCallback onContactBegin);
	bool containsJoint(std::vector<cocos2d::PhysicsJoint*> joints, const char* jointTag) const;

private:
	PhysicsManager();
	bool onContactBegin(cocos2d::PhysicsContact& contact);		

private:	
	static PhysicsManager* m_pInstance;
	const cocos2d::PhysicsMaterial DEFAULT_PHYSICS_MATERIAL = cocos2d::PhysicsMaterial(0.1f, 0.1f, 0.3f);
	const int CONTACT_COLLISION_MASK = 0xFFFFFFFF;
	std::vector<PhysicsContactListener> m_contactListeners;
};