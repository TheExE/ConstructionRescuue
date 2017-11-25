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
	Sprite* pButtonAction = Sprite::create("res/actionButton.png");

	// Set correct rotations
	pButtonDown->setRotation(180);
	pButtonLeft->setRotation(-90);
	pButtonRight->setRotation(90);

	// Set names
	pButtonUp->setName(BUTTON_UP);
	pButtonDown->setName(BUTTON_DOWN);
	pButtonLeft->setName(BUTTON_LEFT);
	pButtonRight->setName(BUTTON_RIGHT);
	pButtonAction->setName(BUTTON_ACTION);

	// Add buttons to parent
	addChild(pButtonUp);
	addChild(pButtonDown);
	addChild(pButtonLeft);
	addChild(pButtonRight);
	addChild(pButtonAction);

	// Set positions
	Size windowSize = Director::getInstance()->getWinSize();
	Size buttonSize = pButtonUp->getContentSize();
	float buttonPositionX = windowSize.width - (buttonSize.width * 4);
	pButtonUp->setPosition(Vec2(buttonPositionX + buttonSize.width,
		buttonSize.height * 3));
	pButtonDown->setPosition(Vec2(buttonPositionX + buttonSize.width, buttonSize.height));
	pButtonLeft->setPosition(Vec2(buttonPositionX, buttonSize.height * 2));
	pButtonRight->setPosition(Vec2(buttonPositionX + buttonSize.width * 2,
		buttonSize.height * 2));
	Size actionButtonSize = pButtonAction->getContentSize();
	pButtonAction->setAnchorPoint(Vec2(0, 0));
	pButtonAction->setPosition(Vec2(actionButtonSize.width, actionButtonSize.height / 2));

	return pButtonUp != nullptr && pButtonDown != nullptr && pButtonLeft != nullptr && pButtonRight != nullptr;
}