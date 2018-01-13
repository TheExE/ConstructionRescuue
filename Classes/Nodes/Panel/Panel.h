#pragma once

#include "cocos2d.h"
#include "extensions/physics-nodes/CCPhysicsSprite.h"
class Panel : public cocos2d::extension::PhysicsSprite
{
public:
	static Panel* create();
	bool init() override;
	void attachToMagnet(cocos2d::Sprite* pMagnetSprite);
	void detachFromMagnet();
	void update(float deltaTime);

private:
	void disableAnimation();

public:
	const int PANEL_MASS = 25;
	const float FLY_ANIMATION_TIME = 0.3f; // TODO: Replace with speed based on distance

private:
	Sprite* m_pMagnet;
	cocos2d::Vec2 m_OffsetFromMagnet;
	bool m_bIsAnimating;
};