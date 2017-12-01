#include <limits>
#include "StaticBackground.h"
#include "Physics/PhysicsManager.h"
#include "GameConsts.h"
#include "extensions/physics-nodes/CCPhysicsSprite.h"

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
	extension::PhysicsSprite* pGround = 
		extension::PhysicsSprite::create("res/ground.png");
	
	// Set positions
	pSky->setAnchorPoint(Vec2::ZERO);
	pSky->setPosition(Vec2::ZERO);			

	// Set meta data
	pGround->setName(GROUND_NODE);

	// Add to parent
	addChild(pSky);
	addChild(pGround);

	// Create physics body
	PhysicsManager::getInstance()->addBoxColider(pGround, PhysicsBodyType::KINEMATIC, 
		FLT_MAX);
	pGround->setPosition(Vec2(200, 0));

	return pSky != nullptr && pGround != nullptr;
}