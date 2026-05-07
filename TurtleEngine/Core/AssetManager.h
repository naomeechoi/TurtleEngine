#pragma once

#include "../Math/Color.h"

struct TextureData
{
	TextureData()
	{
	}

	~TextureData()
	{
		free(data);
		SafeRelease(shaderResourceView);
		SafeRelease(samplerState);
	}

	int width = 0;
	int height = 0;
	int channelCount = 0;
	void* data = nullptr;
	struct ID3D11ShaderResourceView* shaderResourceView = nullptr;
	struct ID3D11SamplerState* samplerState = nullptr;
};

struct Material
{
	~Material()
	{
		SafeDelete(shaderName);
		SafeDelete(texturePath);
	}

	char* shaderName = nullptr;
	Color color = Color::White;
	char* texturePath = nullptr;
};

struct MeshData;
class DefaultShader;

class AssetManager
{
public:
	void Release();
	void LoadMesh(const char* filePath, MeshData** outData);
	void LoadShader(const char* materialName, const wchar_t* shaderName, const char* texturePath, DefaultShader** outShader);
	void LoadMaterial(const char* materialName, Material* outMaterial, DefaultShader** outShader);
	void LoadTexture(const char* filePath, TextureData** outData);

	static AssetManager& Get();

private:
	void LoadMeshFile(const char* filePath, MeshData** outMesh);
	void LoadMaterialFile(const char* name, Material* outMaterial);

private:
	static AssetManager* instance;
	std::unordered_map<std::string, MeshData*> meshes;
	std::unordered_map<std::string, DefaultShader*> shaders;
	std::unordered_map<std::string, TextureData*> textures;
};