#pragma once

#include "../Math/Vector3.h"
#include "../Math/Vector2.h"
#include "../Math/Color.h"

class Vertex
{
public:
	Vertex()
	{
	}

	Vertex(const Vector3& position)
		: position(position)
	{
	}

	Vertex(const Vector3& position, const Vector2& uv, const Color& color)
		: position(position), uv(uv), color(color)
	{
	}

	Vertex(const Vector3& position, const Vector2& uv, const Color& color, const Vector3& normal)
		: position(position), uv(uv), color(color), normal(normal)
	{
	}

	static unsigned int Stride() { return sizeof(Vector3) + sizeof(Vector2) + sizeof(Color) + sizeof(Vector3); }

public:
	Vector3 position = Vector3::Zero;
	Vector2 uv = Vector2::Zero;
	Color color = Color::White;
	Vector3 normal = Vector3::One;
};