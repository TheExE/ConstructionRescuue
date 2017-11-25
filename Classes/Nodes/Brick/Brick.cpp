#include "Brick.h"
#include "GameConsts.h"
#include "Physics/PhysicsManager.h"

using namespace cocos2d;

Brick* Brick::create()
{
	Brick* pBrick = new (std::nothrow) Brick();
	if (pBrick && pBrick->init())
	{
		pBrick->autorelease();		
	}
	else
	{
		CC_SAFE_DELETE(pBrick);
	}
	return pBrick;
}
bool Brick::initBrick()
{
	m_pBrickSprite = Sprite::create("res/brick.png");
	m_pBrickSprite->setName(BRICK_NODE);
	addChild(m_pBrickSprite);
	setPosition(Vec2(200, 135));

	// Create physics body	
	PhysicsManager::getInstance()->addBoxColider(m_pBrickSprite, BRICK_MASS, true, true);

	return m_pBrickSprite != nullptr;
}
Sprite* Brick::getSprite() const 
{
	return m_pBrickSprite;
}