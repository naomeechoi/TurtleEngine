#include "PrecompiledHeader.h"
#include "Transform.h"
#include "../Engine/Engine.h"

Transform::Transform()
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = sizeof(Matrix4);
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA bufferData = {};
	bufferData.pSysMem = &matrix;
	
	refDevice = gEngine->Device();
	refDevice->AddRef();

	refDeviceContext = gEngine->Context();
	refDeviceContext->AddRef();

	ThrowIfFailed(
		refDevice->CreateBuffer(&bufferDesc, &bufferData, &buffer),
		TEXT("Failed to create transform constant buffer."));
}

Transform::~Transform()
{
	refDevice->Release();
	refDeviceContext->Release();

	SafeRelease(buffer);
}

void Transform::Update(float delatTime)
{
	/*matrix = Matrix4::Scale(scale) * Matrix4::Rotation(rotation.ToQuaternion())
		* Matrix4::Translation(position);*/

	D3D11_MAPPED_SUBRESOURCE mappedResource = {};
	refDeviceContext->Map(buffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mappedResource);
	memcpy(mappedResource.pData, &matrix, sizeof(matrix));
	refDeviceContext->Unmap(buffer, 0u);
}

void Transform::Bind()
{
	refDeviceContext->VSSetConstantBuffers(0u, 1u, &buffer);
}

void Transform::SetPosition(const Vector3& newPosition)
{
	position = newPosition;
}

void Transform::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Transform::SetRotation(const Vector3& newRotation)
{
	rotation = newRotation;
}

void Transform::SetRotation(float x, float y, float z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

void Transform::SetScale(const Vector3& newScale)
{
	scale = newScale;
}

void Transform::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

void Transform::SetScale(float scale)
{
	this->scale.x = scale;
	this->scale.y = scale;
	this->scale.z = scale;
}

Vector3 Transform::Right()
{
	return Matrix4::Rotation(rotation) * Vector3::Right;
}

Vector3 Transform::Up()
{
	return Matrix4::Rotation(rotation) * Vector3::Up;
}

Vector3 Transform::Forward()
{
	return Matrix4::Rotation(rotation) * Vector3::Forward;
}
