#include "PrecompiledHeader.h"
#include "AssetManager.h"
#include "../Render/Mesh.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Color.h"
#include "../Render/Vertex.h"
#include "../Engine/Engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Library/stb_image.h"

AssetManager* AssetManager::instance = nullptr;

void AssetManager::Release()
{
	for (auto& mesh : meshes)
		SafeDelete(mesh.second);

	SafeDelete(instance);
}

void AssetManager::LoadMesh(const char* filepath, MeshData** outData)
{
	auto search = meshes.find(filepath);
	if (search != meshes.end())
	{
		*outData = search->second;
		return;
	}

	std::string metaFilePath = FormatString("%s.meta", filepath);
	MeshData* newMeshData = new MeshData();
	newMeshData->Deserialize(metaFilePath.c_str());
	meshes.insert(std::make_pair(filepath, newMeshData));

	*outData = newMeshData;
}

void AssetManager::LoadTexture(const char* filepath, TextureData** outData)
{
	auto search = textures.find(filepath);
	if (search != textures.end())
	{
		*outData = search->second;
		return;
	}

	TextureData* newData = new TextureData();

	// Load a texture file.
	newData->data = stbi_load(filepath, &newData->width, &newData->height, &newData->channelCount, 0);
	if (newData->data == nullptr)
	{
		ThrowWithMessage(TEXT("Failed to load a texture file"));
		return;
	}

	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.Width = newData->width;
	textureDesc.Height = newData->height;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.ArraySize = 1;
	textureDesc.MipLevels = 1;

	D3D11_SUBRESOURCE_DATA textureSubresourceData = {};
	textureSubresourceData.pSysMem = newData->data;
	textureSubresourceData.SysMemPitch = newData->width * newData->channelCount;

	ID3D11Texture2D* texture = nullptr;
	ThrowIfFailed(
		gEngine->Device()->CreateTexture2D(&textureDesc, &textureSubresourceData, &texture),
		TEXT("Failed to create texture2d."));

	ThrowIfFailed(
		gEngine->Device()->CreateShaderResourceView(texture, nullptr, &newData->shaderResourceView),
		TEXT("Failed to create shader resource view"));

	SafeRelease(texture);

	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = -FLT_MIN;
	samplerDesc.MaxLOD = FLT_MAX;
	samplerDesc.MaxAnisotropy = 3u;
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;

	ThrowIfFailed(
		gEngine->Device()->CreateSamplerState(&samplerDesc, &newData->samplerState),
		TEXT("Failed to create sampler state"));

	textures.insert(std::make_pair(filepath, newData));
	*outData = newData;

	newData = nullptr;
}

AssetManager& AssetManager::Get()
{
	if (instance == nullptr)
	{
		instance = new AssetManager();
	}

	return *instance;
}

void AssetManager::LoadMeshFile(const char* filePath, MeshData** outMesh)
{
	std::string fullText;
	if (!ReadAllText(filePath, fullText))
	{
		//TODO ERROR LOG
		return;
	}

	std::stringstream fileStream(fullText);
	std::string line;

	std::vector<Vector3> positions;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;
	std::vector<Vertex> vertices;

	while (std::getline(fileStream, line))
	{
		if (line.empty())
			continue;

		std::stringstream lineStream(line);
		std::string type;
		lineStream >> type;

		if (type == "v")
		{
			Vector3 pos;
			lineStream >> pos.x >> pos.y >> pos.z;
			positions.push_back(pos);
		}
		else if (type == "vt")
		{
			Vector2 uv;
			lineStream >> uv.x >> uv.y;
			uvs.push_back(uv);
		}
		else if (type == "vn")
		{
			Vector3 normal;
			lineStream >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		}
		else if (type == "f")
		{
			std::string vertexData;
			while (lineStream >> vertexData)
			{
				int vIdx = 0;
				int tIdx = 0;
				int nIdx = 0;
				for (auto& ch : vertexData)
				{
					if (ch == '/')
						ch = ' ';
				}

				std::stringstream vertexStream(vertexData);
				vertexStream >> vIdx >> tIdx >> nIdx;
				vertices.emplace_back(
					positions[vIdx - 1],
					uvs[tIdx - 1],
					Color::White,
					normals[nIdx - 1]
				);
			}
		}
	}

	// 인덱스 생성
	std::vector<uint32> indices(vertices.size());
	for (uint32 i = 0; i < (uint32)vertices.size(); ++i)
	{
		indices[i] = i;
	}

	// 출력 데이터 할당 (기존 구조 유지)
	if (*outMesh)
	{
		(*outMesh)->vertexCount = static_cast<uint32>(vertices.size());
		(*outMesh)->vertexBufferData = new Vertex[vertices.size()];
		std::copy(vertices.begin(), vertices.end(), static_cast<Vertex*>((*outMesh)->vertexBufferData));
		(*outMesh)->vertexStride = Vertex::Stride();

		(*outMesh)->indexCount = static_cast<uint32>(indices.size());
		(*outMesh)->indexBufferData = new uint32[indices.size()];
		std::copy(indices.begin(), indices.end(), static_cast<uint32*>((*outMesh)->indexBufferData));
	}
}
