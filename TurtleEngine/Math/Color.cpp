#include "PrecompiledHeader.h"
#include "Color.h"

const Color Color::White = Color(1.0f, 1.0f, 1.0f, 1.0f);
const Color Color::Yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);
const Color Color::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::Gray = Color(0.5f, 0.5f, 0.5f, 1.0f);
const Color Color::Magenta = Color(1.0f, 1.0f, 0.0f, 1.0f);
const Color Color::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::Green = Color(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);

Color& Color::operator=(const Color& other)
{
	rgba[0] = other.rgba[0];
	rgba[1] = other.rgba[1];
	rgba[2] = other.rgba[2];
	rgba[3] = other.rgba[3];

	return *this;
}

Color Color::operator+(const Color& other) const
{
	return Color(
		red + other.red,
		green + other.green,
		blue + other.blue,
		alpha + other.alpha
	);
}

Color Color::operator-(const Color& other) const
{
	return Color(
		red - other.red,
		green - other.green,
		blue - other.blue,
		alpha - other.alpha
	);
}

Color Color::operator*(const Color& other) const
{
	return Color(
		red * other.red,
		green * other.green,
		blue * other.blue,
		alpha * other.alpha
	);
}

Color Color::operator*(float inScale) const
{
	return Color(
		red * inScale,
		green * inScale,
		blue * inScale,
		alpha * inScale
	);
}

Color& Color::operator*=(float inScale)
{
	red *= inScale;
	green *= inScale;
	blue *= inScale;
	alpha *= inScale;
	return *this;
}

Color& Color::operator/=(float inScale)
{
	red /= inScale;
	green /= inScale;
	blue /= inScale;
	alpha /= inScale;
	return *this;
}

Color& Color::operator+=(const Color& other)
{
	red += other.red;
	green += other.green;
	blue += other.blue;
	alpha += other.alpha;
	return *this;
}

Color& Color::operator-=(const Color& other)
{
	red -= other.red;
	green -= other.green;
	blue -= other.blue;
	alpha -= other.alpha;
	return *this;
}

bool Color::operator==(const Color& other) const
{
	return (red == other.red && green == other.green && blue == other.blue && alpha == other.alpha);
}

bool Color::operator!=(const Color& other) const
{
	return (red != other.red || green != other.green || blue != other.blue || alpha != other.alpha);
}

Color::operator float* ()
{
	return rgba;
}

std::string Color::ToString()
{
	return FormatString("(%f, %f, %f, %f)", red, green, blue, alpha);
}

std::wstring Color::ToWideString()
{
	return FormatWideString(TEXT("(%f, %f, %f, %f)"), red, green, blue, alpha);
}