#pragma once
#include <CommonDefine.h>

class Engine
{
public:
	static Engine* GetInstance();
	void Initialize(const wchar_t* name, uint32 width, uint32 height);
	void Run();

	static LRESULT CALLBACK MessageProcedure(HWND handle, UINT message, WPARAM wparam, LPARAM lparam);

private:
	Engine() = default;

public:
	~Engine();

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

private:
	static Engine* instance;
	class Window* window = nullptr;
	bool isInitialized = false;

	// Scene Renderer Resources
	ID3D11Device* device = nullptr;
	ID3D11Debug* debug = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;
};
