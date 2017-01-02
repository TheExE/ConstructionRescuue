#include "Brick.h"

Brick::Brick()
{

}
Brick::~Brick()
{

}
bool Brick::init(cocos2d::Sprite* pBrickSprite)
{
	m_BrickSprite = pBrickSprite;
	return true;
}