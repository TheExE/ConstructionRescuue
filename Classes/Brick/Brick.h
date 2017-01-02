#pragma once

#include "cocos2d.h"

class Brick
{
public:
	Brick();
	~Brick();
	bool init(cocos2d::Sprite* pBrickSprite);

private:
	cocos2d::Sprite* m_BrickSprite;
};