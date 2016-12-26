#include "Crane.h"

Crane::Crane()
{
	m_DriveSpeed = 0;
}
Crane::~Crane()
{

}
bool Crane::init(cocos2d::Sprite* sprite)
{
	m_Sprite = sprite;

	return sprite != nullptr;
}
void Crane::update(float delta)
{
	
	m_Sprite->setPosition(m_Sprite->getPosition() +
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