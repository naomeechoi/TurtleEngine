#pragma once
#include <CommonDefine.h>

class Quaternion;
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

	std::string ToString();
	std::wstring ToWideString();

	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

	float Length() const;
	float Dot(const Vector3& other) const;
	Vector3 Normalized() const;
	Vector3 Cross(const Vector3& other) const;

	// TODO: Quaternion
	//Quaternion ToQuaternion();

	bool Equal(const Vector3& other) const;

	Vector3& operator=(const Vector3& other);

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator+(const float& other) const;
	Vector3& operator+=(const Vector3& other);
	Vector3& operator+=(const float& other);

	Vector3 operator-(const Vector3& other) const;
	Vector3 operator-(const float& other) const;
	Vector3& operator-=(const Vector3& other);
	Vector3& operator-=(const float& other);

	Vector3 operator*(const Vector3& other) const;
	Vector3 operator*(const float& other) const;
	Vector3& operator*=(const Vector3& other);
	Vector3& operator*=(const float& other);

	Vector3 operator/(const Vector3& other) const;
	Vector3 operator/(const float& other) const;
	Vector3& operator/=(const Vector3& other);
	Vector3& operator/=(const float& other);

	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
};

