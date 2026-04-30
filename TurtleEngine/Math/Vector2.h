#pragma once

class Vector2
{
public:
	float x = 0.0f;
	float y = 0.0f;

	Vector2()
		: x(0.0f), y(0.0f)
	{
	}

	Vector2(float value)
		: x(value), y(value)
	{
	}

	Vector2(float x, float y)
		: x(x), y(y)
	{
	}

	Vector2(const Vector2& other)
		: x(other.x), y(other.y)
	{
	}

	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 Right;
	static const Vector2 Up;

	std::wstring ToString();
	float Length();
	float Dot(const Vector2& other);
	bool Equal(const Vector2& other);
	Vector2 Normalized();

	Vector2& operator=(const Vector2& other);

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator+(float other) const;
	Vector2& operator+=(const Vector2& other);
	Vector2& operator+=(float other);

	Vector2 operator-(const Vector2& other) const;
	Vector2 operator-(float other) const;
	Vector2& operator-=(const Vector2& other);
	Vector2& operator-=(float other);

	Vector2 operator*(const Vector2& other) const;
	Vector2 operator*(float other) const;
	Vector2& operator*=(const Vector2& other);
	Vector2& operator*=(float other);

	Vector2 operator/(const Vector2& other) const;
	Vector2 operator/(float other) const;
	Vector2& operator/=(const Vector2& other);
	Vector2& operator/=(float other);

	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;
};
