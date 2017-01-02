#pragma once

#include "cocos2d.h"

class HelloWorld;


class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();
	bool init(HelloWorld* mainScene);
	void addBoxColider(cocos2d::Sprite* pSprite, bool bIsDynamic, bool bIsGravityEnabled = false);
	void addCustomBox(cocos2d::Sprite* pSprite, cocos2d::Size size, bool bIsDynamic, bool bIsGravityEnabled = false);

private:
	bool onContactBegin(cocos2d::PhysicsContact& contact);

};