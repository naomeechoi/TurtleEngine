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
