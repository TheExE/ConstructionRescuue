#pragma once

#include "cocos2d.h"

class HelloWorld;


class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();
	bool init(HelloWorld* mainScene);
	void addBoxColider(cocos2d::Sprite* pSprite, bool bIsDynamic);

private:
	bool onContactBegin(cocos2d::PhysicsContact& contact);

};