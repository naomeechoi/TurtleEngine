#pragma once
class Vector3;
class Matrix4;

class alignas(16) Quaternion
{
public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;

	Quaternion();
	Quaternion(const Vector3& vector, float scalar);
	Quaternion(float x, float y, float z, float w);

	Quaternion Normalized();
	float Dot(const Quaternion& other);

	float Magnitude();
	Quaternion Conjugate();
	Quaternion Inverse();

	Vector3 ToVector3();
	Matrix4 ToMatrix4();
	Matrix4 const ToMatrix4() const;

	Vector3 RotateVector(const Vector3& vector);

	Quaternion operator=(const Quaternion& other);

	Quaternion operator+(const Quaternion& other);
	Quaternion operator+(float scalar);
	Quaternion& operator+=(const Quaternion& other);
	Quaternion& operator+=(float scalar);

	Quaternion operator-(const Quaternion& other);
	Quaternion operator-(float scalar);
	Quaternion& operator-=(const Quaternion& other);
	Quaternion& operator-=(float scalar);

	Quaternion operator*(const Quaternion& other);
	Quaternion operator*(float scalar);
	Quaternion& operator*=(const Quaternion& other);
	Quaternion& operator*=(float scalar);

	Quaternion operator/(const Quaternion& other);
	Quaternion operator/(float scalar);
	Quaternion& operator/=(const Quaternion& other);
	Quaternion& operator/=(float scalar);

	static Quaternion Identity() { return Quaternion(0.0f, 0.0f, 0.0f, 1.0f); }
	static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float t);
};

