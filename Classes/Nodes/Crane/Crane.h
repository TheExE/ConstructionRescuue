#pragma once

#include "cocos2d.h"

struct PhysicsContactInformation;

class Crane: public cocos2d::Node
{
public:
	static Crane* create();

	bool initCrane();
	void update(float deltaTime);
	
	void startMovingTheRope(float speed);
	void stopMovingRope();
	void startMovingCrane(float driveSpeed);	
	void stopMovingCrane();
	void toggleMagnet();	

private:
	bool onPhysicsContact(PhysicsContactInformation& contact);	

public:
	static const int MOVE_SPEED = 20;
	static const int MAGNET_MAX_FORCE = 5000000;
	static const float CHAIN_MOVE_SPEED;
	const int CRANE_MASS = 5000;
	const int MAGNET_MASS = 200;
	const float MIN_ROPE_SCALE_Y = 0.5f;
	const float MAX_ROPE_SCALE_Y = 1.36f;

private:	
	cocos2d::PhysicsJoint* m_MagnetJoint;
	cocos2d::Sprite* m_pCraneSprite;
	cocos2d::Sprite* m_pChainSprite;
	cocos2d::Sprite* m_pMagnetSprite;
	float m_DriveSpeed;
	float m_ChainMoveSpeed;
	bool m_bIsMagnetEnabled;
};