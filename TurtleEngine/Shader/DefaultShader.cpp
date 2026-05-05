#include "PrecompiledHeader.h"
#include "DefaultShader.h"
#include "../Engine/Engine.h"
#include "../Render/Texture.h"

DefaultShader::DefaultShader(const wchar_t* shaderName, const char* textureName)
{
	CopyWideString(&this->name, name);

	const wchar_t* shaderPath = FormatWideStringW(TEXT("../CompiledShader/%sVertexShader.cso"), name);
	ThrowIfFailed(
		D3DReadFileToBlob(shaderPath, &vertexShaderBuffer),
		TEXT("Failed to read compiled vertex shader file"));
	SafeDeleteArray(shaderPath);

	refDevice = gEngine->Device();
	refDevice->AddRef();

	refDeviceContext = gEngine->Context();
	refDeviceContext->AddRef();

	ThrowIfFailed(
		refDevice->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &vertexShader),
		TEXT("Failed to create vertex shader."));

	shaderPath = FormatWideStringW(TEXT("../CompiledShader/%sPixelShader.cso"), name);
	ThrowIfFailed(
		D3DReadFileToBlob(shaderPath, &pixelShaderBuffer),
		TEXT("Failed to read compiled pixel shader file"));
	SafeDeleteArray(shaderPath);

	ThrowIfFailed(
		refDevice->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &pixelShader),
		TEXT("Failed to create pixel shader."));

	D3D11_INPUT_ELEMENT_DESC inputlayoutDesc[] =
	{
		{"POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u},
		{"TEXCOORD", 0u, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u},
		{"COLOR", 0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u},
		{"NORMAL", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u},
	};

	ThrowIfFailed(
		refDevice->CreateInputLayout(inputlayoutDesc, _countof(inputlayoutDesc), vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &inputLayout),
		TEXT("Failed to create input layout."));
#if _DEBUG
	const char* inputlayoutname = "EngineShader::InputLayout";
	uint32 size = static_cast<uint32>(strlen(inputlayoutname));
	inputLayout->SetPrivateData(WKPDID_D3DDebugObjectName, size, inputlayoutname);
#endif

	D3D11_BUFFER_DESC pixelConstantBufferDesc = {};
	pixelConstantBufferDesc.ByteWidth = sizeof(Color);
	pixelConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	pixelConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pixelConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA pixelConstantBufferData = {};
	pixelConstantBufferData.pSysMem = &color;

	ThrowIfFailed(
		refDevice->CreateBuffer(&pixelConstantBufferDesc, &pixelConstantBufferData, &pixelShaderConstantBuffer),
		TEXT("Failed to create pixel shader constant shader buffer")
	);

	// Texture.
	if (textureName != nullptr)
	{
		texture = new Texture(textureName);
	}
	else
	{
		texture = new Texture("../Assets/Textures/colormap.png");
	}
}

DefaultShader::~DefaultShader()
{
	refDevice->Release();
	refDeviceContext->Release();

	SafeDeleteArray(name);

	SafeDelete(texture);

	SafeRelease(inputLayout);

	SafeRelease(vertexShader);
	SafeRelease(vertexShaderBuffer);
	SafeRelease(pixelShader);
	SafeRelease(pixelShaderBuffer);
	SafeRelease(pixelShaderConstantBuffer);
}

void DefaultShader::Bind(bool skipTextureBinding)
{
	refDeviceContext->IASetInputLayout(inputLayout);
	refDeviceContext->VSSetShader(vertexShader, nullptr, 0u);
	refDeviceContext->PSSetConstantBuffers(0u, 1u, &pixelShaderConstantBuffer);
	refDeviceContext->PSSetShader(pixelShader, nullptr, 0u);
	if (texture && !skipTextureBinding)
		texture->Bind();
}

void DefaultShader::SetColor(const Color& color)
{
	this->color = color;

	D3D11_MAPPED_SUBRESOURCE mappedResource = {};
	refDeviceContext->Map(pixelShaderConstantBuffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mappedResource);
	memcpy(mappedResource.pData, &color, sizeof(Color));
	refDeviceContext->Unmap(pixelShaderConstantBuffer, 0u);
}
