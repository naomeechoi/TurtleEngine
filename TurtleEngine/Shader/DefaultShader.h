#pragma once
#include "../Math/Color.h"

class DefaultShader
{
public:
	DefaultShader(const wchar_t* shaderName, const char* textureName = nullptr);
	virtual ~DefaultShader();

	virtual void Bind(bool skipTextureBinding = false);
	void SetColor(const Color& color);

protected:
	wchar_t* name = nullptr;
	Color color = Color::White;
	class Texture* texture = nullptr;

	ID3D11VertexShader* vertexShader = nullptr;
	ID3DBlob* vertexShaderBuffer = nullptr;

	ID3D11PixelShader* pixelShader = nullptr;
	ID3DBlob* pixelShaderBuffer = nullptr;

	ID3D11InputLayout* inputLayout = nullptr;

	ID3D11Buffer* pixelShaderConstantBuffer = nullptr;

	ID3D11Device* refDevice = nullptr;
	ID3D11DeviceContext* refDeviceContext = nullptr;
};

