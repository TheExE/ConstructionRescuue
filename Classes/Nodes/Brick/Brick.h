#pragma once

#include "cocos2d.h"

class Brick: public cocos2d::Node
{
public:
	static Brick* create();
	bool initBrick();	
	cocos2d::Sprite* getSprite() const;

public:
	const int BRICK_MASS = 50;
	
private:
	cocos2d::Sprite* m_pBrickSprite;
};