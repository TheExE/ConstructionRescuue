#pragma once

#include "../HelloWorldScene.h"

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();
	bool init(HelloWorld* mainScene);


private:
	bool onContactBegin(cocos2d::PhysicsContact& contact);

};