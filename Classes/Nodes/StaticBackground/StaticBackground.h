#pragma once

#include "cocos2d.h"

class StaticBackground: public cocos2d::Node
{
	public:
		static StaticBackground* create();
		bool initStaticBackground();
};