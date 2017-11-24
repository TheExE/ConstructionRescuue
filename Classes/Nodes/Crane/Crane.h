#pragma once

#include "cocos2d.h"

class Crane: public cocos2d::Node
{
public:
	static Crane* create();

	bool initCrane();
	void update(float delta);
	
	void startMovingTheRope(float speed);
	void stopMovingRope();
	void startMovingCrane(float driveSpeed);	
	void stopMovingCrane();
	cocos2d::Sprite* getHookSprite() const;
	cocos2d::Sprite* getRopeSprite() const;

public:
	static const int MOVE_SPEED = 20;
	static const int HOOK_MAX_FORCE = 1000;
	static const float ROPE_MOVE_SPEED;
	const int CRANE_MASS = 5000;
	const int HOOK_MASS = 20;

private:	
	cocos2d::Sprite* m_pCraneSprite;
	cocos2d::Sprite* m_pRopeSprite;
	cocos2d::Sprite* m_pHookSprite;
	float m_DriveSpeed;
	float m_RopeMoveSpeed;
};