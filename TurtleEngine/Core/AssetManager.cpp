#include <PrecompiledHeader.h>
#include "AssetManager.h"
#include "../Render/Mesh.h"

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

AssetManager& AssetManager::Get()
{
	// TODO: 여기에 return 문을 삽입합니다.
}

void AssetManager::LoadMeshFile(const char* filePath, MeshData** outMesh)
{
}
