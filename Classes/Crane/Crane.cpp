#include "Crane.h"

const float Crane::ROPE_MOVE_SPEED = 5.2f;

Crane::Crane()
{
	m_DriveSpeed = 0;
	m_RopeMoveSpeed = 0;
}
Crane::~Crane()
{

}
bool Crane::init(cocos2d::Sprite* truckSprite, cocos2d::Sprite* ropeSprite, cocos2d::Sprite* hookSprite)
{
	m_TruckSprite = truckSprite;
	m_RopeSprite = ropeSprite;
	m_HookSprite = hookSprite;

	// Set rope behind the crane truck
	m_RopeSprite->setLocalZOrder(-1);
	m_RopeSprite->setGlobalZOrder(-1);


	return truckSprite != nullptr && ropeSprite != nullptr && hookSprite != nullptr;
}

void Crane::update(float deltaTime)
{
	// Move crane
	m_TruckSprite->setPosition(m_TruckSprite->getPosition() +
		cocos2d::Vec2(m_DriveSpeed*deltaTime, 0));

	// Move rope
	m_RopeSprite->setScaleY(m_RopeSprite->getScaleY() + m_RopeMoveSpeed * deltaTime);
	m_HookSprite->setPositionY(m_RopeSprite->getContentSize().height*178
		+ m_RopeSprite->getContentSize().height * -m_RopeSprite->getScaleY());
}

void Crane::startMovingCraneLeft(float driveSpeed)
{
	m_DriveSpeed = driveSpeed;
}

void Crane::startMovingCraneRight(float driveSpeed)
{
	m_DriveSpeed = driveSpeed;
}

void Crane::stopMovingCrane()
{
	m_DriveSpeed = 0;
}

void Crane::startLoweringRope()
{
	m_RopeMoveSpeed = ROPE_MOVE_SPEED;
}

void Crane::startAscendingRope()
{
	m_RopeMoveSpeed = -ROPE_MOVE_SPEED;
}

void Crane::stopMovingRope()
{
	m_RopeMoveSpeed = 0;
}

cocos2d::Sprite* Crane::getHookSprite() const
{
	return m_HookSprite;
}
cocos2d::Sprite* Crane::getRopeSprite() const
{
	return m_RopeSprite;
}