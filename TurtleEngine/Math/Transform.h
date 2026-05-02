#pragma once
#include "../Math/Vector3.h"
#include "../Math/Matrix4.h"

class Transform
{
public:
	Transform();
	~Transform();

	void Update(float delatTime);
	void Bind();

	Vector3& Position() { return position; }
	void SetPosition(const Vector3& newPosition);
	void SetPosition(float x, float y, float z);

	Vector3& Rotation() { return rotation; }
	void SetRotation(const Vector3& newRotation);
	void SetRotation(float x, float y, float z);

	Vector3& Scale() { return scale; }
	void SetScale(const Vector3& newScale);
	void SetScale(float x, float y, float z);
	void SetScale(float scale);

	Vector3 Right();
	Vector3 Up();
	Vector3 Forward();

private:
	Vector3 position = Vector3::Zero;
	Vector3 rotation = Vector3::Zero;
	Vector3 scale = Vector3::One;

	Matrix4 matrix = Matrix4::Identity();

	struct ID3D11Buffer* buffer = nullptr;
	struct ID3D11Device* refDevice = nullptr;
	struct ID3D11DeviceContext* refDeviceContext = nullptr;
};
