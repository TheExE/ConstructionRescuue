#include "Crane.h"

Crane::Crane()
{
	m_DriveSpeed = 0;
}
Crane::~Crane()
{

}
bool Crane::init(cocos2d::Sprite* truckSprite, cocos2d::Sprite* ropeSprite, cocos2d::Sprite* hookSprite)
{
	m_TruckSprite = truckSprite;
	m_RopeSprite = ropeSprite;
	m_HookSprite = hookSprite;

	// Set behind the crane truck
	m_RopeSprite->setLocalZOrder(0);

	return truckSprite != nullptr && ropeSprite != nullptr && hookSprite != nullptr;
}

void Crane::update(float delta)
{
	m_TruckSprite->setPosition(m_TruckSprite->getPosition() +
		cocos2d::Vec2(m_DriveSpeed*delta, 0));
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