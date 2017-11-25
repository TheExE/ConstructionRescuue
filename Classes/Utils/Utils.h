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
};