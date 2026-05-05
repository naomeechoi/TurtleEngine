#pragma once


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

struct MeshData;
class AssetManager
{
public:
	void Release();
	void LoadMesh(const char* filepath, MeshData** outData);
	void LoadTexture(const char* filepath, TextureData** outData);

	static AssetManager& Get();

private:
	void LoadMeshFile(const char* filePath, MeshData** outMesh);

private:
	static AssetManager* instance;
	std::unordered_map<std::string, MeshData*> meshes;
	std::unordered_map<std::string, TextureData*> textures;
};