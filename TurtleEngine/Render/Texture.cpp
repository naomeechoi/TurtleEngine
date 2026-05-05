#include "PrecompiledHeader.h"
#include "Texture.h"
#include "../Engine/Engine.h"
#include "../Core/AssetManager.h"

Texture::Texture()
{
	refDevice = gEngine->Device();
	refDevice->AddRef();

	refDeviceContext = gEngine->Context();
	refDeviceContext->AddRef();
}

Texture::Texture(const char* filename, BindType bindType, uint32 index)
	: bindType(bindType), index(index)
{
	refDevice = gEngine->Device();
	refDevice->AddRef();

	refDeviceContext = gEngine->Context();
	refDeviceContext->AddRef();

	CopyString(&name, filename);
	LoadTexture(filename);
}


Texture::~Texture()
{
	refDevice->Release();
	refDeviceContext->Release();

	SafeDeleteArray(name);
}

void Texture::Bind()
{
	if (bindType == BindType::VertexShader)
	{
		refDeviceContext->VSSetShaderResources(index, 1u, &textureData->shaderResourceView);
		refDeviceContext->VSSetSamplers(index, 1u, &textureData->samplerState);
	}
	else
	{
		refDeviceContext->PSGetShaderResources(index, 1u, &textureData->shaderResourceView);
		refDeviceContext->PSSetSamplers(index, 1u, &textureData->samplerState);
	}
}

void Texture::LoadTexture(const char* filename)
{
	AssetManager::Get().LoadTexture(filename, &textureData);
}
