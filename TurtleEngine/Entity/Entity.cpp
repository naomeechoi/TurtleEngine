#include "PrecompiledHeader.h"
#include "Entity.h"

#include "../Render/Mesh.h"
#include "../Math/Quaternion.h"

#include "../Shader/DefaultShader.h"

#include "../Engine/Engine.h"

Entity::Entity()
{
	refDevice = gEngine->Device();
	refDevice->AddRef();

	refContext = gEngine->Context();
	refContext->AddRef();

	transform = new Transform();

	// AABB Min-Max 설정.
	UpdateAABB();
}

Entity::~Entity()
{
	refDevice->Release();
	refContext->Release();
	SafeDelete(transform);
}

void Entity::Update(float deltaTime)
{
	transform->Update(deltaTime);
}

void Entity::Draw(EngineShader* overrideShader, bool skipTextureBinding)
{
	transform->Bind();
}

bool Entity::IsColideWithOther(const Entity& other)
{
	if (this->max.x < other.min.x || this->min.x > other.max.x) return false;
	if (this->max.y < other.min.y || this->min.y > other.max.y) return false;
	if (this->max.z < other.min.z || this->min.z > other.max.z) return false;

	return true;
}

void Entity::SetPosition(const Vector3& position)
{
	transform->SetPosition(position);
	UpdateAABB();
}

void Entity::SetPosition(float x, float y, float z)
{
	transform->SetPosition(x, y, z);
	UpdateAABB();
}

void Entity::SetRotation(const Vector3& rotation)
{
	transform->SetRotation(rotation);
	UpdateAABB();
}

void Entity::SetRotation(float x, float y, float z)
{
	transform->SetRotation(x, y, z);
	UpdateAABB();
}

void Entity::SetScale(const Vector3& scale)
{
	transform->SetScale(scale);
	UpdateAABB();
}

void Entity::SetScale(float x, float y, float z)
{
	transform->SetScale(x, y, z);
	UpdateAABB();
}

Transform& Entity::GetTransform() const
{
	return *transform;
}

Vector3 Entity::Min()
{
	return min;
}

Vector3 Entity::Max()
{
	return max;
}

void Entity::UpdateAABB()
{
	// 1. 회전 전 로컬 박스의 8개 정점을 스케일에 맞춰 생성 (생략 가능하지만 개념상 필요)
	// 2. 간단하게 처리하려면, 회전된 후의 "최대 범위"를 새로 계산해야 함

	Vector3 localExtents = Vector3::One * transform->Scale();

	// 로컬의 min, max를 회전시킨 후 '위치'를 나중에 더함
	Vector3 rotatedMin = transform->Rotation().ToQuaternion().RotateVector(localExtents * -1.0f);
	Vector3 rotatedMax = transform->Rotation().ToQuaternion().RotateVector(localExtents);

	// 회전 후에는 rotatedMin.x가 rotatedMax.x보다 커질 수 있으므로 다시 정렬
	min.x = std::min(rotatedMin.x, rotatedMax.x) + transform->Position().x;
	min.y = std::min(rotatedMin.y, rotatedMax.y) + transform->Position().y;
	min.z = std::min(rotatedMin.z, rotatedMax.z) + transform->Position().z;

	max.x = std::max(rotatedMin.x, rotatedMax.x) + transform->Position().x;
	max.y = std::max(rotatedMin.y, rotatedMax.y) + transform->Position().y;
	max.z = std::max(rotatedMin.z, rotatedMax.z) + transform->Position().z;
}