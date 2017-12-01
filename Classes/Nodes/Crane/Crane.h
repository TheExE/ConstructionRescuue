#pragma once

#include "cocos2d.h"
#include "extensions/physics-nodes/CCPhysicsSprite.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "Nodes/Panel/Panel.h"

class Crane: public cocos2d::extension::PhysicsSprite, b2RayCastCallback
{
public:
	static Crane* create();

	bool init();
	void update(float deltaTime);
	
	void moveChainUp();
	void moveChainDown();
	void stopMovingRope();

	void moveCraneRight();	
	void moveCraneLeft();
	void stopMovingCrane();
	
	void toggleMagnet();	

private:
	bool onRaycastHit(cocos2d::PhysicsWorld& world,
		const cocos2d::PhysicsRayCastInfo& info, void* data);
	void moveCrane();
	void moveRope(float deltaTime);

	virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float32 fraction) override;

public:	
	const int MAGNET_MAX_FORCE = 5000000;
	const int CRANE_MASS = 5000;
	const int MAGNET_MASS = 500;
	const float MOVE_SPEED = 0.01f;
	const float CHAIN_MOVE_SPEED = 0.2f;
	const float MIN_ROPE_SCALE_Y = 0.8f;
	const float MAX_ROPE_SCALE_Y = 1.36f;
	const float TIME_BETWEEN_MAGNET_CHECK = 1.5f;
	const float MAGNET_WORK_DISTANCE = 20;	

private:			
	Sprite* m_pChainSprite;
	Sprite* m_pMagnetSprite;
	Panel* m_pMagnetPanel;
	float m_DriveSpeed;
	float m_ChainMoveSpeed;
	float m_CurTimeForMagnetCheck;
	bool m_bIsMagnetEnabled;		
};
