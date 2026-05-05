#pragma once
#include "../Core/CommonDefine.h"
class Texture
{
	enum class BindType
	{
		VertexShader,
		PixelShader
	};

public:
	Texture();
	Texture(const char* filename, BindType bindType = BindType::PixelShader, uint32 index = 0u);
	virtual ~Texture();

	void Bind();

private:
	void LoadTexture(const char* filename);

private:
	char* name = nullptr;
	uint32 index = 0u;

	class TextureData* textureData = nullptr;
	BindType bindType = BindType::PixelShader;

	struct ID3D11Device* refDevice = nullptr;
	struct ID3D11DeviceContext* refDeviceContext = nullptr;
};

