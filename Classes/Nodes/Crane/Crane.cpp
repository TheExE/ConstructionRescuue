#include "Crane.h"
#include "GameConsts.h"
#include "Physics/PhysicsManager.h"
#include "Utils/Utils.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Nodes/Panel/Panel.h"


using namespace cocos2d;

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

bool Crane::init()
{
	// First call the base class
	Node::init();

	// Load sprites
	setTexture("res/crane.png");
	m_pChainSprite = Sprite::create("res/chain.png");
	m_pMagnetSprite = Sprite::create("res/magnet.png");	

	// Create physics bodies	
	Size cranePhysicsBodySize = getContentSize();
	cranePhysicsBodySize.width *= 0.5f;
	PhysicsManager::getInstance()->addCustomBoxCollider(this,
		cranePhysicsBodySize, DYNAMIC, CRANE_MASS);	

	// Set names
	setName(CRANE_NODE);
	m_pChainSprite->setName(CHAIN_NODE);
	m_pMagnetSprite->setName(MAGNET_NODE);

	// Set correct relationships
	addChild(m_pChainSprite);
	addChild(m_pMagnetSprite); 

	// Set rope anchor in top middle to scale properly
	m_pChainSprite->setAnchorPoint(Vec2(0.5f, 1));

	// Set positions
	Vec2 craneStartPosition = Vec2(100, 100);
	setPosition(craneStartPosition);
	setAnchorPoint(Vec2(0.3f, 0.5f));	

	float localPosX = 114;
	m_pChainSprite->setPosition(Vec2(localPosX, 80)); 
	m_pMagnetSprite->setPosition(Vec2(localPosX, 32)); 

	// Set rope behind the crane truck
	int ropeOrderLayer = -1;
	m_pChainSprite->setLocalZOrder(ropeOrderLayer);

	// At begining magnet is disabled
	m_bIsMagnetEnabled = false;	

	return getTexture() != nullptr && m_pChainSprite != nullptr &&
		m_pMagnetSprite != nullptr;
}

void Crane::update(float deltaTime)
{
	moveCrane();
	moveRope(deltaTime);
	
	// Check magnet
	if(m_bIsMagnetEnabled && m_pMagnetPanel == nullptr)
	{
		m_CurTimeForMagnetCheck += deltaTime;
		if (m_CurTimeForMagnetCheck > TIME_BETWEEN_MAGNET_CHECK)
		{
			/* Cast a ray going from magnet to ground
			 * and check if panel is intersected.
			 */
			Size craneSize = getContentSize();
			Vec2 craneAchorPosition = Vec2(craneSize.width / 2,
				craneSize.height / 2);

			// Translate magnet position to world space
			Vec2 rayStartPosition = Utils::toParentPositionSpace(this,
				m_pMagnetSprite->getPosition());							

			PhysicsManager::getInstance()->
				castRay(this, rayStartPosition,
					rayStartPosition - Vec2(0, MAGNET_WORK_DISTANCE));
			m_CurTimeForMagnetCheck = 0;
		}
	}
}

void Crane::moveCrane()
{
	// Move crane using force
	b2Body* craneBody = getB2Body();
	craneBody->ApplyLinearImpulse(b2Vec2(m_DriveSpeed, 0),
		craneBody->GetWorldCenter(), true);
	b2Vec2 linearVelocity = craneBody->GetLinearVelocity();
	if (linearVelocity.x > 1)
	{
		craneBody->SetLinearVelocity(b2Vec2(1, 0));
	}
	else if (linearVelocity.x < -1)
	{
		craneBody->SetLinearVelocity(b2Vec2(-1, 0));
	}
}

void Crane::moveRope(float deltaTime)
{
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

void Crane::moveCraneRight()
{
	m_DriveSpeed = MOVE_SPEED;
}

void Crane::moveCraneLeft()
{
	m_DriveSpeed = -MOVE_SPEED;
}

void Crane::stopMovingCrane()
{
	m_DriveSpeed = 0;
}

void Crane::moveChainUp()
{
	m_ChainMoveSpeed = -CHAIN_MOVE_SPEED;	// Reducing the scale
}

void Crane::moveChainDown()
{
	m_ChainMoveSpeed = CHAIN_MOVE_SPEED;
}

void Crane::stopMovingRope()
{
	m_ChainMoveSpeed = 0;
}

void Crane::toggleMagnet()
{
	m_bIsMagnetEnabled = !m_bIsMagnetEnabled;
	

	// Debug info
	if(m_bIsMagnetEnabled)
	{
		cocos2d::log("Crane: Magnet enabled !");
	}
	else
	{
		cocos2d::log("Crane: Magnet disabled !");

		// Drop the panel
		if(m_pMagnetPanel != nullptr)
		{
			m_pMagnetPanel->detachFromMagnet();
			m_pMagnetPanel = nullptr;
		}
	}
}

float32 Crane::ReportFixture(b2Fixture* fixture, const b2Vec2& point,
	const b2Vec2& normal, float32 fraction)
{
	// Check if ray intersected with panel object
	Panel* pPanel = (Panel*)fixture->GetBody()->GetUserData();
	
	if(pPanel != nullptr)
	{
		/* If magnet is enabled and ray intersected with 
		 * panel then attach the panel to magnet.
		 */
		const char* otherBodyName = pPanel->getName().c_str();
		Vec2 magnetPosInParentSpace = Utils::toParentPositionSpace(this,
			m_pMagnetSprite->getPosition());
		float distance = magnetPosInParentSpace.distance(pPanel->getPosition());

		if (strcmp(otherBodyName, PANEL_NODE) == 0 &&
			distance <= MAGNET_WORK_DISTANCE && m_pMagnetPanel == nullptr)
		{
			cocos2d::log("Ray cast hit the panel !");
			pPanel->attachToMagnet(m_pMagnetSprite);
			m_pMagnetPanel = pPanel;
		}
	}
	
	// Return 0 terminates raycast
	return 0;
}