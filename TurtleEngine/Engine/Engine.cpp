#include "PrecompiledHeader.h"
#include "Engine.h"
#include "Window.h"

Engine* Engine::instance = nullptr;

Engine::~Engine()
{
	SafeDelete(window);
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
	swapChainDesc.BufferCount = 1;
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
		device->QueryInterface()
		,TEXT("Failed to create device.")
	);
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

		}
	}
}

LRESULT Engine::MessageProcedure(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_DESTROY:
	{

	}
	break;
	case WM_SIZE:
	{

	}
	break;
	}
	return DefWindowProc(handle, message, wparam, lparam);
}
