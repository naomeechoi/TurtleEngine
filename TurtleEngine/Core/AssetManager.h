#pragma once

struct MeshData;

class AssetManager
{
public:
	void Release();
	void LoadMesh(const char* filepath, MeshData** outData);

	static AssetManager& Get();

private:
	void LoadMeshFile(const char* filePath, MeshData** outMesh);

private:
	static AssetManager* instance;
	std::unordered_map<std::string, MeshData*> meshes;
};