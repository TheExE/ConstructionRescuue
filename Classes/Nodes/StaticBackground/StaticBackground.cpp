#include "StaticBackground.h"
#include "Physics/PhysicsManager.h"

using namespace cocos2d;

StaticBackground* StaticBackground::create()
{
	StaticBackground * ret = new (std::nothrow) StaticBackground();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool StaticBackground::initStaticBackground()
{
	// Load sprites
	Sprite* pSky = Sprite::create("res/sky.png");
	Sprite* pGround = Sprite::create("res/ground.png");
	
	// Set positions
	pSky->setAnchorPoint(Vec2::ZERO);
	pSky->setPosition(Vec2::ZERO);
	pGround->setAnchorPoint(Vec2::ZERO);
	pGround->setPosition(Vec2::ZERO);

	// Add to parent
	addChild(pSky);
	addChild(pGround);

	// Create physics body
	PhysicsManager::getInstance()->addBoxColider(pGround, PHYSICS_INFINITY, false);

	return pSky != nullptr && pGround != nullptr;
}