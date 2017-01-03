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
cocos2d::Sprite* Brick::getSprite() const 
{
	return m_BrickSprite;
}