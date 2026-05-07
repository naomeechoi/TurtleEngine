#pragma once
#include "../Math/Transform.h"
#include "../Math/Vector3.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void Update(float deltaTime);
	virtual void Draw(class EngineShader* overrideShader = nullptr, bool skipTextureBinding = false);

	bool IsColideWithOther(const Entity& other);

	Vector3& Position() { return transform->Position(); }
	virtual void SetPosition(const Vector3& position);
	virtual void SetPosition(float x, float y, float z);

	Vector3& Rotation() { return transform->Rotation(); }
	virtual void SetRotation(const Vector3& rotation);
	virtual void SetRotation(float x, float y, float z);

	Vector3& Scale() { return transform->Scale(); }
	virtual void SetScale(const Vector3& scale);
	virtual void SetScale(float x, float y, float z);

	Transform& GetTransform() const;
	Vector3 Min();
	Vector3 Max();

protected:
	void UpdateAABB();

protected:
	Transform* transform = nullptr;
	Vector3 min = Vector3::One;
	Vector3 max = Vector3::One;

	struct ID3D11Device* refDevice = nullptr;
	struct ID3D11DeviceContext* refContext = nullptr;
};

