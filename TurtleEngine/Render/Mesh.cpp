#include "PrecompiledHeader.h"
#include "Mesh.h"
#include "../Engine/Engine.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Render/Vertex.h"
#include "../Core/AssetManager.h"

MeshData::~MeshData()
{
	SafeDelete(vertexBufferData);
	SafeDelete(indexBufferData);
}

void MeshData::Serialize(const char* filename)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);

	if (!file.is_open())
	{
		//Logger::Get().PrintMessage(TEXT("Failed to open file for writing"));
		return;
	}

	file.write(reinterpret_cast<const char*>(&vertexStride), sizeof(vertexStride));
	file.write(reinterpret_cast<const char*>(&vertexCount), sizeof(vertexCount));

	if (vertexBufferData && vertexCount > 0)
	{
		size_t totalBufferSize = static_cast<size_t>(vertexStride) * vertexCount;
		file.write(static_cast<const char*>(vertexBufferData), totalBufferSize);
	}

	file.write(reinterpret_cast<const char*>(&indexCount), sizeof(indexCount));

	if (indexBufferData && indexCount > 0)
	{
		size_t totalIndexSize = static_cast<size_t>(sizeof(uint32)) * indexCount;
		file.write(reinterpret_cast<const char*>(indexBufferData), totalIndexSize);
	}
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
		size_t bufferSize = static_cast<size_t>(vertexStride) * vertexCount;

		vertexBufferData = new char[bufferSize];
		if (vertexBufferData != nullptr)
		{
			file.read(static_cast<char*>(vertexBufferData), bufferSize);
		}
	}

	file.read(reinterpret_cast<char*>(&indexCount), sizeof(indexCount));

	if (indexCount > 0)
	{
		indexBufferData = new uint32[indexCount];
		if (indexBufferData != nullptr)
		{
			size_t totalIndexSize = static_cast<size_t>(sizeof(uint32)) * indexCount;
			file.read(reinterpret_cast<char*>(indexBufferData), totalIndexSize);
		}
	}
}

Mesh::Mesh()
{
	refDevice = gEngine->Device();
	refDevice->AddRef();

	refDeviceContext = gEngine->Context();
	refDeviceContext->AddRef();
}

Mesh::Mesh(const char* filePath)
	: Mesh()
{
	AssetManager::Get().LoadMesh(filePath, &meshData);

	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.ByteWidth = meshData->vertexStride * meshData->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = meshData->vertexBufferData;

	ThrowIfFailed(refDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer),
		TEXT("Failed to create vertex buffer."));

	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.ByteWidth = sizeof(uint32) * meshData->indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA indexData = {};
	indexData.pSysMem = meshData->indexBufferData;

	ThrowIfFailed(refDevice->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer),
		TEXT("Failed to create vertex buffer."));
}

Mesh::Mesh(void* vertexBufferData, uint32 vertexStride, uint32 vertexCount, void* indexBufferData, uint32 indexCount)
	:Mesh()
{
	meshData = new MeshData(vertexBufferData, vertexStride, vertexCount, indexBufferData, indexCount);
}

Mesh::Mesh(MeshData* meshData)
{
	this->meshData = meshData;

	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.ByteWidth = meshData->vertexStride * meshData->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = meshData->vertexBufferData;

	ThrowIfFailed(
		refDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer),
		TEXT("Failed to create vertex buffer."));

	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.ByteWidth = sizeof(uint32) * meshData->indexCount;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA indexData = {};
	indexData.pSysMem = meshData->indexBufferData;

	ThrowIfFailed(
		refDevice->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer),
		TEXT("Failed to create index buffer."));
}

Mesh::~Mesh()
{
	refDevice->Release();
	refDeviceContext->Release();

	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void Mesh::Draw()
{
	uint32 offset = 0u;
	refDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	refDeviceContext->IASetVertexBuffers(0u, 1u, &vertexBuffer, &meshData->vertexStride, &offset);
	refDeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0u);

	refDeviceContext->DrawIndexed(meshData->indexCount, 0u, 0u);
}

void Mesh::UpdateMeshData(MeshData* data)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource = {};
	refDeviceContext->Map(vertexBuffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mappedResource);
	memcpy(mappedResource.pData, data->vertexBufferData, data->vertexStride * data->vertexCount);
	refDeviceContext->Unmap(vertexBuffer, 0u);
}
