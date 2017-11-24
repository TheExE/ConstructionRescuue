#pragma once

#include "cocos2d.h"

class PhysicsManager
{
public:
	static PhysicsManager* getInstance();		
	bool setContactListenerContext(cocos2d::Node* node);
	void addBoxColider(cocos2d::Sprite* pSprite, float mass, bool bIsDynamic, bool bIsGravityEnabled = false);
	void addCustomBox(cocos2d::Sprite* pSprite, cocos2d::Size size, float mass, bool bIsDynamic, bool bIsGravityEnabled = false);

private:
	PhysicsManager();
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	bool containsJoint(std::vector<cocos2d::PhysicsJoint*> joints, const char* jointTag) const;

private:
	static PhysicsManager* m_pInstance;
	const cocos2d::PhysicsMaterial DEFAULT_PHYSICS_MATERIAL = cocos2d::PhysicsMaterial(0.1f, 0.1f, 0.3f);
	const int CONTACT_COLLISION_MASK = 0xFFFFFFFF;
};