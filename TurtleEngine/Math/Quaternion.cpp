#include "PrecompiledHeader.h"
#include "MathDefine.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix4.h"

Quaternion::Quaternion()
{
}

Quaternion::Quaternion(const Vector3& vector, float scalar)
	: x(vector.x), y(vector.y), z(vector.z), w(scalar)
{
}

Quaternion::Quaternion(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{
}

Quaternion Quaternion::Normalized()
{
	return *this / Magnitude();
}

float Quaternion::Dot(const Quaternion& other)
{
	return (x * other.x + y * other.y + z * other.z + w * other.w);
}

float Quaternion::Magnitude()
{
	return std::sqrtf(Dot(*this));
}

Quaternion Quaternion::Conjugate()
{
	return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::Inverse()
{
	return Conjugate();
}

Vector3 Quaternion::ToVector3()
{
	float sqW = w * w;
	float sqX = x * x;
	float sqY = y * y;
	float sqZ = z * z;

	float unit = sqX + sqY + sqZ + sqW;
	float test = x * y + z * w;

	float yaw = 0.0f;
	float pitch = 0.0f;
	float roll = 0.0f;

	// North pole singularaty.
	if (test > 0.499f * unit)
	{
		yaw = 2.0f * std::atan2f(x, w);
		pitch = Math::PI * 0.5f;
		roll = 0.0f;

		return Vector3(yaw, pitch, roll);
	}

	// South pole singularaty
	if (test < -0.499f * unit)
	{
		yaw = -2.0f * std::atan2f(x, w);
		pitch = -Math::PI * 0.5f;
		roll = 0.0f;

		return Vector3(yaw, pitch, roll);
	}

	yaw = std::atan2f(2.0f * y * w - 2.0f * x * z, sqX - sqY - sqZ + sqW);
	pitch = std::asinf(2.0f * test / unit);
	roll = std::atan2f(2.0f * x * w - 2.0f * y * z, -sqX + sqY - sqZ + sqW);

	return Vector3(yaw, pitch, roll);
}

Matrix4 Quaternion::ToMatrix4()
{
	// Precalculate coordinate products
	float x = this->x * 2.0f;
	float y = this->y * 2.0f;
	float z = this->z * 2.0f;
	float xx = this->x * x;
	float yy = this->y * y;
	float zz = this->z * z;
	float xy = this->x * y;
	float xz = this->x * z;
	float yz = this->y * z;
	float wx = this->w * x;
	float wy = this->w * y;
	float wz = this->w * z;

	Matrix4 mat = Matrix4::Identity();
	mat.Get(0, 0) = 1.0f - (yy + zz);
	mat.Get(1, 0) = xy + wz;
	mat.Get(2, 0) = xz - wy;
	mat.Get(3, 0) = 0.0f;

	mat.Get(0, 1) = xy - wz;
	mat.Get(1, 1) = 1.0f - (xx + zz);
	mat.Get(2, 1) = yz + wx;
	mat.Get(3, 1) = 0.0f;

	mat.Get(0, 2) = xz + wy;
	mat.Get(1, 2) = yz - wx;
	mat.Get(2, 2) = 1.0f - (xx + yy);
	mat.Get(3, 2) = 0.0f;

	mat.Get(0, 3) = 0.0f;
	mat.Get(1, 3) = 0.0f;
	mat.Get(2, 3) = 0.0f;
	mat.Get(3, 3) = 1.0f;

	return mat;
}

Matrix4 const Quaternion::ToMatrix4() const
{
	// Precalculate coordinate products
	float x = this->x * 2.0f;
	float y = this->y * 2.0f;
	float z = this->z * 2.0f;
	float xx = this->x * x;
	float yy = this->y * y;
	float zz = this->z * z;
	float xy = this->x * y;
	float xz = this->x * z;
	float yz = this->y * z;
	float wx = this->w * x;
	float wy = this->w * y;
	float wz = this->w * z;

	Matrix4 mat = Matrix4::Identity();
	mat.Get(0, 0) = 1.0f - (yy + zz);
	mat.Get(1, 0) = xy + wz;
	mat.Get(2, 0) = xz - wy;
	mat.Get(3, 0) = 0.0f;

	mat.Get(0, 1) = xy - wz;
	mat.Get(1, 1) = 1.0f - (xx + zz);
	mat.Get(2, 1) = yz + wx;
	mat.Get(3, 1) = 0.0f;

	mat.Get(0, 2) = xz + wy;
	mat.Get(1, 2) = yz - wx;
	mat.Get(2, 2) = 1.0f - (xx + yy);
	mat.Get(3, 2) = 0.0f;

	mat.Get(0, 3) = 0.0f;
	mat.Get(1, 3) = 0.0f;
	mat.Get(2, 3) = 0.0f;
	mat.Get(3, 3) = 1.0f;

	return mat;
}

Vector3 Quaternion::RotateVector(const Vector3& vector)
{
	float x = this->x * 2.0f;
	float y = this->y * 2.0f;
	float z = this->z * 2.0f;
	float xx = this->x * x;
	float yy = this->y * y;
	float zz = this->z * z;
	float xy = this->x * y;
	float xz = this->x * z;
	float yz = this->y * z;
	float wx = this->w * x;
	float wy = this->w * y;
	float wz = this->w * z;

	Vector3 res;
	res.x = (1.0f - (yy + zz)) * vector.x + (xy - wz) * vector.y + (xz + wy) * vector.z;
	res.y = (xy + wz) * vector.x + (1.0f - (xx + zz)) * vector.y + (yz - wx) * vector.z;
	res.z = (xz - wy) * vector.x + (yz + wx) * vector.y + (1.0f - (xx + yy)) * vector.z;

	return res;
}

Quaternion Quaternion::operator=(const Quaternion& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;

	return *this;
}

Quaternion Quaternion::operator+(const Quaternion& other)
{
	Quaternion temp = *this;
	temp.x += other.x;
	temp.y += other.y;
	temp.z += other.z;
	temp.w += other.w;

	return temp;
}

Quaternion Quaternion::operator+(float scalar)
{
	Quaternion temp = *this;
	temp.x += scalar;
	temp.y += scalar;
	temp.z += scalar;
	temp.w += scalar;

	return temp;
}

Quaternion& Quaternion::operator+=(const Quaternion& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;

	return *this;
}

Quaternion& Quaternion::operator+=(float scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;
	w += scalar;

	return *this;
}

Quaternion Quaternion::operator-(const Quaternion& other)
{
	Quaternion temp = *this;
	temp.x -= other.x;
	temp.y -= other.y;
	temp.z -= other.z;
	temp.w -= other.w;

	return temp;
}

Quaternion Quaternion::operator-(float scalar)
{
	Quaternion temp = *this;
	temp.x -= scalar;
	temp.y -= scalar;
	temp.z -= scalar;
	temp.w -= scalar;

	return temp;
}

Quaternion& Quaternion::operator-=(const Quaternion& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;

	return *this;
}

Quaternion& Quaternion::operator-=(float scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;
	w -= scalar;

	return *this;
}

Quaternion Quaternion::operator*(const Quaternion& other)
{
	Quaternion temp;
	temp.x = w * other.x + x * other.w + y * other.z - z * other.y;
	temp.y = w * other.y + y * other.w + z * other.x - x * other.z;
	temp.z = w * other.z + z * other.w + x * other.y - y * other.x;
	temp.w = w * other.w - x * other.x - y * other.y - z * other.z;

	return temp;
}

Quaternion Quaternion::operator*(float scalar)
{
	Quaternion temp = *this;
	temp.x *= scalar;
	temp.y *= scalar;
	temp.z *= scalar;
	temp.w *= scalar;

	return temp;
}

Quaternion& Quaternion::operator*=(const Quaternion& other)
{
	Quaternion temp = *this;
	*this = temp * other;

	return *this;
}

Quaternion& Quaternion::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;

	return *this;
}

Quaternion Quaternion::operator/(const Quaternion& other)
{
	Quaternion temp = *this;
	temp.x /= other.x;
	temp.y /= other.y;
	temp.z /= other.z;
	temp.w /= other.w;

	return temp;
}

Quaternion Quaternion::operator/(float scalar)
{
	Quaternion temp = *this;
	temp.x /= scalar;
	temp.y /= scalar;
	temp.z /= scalar;
	temp.w /= scalar;

	return temp;
}

Quaternion& Quaternion::operator/=(const Quaternion& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;

	return *this;
}

Quaternion& Quaternion::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;

	return *this;
}

Quaternion Quaternion::Lerp(const Quaternion& a, const Quaternion& b, float t)
{
	Quaternion tempA = a;
	Quaternion tempB = b;
	const float check = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	if (check < 0.0f)
	{
		tempB = tempB.Conjugate();
	}

	Quaternion q;
	q.x = tempA.x * (1.0f - t) + tempB.x * t;
	q.y = tempA.y * (1.0f - t) + tempB.y * t;
	q.z = tempA.z * (1.0f - t) + tempB.z * t;
	q.w = tempA.w * (1.0f - t) + tempB.w * t;

	return q;
}