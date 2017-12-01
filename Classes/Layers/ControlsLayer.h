#pragma once

#include "cocos2d.h"

class ControlsLayer : public cocos2d::Layer
{
	public:
		static ControlsLayer* create();
		bool initControlsLayer();				
};