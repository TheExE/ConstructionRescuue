#pragma once

#include "cocos2d.h"

class Crane
{
public:
	Crane();
	~Crane();

	bool init(cocos2d::Sprite* sprite);
	void update(float delta);

	void startMovingCraneLeft(float driveSpeed);
	void startMovingCraneRight(float driveSpeed);
	void stopMovingCrane();

private:
	cocos2d::Sprite* m_Sprite;
	float m_DriveSpeed;
};