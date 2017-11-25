#include "Crane.h"
#include "GameConsts.h"
#include "Physics/PhysicsManager.h"
#include "Utils/Utils.h"


using namespace cocos2d;

const float Crane::CHAIN_MOVE_SPEED = 0.2f;

Crane* Crane::create()
{
	Crane* pCrane = new (std::nothrow) Crane();
	if (pCrane && pCrane->init())
	{
		pCrane->autorelease();
		pCrane->m_DriveSpeed = 0;
		pCrane->m_ChainMoveSpeed = 0;
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
	m_pChainSprite = Sprite::create("res/chain.png");
	m_pMagnetSprite = Sprite::create("res/magnet.png");

	// Set names
	m_pCraneSprite->setName(CRANE_NODE);
	m_pChainSprite->setName(CHAIN_NODE);
	m_pMagnetSprite->setName(MAGNET_NODE);

	// Set correct relationships
	m_pCraneSprite->addChild(m_pChainSprite);
	m_pCraneSprite->addChild(m_pMagnetSprite);
	addChild(m_pCraneSprite);

	// Set rope anchor in top middle to scale properly
	m_pChainSprite->setAnchorPoint(Vec2(0.5f, 1));

	// Set positions
	Vec2 craneStartPosition = Vec2(100, 135);
	setPosition(craneStartPosition);
	
	int ropeRelativeX = 114;
	m_pChainSprite->setPosition(Vec2(ropeRelativeX, 80));
	m_pMagnetSprite->setPosition(Vec2(ropeRelativeX, 32));

	// Set rope behind the crane truck
	int ropeOrderLayer = -1;
	m_pChainSprite->setLocalZOrder(ropeOrderLayer);

	// Create physics bodies	
	Size cranePhysicsBodySize = m_pCraneSprite->getContentSize();
	cranePhysicsBodySize.width -= cranePhysicsBodySize.width / 1.37f;
	PhysicsManager::getInstance()->addCustomBox(m_pCraneSprite, cranePhysicsBodySize,
		CRANE_MASS, true, true);
	
	Size hookPhysicsBodySize = m_pMagnetSprite->getContentSize();
	hookPhysicsBodySize.height = hookPhysicsBodySize.height / 2.f;
	PhysicsManager::getInstance()->addCustomBox(m_pMagnetSprite, hookPhysicsBodySize,
		MAGNET_MASS, false);

	// Set contact listener
	PhysicsManager::getInstance()->
	addContactListener(MAGNET_NODE, CC_CALLBACK_1(Crane::onPhysicsContact, this));

	// At begining magnet is disabled
	m_bIsMagnetEnabled = false;

	return m_pCraneSprite != nullptr && m_pChainSprite != nullptr &&
		m_pMagnetSprite != nullptr;
}

void Crane::update(float deltaTime)
{
	// Move crane
	Vec2 currenCranePosition = m_pCraneSprite->getPosition();
	m_pCraneSprite->setPosition(currenCranePosition + Vec2(m_DriveSpeed * deltaTime, 0));

	// Move rope	
	m_pChainSprite->setScaleY(m_pChainSprite->getScaleY() + m_ChainMoveSpeed * deltaTime);
	
	// Make sure the scale is in valid range
	float currentRopeScaleY = m_pChainSprite->getScaleY();
	currentRopeScaleY = Utils::clampValue(currentRopeScaleY, MIN_ROPE_SCALE_Y,
		MAX_ROPE_SCALE_Y);
	m_pChainSprite->setScaleY(currentRopeScaleY);

	// Finally set magnets position at the end of the chain (in cocos y is up)
	Size chainSize = m_pChainSprite->getContentSize();	
	m_pMagnetSprite->setPositionY(m_pChainSprite->getPositionY() - 
		chainSize.height * currentRopeScaleY);
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
	m_ChainMoveSpeed = speed;
}

void Crane::stopMovingRope()
{
	m_ChainMoveSpeed = 0;
}

void Crane::toggleMagnet()
{
	m_bIsMagnetEnabled = !m_bIsMagnetEnabled;
	
	if(!m_bIsMagnetEnabled && m_MagnetJoint != nullptr)
	{
		// Magnet disabled - remove the joint
		m_MagnetJoint->removeFormWorld();
		m_MagnetJoint = nullptr;
	}

	// Debug info
	if(m_bIsMagnetEnabled)
	{
		cocos2d::log("Crane: Magnet enabled !");
	}
	else
	{
		cocos2d::log("Crane: Magnet disabled !");
	}
}

bool Crane::onPhysicsContact(PhysicsContactInformation& contact)
{
	PhysicsBody* pMagnetBody = contact.pListenerShape;
	PhysicsBody* pOtherBody = contact.pTheOtherShape;

	// If magnet is enabled and it collided with brick then attach the brick to magnet
	const char* otherBodyName = pOtherBody->getNode()->getName().c_str();	
	if (strcmp(otherBodyName, BRICK_NODE) == 0)
	{
		if (m_bIsMagnetEnabled && m_MagnetJoint == nullptr)
		{			
			m_MagnetJoint = PhysicsJointFixed::construct(pMagnetBody, pOtherBody,
				pMagnetBody->getNode()->getPosition() - Vec2(0, m_pMagnetSprite->getContentSize().height/2));
			m_MagnetJoint->setEnable(true);			
			m_MagnetJoint->setMaxForce(MAGNET_MAX_FORCE);			
			m_MagnetJoint->setTag(*MAGNET_JOINT);
			pMagnetBody->getWorld()->addJoint(m_MagnetJoint);	
			pOtherBody->setVelocity(Vec2::ZERO);
		}
	}
	return true;
}