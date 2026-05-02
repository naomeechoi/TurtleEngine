#include "PrecompiledHeader.h"
#include "Engine.h"
#include "Window.h"

Engine* Engine::instance = nullptr;

Engine::~Engine()
{
	instance = nullptr;
	SafeDelete(window);
	SafeRelease(swapChain);
	SafeRelease(renderTargetView);
	SafeRelease(device);
	SafeRelease(deviceContext);
}

void Engine::BeginScene()
{
	float clearColor[4] = { 0.2f, 0.3f, 0.1f, 1.0f };
	deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
}

void Engine::UpdateViewport(uint32 width, uint32 height)
{
	viewport = {};
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
}

Engine* Engine::GetInstance()
{
	if (instance == nullptr)
		instance = new Engine();

	return instance;
}

void Engine::Initialize(const wchar_t* name, uint32 width, uint32 height)
{
	if (isInitialized)
		return;

	isInitialized = true;
	window = new Window(name, width, height, Engine::MessageProcedure);

	uint32 flag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if _DEBUG
	flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	ThrowIfFailed(
		D3D11CreateDevice(
			nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flag, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION, &device, nullptr, &deviceContext),
		TEXT("Failed to create device.")
	);

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = window->Handle();
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	
	IDXGIDevice* dxgiDevice = nullptr;
	ThrowIfFailed(
		device->QueryInterface(IID_PPV_ARGS(&dxgiDevice))
		,TEXT("Failed to create dxgiDevice."));

	IDXGIAdapter* dxgiAdapter = nullptr;
	ThrowIfFailed(
		dxgiDevice->GetParent(IID_PPV_ARGS(&dxgiAdapter))
		, TEXT("Failed to create dxgiAdapter."));

	IDXGIFactory* dxgiFactory = nullptr;
	ThrowIfFailed(
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory))
		, TEXT("Failed to create dxgiFactory.")
	);

	ThrowIfFailed(
		dxgiFactory->CreateSwapChain(device, &swapChainDesc, &swapChain),
		TEXT("Failed to create swap chain.")
	);

	SafeRelease(dxgiDevice);
	SafeRelease(dxgiAdapter);
	SafeRelease(dxgiFactory);

	ID3D11Texture2D* backBuffer = nullptr;
	ThrowIfFailed(
		swapChain->GetBuffer(0u, IID_PPV_ARGS(&backBuffer)),
		TEXT("Failed to create swapChain."));

	ThrowIfFailed(
		device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView),
		TEXT("Failed to create renderTargetView."));

	SafeRelease(backBuffer);
	deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);

	UpdateViewport(width, height);
}

void Engine::Run()
{
	MSG message = {};
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, nullptr, 0u, 0u, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			BeginScene();
			swapChain->Present(1, 0);
		}
	}
}

LRESULT Engine::MessageProcedure(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0); // 이걸 호출해야 Run()의 WM_QUIT이 작동합니다.
		return 0;
	}
	break;
	case WM_SIZE:
	{

	}
	break;
	}
	return DefWindowProc(handle, message, wparam, lparam);
}
