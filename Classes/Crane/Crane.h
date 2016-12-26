#pragma once

#include "cocos2d.h"

class Crane
{
public:
	Crane();
	~Crane();

	bool init(cocos2d::Sprite* truckSprite, cocos2d::Sprite* ropeSprite, cocos2d::Sprite* hookSprite);
	void update(float delta);

	void startMovingCraneLeft(float driveSpeed);
	void startMovingCraneRight(float driveSpeed);
	void stopMovingCrane();

private:
	cocos2d::Sprite* m_TruckSprite;
	cocos2d::Sprite* m_RopeSprite;
	cocos2d::Sprite* m_HookSprite;
	float m_DriveSpeed;
};