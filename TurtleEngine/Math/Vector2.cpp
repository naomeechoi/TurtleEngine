#include <PrecompiledHeader.h>
#include "Vector2.h"

const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::One = Vector2(1.0f, 1.0f);
const Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
const Vector2 Vector2::Up = Vector2(0.0f, 1.0f);

std::wstring Vector2::ToString()
{
	return FormatWideString(TEXT("(%f, %f)"), x, y);
}

float Vector2::Length()
{
	return sqrtf((x * x) + (y * y));
}

float Vector2::Dot(const Vector2& other)
{
	return (x * other.x) + (y * other.y);
}

bool Vector2::Equal(const Vector2& other)
{
	return (x == other.x && y == other.y);
}

Vector2 Vector2::Normalized()
{
	float length = Length();
	return Vector2(x / length, y / length);
}

Vector2& Vector2::operator=(const Vector2& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator+(float other) const
{
	return Vector2(x + other, y + other);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	// TODO: 여기에 return 문을 삽입합니다.
}

Vector2& Vector2::operator+=(float other)
{
	// TODO: 여기에 return 문을 삽입합니다.
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2();
}

Vector2 Vector2::operator-(float other) const
{
	return Vector2();
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	// TODO: 여기에 return 문을 삽입합니다.
}

Vector2& Vector2::operator-=(float other)
{
	// TODO: 여기에 return 문을 삽입합니다.
}

Vector2 Vector2::operator*(const Vector2& other) const
{
	return Vector2();
}

Vector2 Vector2::operator*(float other) const
{
	return Vector2();
}

Vector2& Vector2::operator*=(const Vector2& other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

Vector2& Vector2::operator*=(float other)
{
	x *= other;
	y *= other;
	return *this;
}

Vector2 Vector2::operator/(const Vector2& other) const
{
	return Vector2(x / other.x, y / other.y);
}

Vector2 Vector2::operator/(float other) const
{
	return Vector2(x / other, y / other);
}

Vector2& Vector2::operator/=(const Vector2& other)
{
	x /= other.x;
	y /= other.y;
	return *this;
}

Vector2& Vector2::operator/=(float other)
{
	x /= other;
	y /= other;
	return *this;
}

bool Vector2::operator==(const Vector2& other) const
{
	return (x == other.x && y == other.y);
}

bool Vector2::operator!=(const Vector2& other) const
{
	return (x != other.x || y != other.y);
}
