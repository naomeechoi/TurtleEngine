#include "PrecompiledHeader.h"
#include "AssetManager.h"
#include "../Render/Mesh.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Color.h"
#include "../Render/Vertex.h"

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
