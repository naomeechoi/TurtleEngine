#include <PrecompiledHeader.h>
#include "Vector3.h"

const Vector3 Vector3::Zero = { 0.0f, 0.0f, 0.0f };
const Vector3 Vector3::One = { 1.0f, 1.0f, 1.0f };
const Vector3 Vector3::Right = { 1.0f, 0.0f, 0.0f };
const Vector3 Vector3::Up = { 0.0f, 1.0f, 0.0f };
const Vector3 Vector3::Forward = { 0.0f, 0.0f, 1.0f };

std::string Vector3::ToString()
{
	return FormatString("(%f, %f, %f)", x, y, z);
}

std::wstring Vector3::ToWideString()
{
	return FormatWideString(TEXT("(%f, %f, %f)"), x, y, z);
}

Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
{
	return a * (1 - t) + b * t;
}

float Vector3::Length() const
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

float Vector3::Dot(const Vector3& other) const
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}

Vector3 Vector3::Normalized() const
{
	float length = Length();
	return Vector3(x / length, y / length, z / length);
}


Vector3 Vector3::Cross(const Vector3& other) const
{
	return Vector3(
		y * other.z - z * other.y,
		-x * other.z + z * other.x,
		x * other.y - y * other.x
	);
}


bool Vector3::Equal(const Vector3& other) const
{
	return (x == other.x && y == other.y && z == other.z);
}

Vector3& Vector3::operator=(const Vector3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator+(const float& other) const
{
	return Vector3(x + other, y + other, z + other);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3& Vector3::operator+=(const float& other)
{
	x += other;
	y += other;
	z += other;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator-(const float& other) const
{
	return Vector3(x - other, y - other, z - other);
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3& Vector3::operator-=(const float& other)
{
	x -= other;
	y -= other;
	z -= other;
	return *this;
}

Vector3 Vector3::operator*(const Vector3& other) const
{
	return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator*(const float& other) const
{
	return Vector3(x * other, y * other, z * other);
}

Vector3& Vector3::operator*=(const Vector3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

Vector3& Vector3::operator*=(const float& other)
{
	x *= other;
	y *= other;
	z *= other;
	return *this;
}

Vector3 Vector3::operator/(const Vector3& other) const
{
	return Vector3(x / other.x, y / other.y, z / other.z);
}

Vector3 Vector3::operator/(const float& other) const
{
	return Vector3(x / other, y / other, z / other);
}

Vector3& Vector3::operator/=(const Vector3& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

Vector3& Vector3::operator/=(const float& other)
{
	x /= other;
	y /= other;
	z /= other;
	return *this;
}

bool Vector3::operator==(const Vector3& other) const
{
	return (x == other.x && y == other.y && z == other.z);
}

bool Vector3::operator!=(const Vector3& other) const
{
	return (x != other.x || y != other.y || z != other.z);
}
