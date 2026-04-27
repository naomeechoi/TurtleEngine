#pragma once
#include <CommonDefine.h>

class Vector3
{
public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vector3() = default;
	Vector3(float value)
		: x(value), y(value), z(value) { }
	Vector3(float x, float y, float z)
		: x(x), y(y), z(z) {
	}
	Vector3(const Vector3& other)
		: x(other.x), y(other.y), z(other.z) {
	}

	static uint32 Stride() { return sizeof(float) * 3; }

	static const Vector3 Zero;
	static const Vector3 One;
	static const Vector3 Right;
	static const Vector3 Up;
	static const Vector3 Forward;
};

