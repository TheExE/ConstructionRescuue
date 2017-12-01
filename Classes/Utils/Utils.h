#pragma once

namespace Utils
{
	/*
	 * Returns the given value clamped in min, max value range.
	 */
	template <typename  T>
	static T clampValue(const T& value, const T& minValue, const T& maxValue)
	{
		T newValue(value);
		if(value < minValue)
		{
			newValue = minValue;
		}
		else if(value > maxValue)
		{
			newValue = maxValue;
		}
		return newValue;
	}

	/*
	 * Logs cocos2d vector.
	 */
	static void logVec2(const cocos2d::Vec2& position)
	{
		cocos2d::log("X:%f, Y:%f", position.x, position.y);
	}

	/*
	 * Function returns given position
	 * transformed in parent space.
	 */
	static cocos2d::Vec2 toParentPositionSpace(const cocos2d::Node* parent, const cocos2d::Vec2& childPos)
	{
		cocos2d::Size size = parent->getContentSize();
		cocos2d::Vec2 achorPercentage = parent->getAnchorPoint();
		cocos2d::Vec2 achorPoint = cocos2d::Vec2(size.width * achorPercentage.x, 
			size.height * achorPercentage.y);
		return parent->getPosition() - achorPoint + childPos;
	}
};