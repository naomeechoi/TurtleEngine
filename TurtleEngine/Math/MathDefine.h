#pragma once
#include "PrecompiledHeader.h"
#include <cmath>

namespace Math
{
	constexpr float PI = 3.14159265f;
	constexpr float Deg2Rad = (PI / 180.0f);
	constexpr float Rad2Deg = (180.0f / PI);
	FORCEINLINE float Lerpf(float a, float b, float alpha)
	{
#if _DEBUG
		alpha = std::clamp(alpha, 0.0f, 1.0f);
#else
		if (alpha > 1.0f)
		{
			alpha = 1.0f;
		}
		else if (alpha < 0.0f)
		{
			alpha = 0.0f;
		}
#endif

		return (1 - alpha) * a + alpha * b;
	}
};