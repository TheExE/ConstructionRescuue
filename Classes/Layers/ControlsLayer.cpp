#include "ControlsLayer.h"
#include "GameConsts.h"

using namespace cocos2d;

ControlsLayer* ControlsLayer::create()
{
	ControlsLayer* pLayer = new (std::nothrow) ControlsLayer();
	if (pLayer && pLayer->init())
	{
		pLayer->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pLayer);
	}
	return pLayer;
}

bool ControlsLayer::initControlsLayer()
{
	// Load sprites
	Sprite* pButtonUp = Sprite::create("res/arrow.png");
	Sprite* pButtonDown = Sprite::create("res/arrow.png");
	Sprite* pButtonLeft = Sprite::create("res/arrow.png");
	Sprite* pButtonRight = Sprite::create("res/arrow.png");

	// Set correct rotations
	pButtonDown->setRotation(180);
	pButtonLeft->setRotation(-90);
	pButtonRight->setRotation(90);

	// Set names
	pButtonUp->setName(BUTTON_UP);
	pButtonDown->setName(BUTTON_DOWN);
	pButtonLeft->setName(BUTTON_LEFT);
	pButtonRight->setName(BUTTON_RIGHT);

	// Add buttons to parent
	addChild(pButtonUp);
	addChild(pButtonDown);
	addChild(pButtonLeft);
	addChild(pButtonRight);

	// Set positions
	Size buttonSize = pButtonUp->getContentSize();
	pButtonUp->setPosition(Vec2(buttonSize.width, buttonSize.height*2));
	pButtonDown->setPosition(Vec2(buttonSize.width, 0));
	pButtonLeft->setPosition(Vec2(0, buttonSize.height));
	pButtonRight->setPosition(Vec2(buttonSize.width*2, buttonSize.height));

	Size windowSize = Director::getInstance()->getWinSize();
	setPosition(windowSize.width - (buttonSize.width * 4), buttonSize.height/2);

	return pButtonUp != nullptr && pButtonDown != nullptr && pButtonLeft != nullptr && pButtonRight != nullptr;
}