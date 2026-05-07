#include "PrecompiledHeader.h"
#include "AssetManager.h"
#include "../Engine/Engine.h"

#include "../Render/Mesh.h"
#include "../Render/Vertex.h"
#include "../Shader/DefaultShader.h"

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Color.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Library/stb_image.h"

AssetManager* AssetManager::instance = nullptr;

void AssetManager::Release()
{
	for (auto& mesh : meshes)
		SafeDelete(mesh.second);

	SafeDelete(instance);
}

void AssetManager::LoadMesh(const char* filePath, MeshData** outData)
{
	auto search = meshes.find(filePath);
	if (search != meshes.end())
	{
		*outData = search->second;
		return;
	}

	std::string metaFilePath = FormatString("%s.meta", filePath);
	MeshData* newMeshData = new MeshData();
	newMeshData->Deserialize(metaFilePath.c_str());
	meshes.insert(std::make_pair(filePath, newMeshData));

	*outData = newMeshData;
}

void AssetManager::LoadShader(const char* materialName, const wchar_t* shaderName, const char* texturePath, DefaultShader** outShader)
{
	auto search = shaders.find(materialName);
	if (search != shaders.end())
	{
		*outShader = search->second;
		return;
	}

	DefaultShader* newShader = new DefaultShader(shaderName, texturePath);
	if (newShader == nullptr)
	{
		// TODO LOG
		__debugbreak();
		return;
	}

	shaders.insert(std::make_pair(materialName, newShader));
	*outShader = newShader;
}

void AssetManager::LoadMaterial(const char* materialName, Material* outMaterial, DefaultShader** outShader)
{
	LoadMaterialFile(materialName, outMaterial);
	size_t convertedChars = 0;
	size_t newSize = strlen(outMaterial->shaderName) + 1;
	wchar_t* shaderName = new wchar_t[newSize];
	mbstowcs_s(&convertedChars, shaderName, newSize, outMaterial->shaderName, _TRUNCATE);
	LoadShader(materialName, shaderName, outMaterial->texturePath, outShader);

	SafeDeleteArray(shaderName);
}

void AssetManager::LoadTexture(const char* filePath, TextureData** outData)
{
	auto search = textures.find(filePath);
	if (search != textures.end())
	{
		*outData = search->second;
		return;
	}

	TextureData* newData = new TextureData();

	// Load a texture file.
	newData->data = stbi_load(filePath, &newData->width, &newData->height, &newData->channelCount, 0);
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

	textures.insert(std::make_pair(filePath, newData));
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

void AssetManager::LoadMaterialFile(const char* name, Material* outMaterial)
{
	std::string filePath = FormatString("%s/%s.txt", "../Assets/Materials/", name);
	std::string fullText;
	if (!ReadAllText(filePath, fullText))
	{
		//TODO ERROR LOG
		return;
	}

	std::stringstream fileStream(fullText);
	std::string line;

	while (std::getline(fileStream, line))
	{
		if (line.empty())
			continue;

		std::stringstream lineStream(line);
		std::string type;
		lineStream >> type;

		if (type == "color")
		{
			char junk; // to remove symbols
			Color& color = outMaterial->color;
			lineStream >> junk; // ignore '='
			lineStream >> junk; // ignore '('
			lineStream >> color.red >> junk;   // ignore ','
			lineStream >> color.green >> junk; // ignore ','
			lineStream >> color.blue >> junk;  // ignore ','
			lineStream >> color.alpha;
		}
		else if (type == "texture")
		{
			std::string dummy;
			lineStream >> dummy; // to ignore '=' 

			if (outMaterial->texturePath)
				SafeDeleteArray(outMaterial->texturePath);

			outMaterial->texturePath = new char[MAX_PATH];

			lineStream >> std::ws;
			lineStream.getline(outMaterial->texturePath, MAX_PATH);
		}
		else if (type == "shader")
		{
			std::string dummy;
			lineStream >> dummy; // to ignore '=' 

			if (outMaterial->shaderName)
				SafeDeleteArray(outMaterial->shaderName);

			outMaterial->shaderName = new char[MAX_PATH];

			lineStream >> std::ws;
			lineStream.getline(outMaterial->shaderName, MAX_PATH);
		}
	}
}
