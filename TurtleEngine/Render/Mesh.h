#pragma once
#include "CommonDefine.h"

struct MeshData
{
	MeshData() = default;
	~MeshData();

	void Serialize(const char* fileName);
	void Deserialize(const char* fileName);

	void* vertexBufferData = nullptr;
	uint32 vertexStride = 0u;
	uint32 vertexCount = 0u;

	void* indexBufferData = nullptr;
	uint32 indexCount = 0u;
};

class Mesh
{
public:
	Mesh();
	Mesh(const char* filePath);
	Mesh(
		void* vertexBufferData,
		uint32 vertexStride,
		uint32 vertexCount,
		void* indexBufferData,
		uint32 indexCount);
	Mesh(MeshData* meshData);

	virtual void Draw();
	void UpdateMeshData(MeshData* data);
	uint32 IndexCount() const { return meshData->indexCount; }

protected:
	MeshData* meshData = nullptr;
	struct ID3D11Buffer* vertexBuffer = nullptr;
	struct ID3D11Buffer* indexBuffer = nullptr;

	struct ID3D11Device* refDevice = nullptr;
	struct ID3D11DeviceContext* refContext = nullptr;
};

