#include "PrecompiledHeader.h"
#include "Mesh.h"

MeshData::~MeshData()
{
}

void MeshData::Serialize(const char* filename)
{
}

void MeshData::Deserialize(const char* filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open())
	{
		// TODO: Fail log
		return;
	}

	file.read(reinterpret_cast<char*>(&vertexStride), sizeof(vertexStride));
	file.read(reinterpret_cast<char*>(&vertexCount), sizeof(vertexCount));

	if (vertexStride > 0 && vertexCount > 0)
	{
		size_t totalSize = static_cast<size_t>(vertexStride) * vertexCount;
		vertexBufferData.resize(totalSize);
		file.read(vertexBufferData.data(), totalSize);
	}

	file.read(reinterpret_cast<char*>(&indexCount), sizeof(indexCount));

	if (indexCount > 0)
	{
		indexBufferData.resize(indexCount);
		file.read(reinterpret_cast<char*>(indexBufferData.data()), sizeof(uint32) * indexCount);
	}
}

Mesh::Mesh()
{
}

Mesh::Mesh(const char* filePath)
{
}

Mesh::Mesh(void* vertexBufferData, uint32 vertexStride, uint32 vertexCount, void* indexBufferData, uint32 indexCount)
{
}

Mesh::Mesh(MeshData* meshData)
{
}

void Mesh::Draw()
{
}

void Mesh::UpdateMeshData(MeshData* data)
{
}
