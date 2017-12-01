#include "Panel.h"
#include "GameConsts.h"
#include "Physics/PhysicsManager.h"
#include "Utils/Utils.h"

using namespace cocos2d;

Panel* Panel::create()
{
	Panel* pPanel = new (std::nothrow) Panel();
	if (pPanel && pPanel->init())
	{
		pPanel->autorelease();		
	}
	else
	{
		CC_SAFE_DELETE(pPanel);
	}
	return pPanel;
}
bool Panel::init()
{
	Node::init();
	setTexture("res/panel.png");
	setName(PANEL_NODE);		
	setAnchorPoint(Vec2(0.5f, 0.5f));

	// Create physics body	
	Size size = getContentSize();
	size.width *= 0.95f;
	size.height *= 0.75f;
	PhysicsManager::getInstance()->addCustomBoxCollider(this, size, DYNAMIC, 
		PANEL_MASS);	
	setPosition(Vec2(300, 150));

	// Set default value
	m_bIsAnimating = false;

	return getTexture() != nullptr;
}

void Panel::attachToMagnet(Sprite* pMagnetSprite)
{
	m_pMagnet = pMagnetSprite;
	m_OffsetFromMagnet = Vec2(0, m_pMagnet->getContentSize().height * 2);

	// When magnet takes posesion of this panel disable physics
	getB2Body()->SetActive(false);
	
	// Animate panel flying to magnet	
	FiniteTimeAction* callBack = CallFunc::create(CC_CALLBACK_0(Panel::disableAnimation,
		this));
	FiniteTimeAction* moveToMagnet = MoveTo::create(FLY_ANIMATION_TIME,
		Utils::toParentPositionSpace(pMagnetSprite->getParent(),
		pMagnetSprite->getPosition()) - m_OffsetFromMagnet);

	Vector<FiniteTimeAction*> actionsToPerform;
	actionsToPerform.pushBack(moveToMagnet);
	actionsToPerform.pushBack(callBack);
	Sequence* actionSequence = Sequence::create(actionsToPerform);
	
	runAction(actionSequence);
	m_bIsAnimating = true;
}

void Panel::detachFromMagnet()
{
	m_pMagnet = nullptr;

	// Return control to physics
	getB2Body()->SetActive(true);
}

void Panel::disableAnimation()
{
	m_bIsAnimating = false;
}

void Panel::update(float deltaTime)
{
	if(m_pMagnet != nullptr && !m_bIsAnimating)
	{
		// Make this panel fallow magnet
		Vec2 magnetPosInWorld = Utils::toParentPositionSpace(m_pMagnet->getParent(),
			m_pMagnet->getPosition());
		setPosition(magnetPosInWorld - m_OffsetFromMagnet);
	}
}