#include "Crane.h"
#include "GameConsts.h"
#include "Physics/PhysicsManager.h"

using namespace cocos2d;

const float Crane::ROPE_MOVE_SPEED = 5.2f;

Crane* Crane::create()
{
	Crane* pCrane = new (std::nothrow) Crane();
	if (pCrane && pCrane->init())
	{
		pCrane->autorelease();
		pCrane->m_DriveSpeed = 0;
		pCrane->m_RopeMoveSpeed = 0;
	}
	else
	{
		CC_SAFE_DELETE(pCrane);
	}
	return pCrane;
}

bool Crane::initCrane()
{
	// Load sprites
	m_pCraneSprite = Sprite::create("res/crane.png");
	m_pRopeSprite = Sprite::create("res/rope.png");
	m_pHookSprite = Sprite::create("res/hook.png");

	// Set names
	m_pCraneSprite->setName(CRANE_NODE);
	m_pRopeSprite->setName(ROPE_NODE);
	m_pHookSprite->setName(HOOK_NODE);

	// Set correct relationships
	m_pCraneSprite->addChild(m_pRopeSprite);
	m_pCraneSprite->addChild(m_pHookSprite);
	addChild(m_pCraneSprite);

	// Set positions
	Vec2 craneStartPosition = Vec2(100, 135);
	setPosition(craneStartPosition);
	
	int ropeRelativeX = 114;
	m_pRopeSprite->setPosition(Vec2(ropeRelativeX, 55));
	m_pHookSprite->setPosition(Vec2(ropeRelativeX, 30));

	// Set rope behind the crane truck
	int ropeOrderLayer = -1;
	m_pRopeSprite->setLocalZOrder(ropeOrderLayer);

	// Create physics bodies	
	Size cranePhysicsBodySize = m_pCraneSprite->getContentSize();
	cranePhysicsBodySize.width -= cranePhysicsBodySize.width / 1.37f;
	PhysicsManager::getInstance()->addCustomBox(m_pCraneSprite, cranePhysicsBodySize,
		CRANE_MASS, true, true);
	
	Size hookPhysicsBodySize = m_pHookSprite->getContentSize();
	hookPhysicsBodySize.height = hookPhysicsBodySize.height / 2.f;
	PhysicsManager::getInstance()->addCustomBox(m_pHookSprite, hookPhysicsBodySize,
		HOOK_MASS, false);

	return m_pCraneSprite != nullptr && m_pRopeSprite != nullptr &&
		m_pHookSprite != nullptr;
}

void Crane::update(float deltaTime)
{
	// Move crane
	Vec2 currenCranePosition = m_pCraneSprite->getPosition();
	m_pCraneSprite->setPosition(currenCranePosition + Vec2(m_DriveSpeed * deltaTime, 0));

	// Move rope
	float currentRopeScaleY = m_pRopeSprite->getScaleY();
	m_pRopeSprite->setScaleY(currentRopeScaleY + m_RopeMoveSpeed * deltaTime);
	m_pHookSprite->setPositionY(m_pRopeSprite->getContentSize().height
		- m_pRopeSprite->getContentSize().height * currentRopeScaleY);
}

void Crane::startMovingCrane(float driveSpeed)
{
	m_DriveSpeed = driveSpeed;
}

void Crane::stopMovingCrane()
{
	m_DriveSpeed = 0;
}

void Crane::startMovingTheRope(float speed)
{
	m_RopeMoveSpeed = speed;
}

void Crane::stopMovingRope()
{
	m_RopeMoveSpeed = 0;
}

cocos2d::Sprite* Crane::getHookSprite() const
{
	return m_pHookSprite;
}
cocos2d::Sprite* Crane::getRopeSprite() const
{
	return m_pRopeSprite;
}