#include "PrecompiledHeader.h"
#include "Window.h"

Window::Window(const wchar_t* name, uint32 width, uint32 height, WNDPROC windowProcedure)
	: width(width), height(height)
{
	CopyWideString(&this->name, name);

	instance = GetModuleHandle(nullptr);
	
	WNDCLASSEX windowClass = {};
	windowClass.cbSize = sizeof(windowClass);
	windowClass.hInstance = instance;
	windowClass.lpszClassName = TEXT("TurtleEngineWindow");
	windowClass.style = CS_VREDRAW | CS_HREDRAW;
	windowClass.lpfnWndProc = windowProcedure;

	RegisterClassEx(&windowClass);

	RECT rect = { 0,0, static_cast<long>(width), static_cast<long>(height) };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;
	int positionX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
	int positionY = (GetSystemMetrics(SM_CXSCREEN) - windowHeight) / 2;

	handle = CreateWindow(
		windowClass.lpszClassName,
		this->name,
		WS_OVERLAPPEDWINDOW,
		positionX, positionY,
		windowWidth, windowHeight,
		nullptr,
		nullptr,
		instance,
		nullptr
	);

	ShowWindow(handle, SW_SHOW);
	UpdateWindow(handle);
}

Window::~Window()
{
	SafeDeleteArray(name);
}

void Window::SetWidth(uint32 width)
{
	this->width = width;
}

void Window::SetHeight(uint32 height)
{
	this->height = height;
}

void Window::SetWidthAndHeight(uint32 width, uint32 height)
{
	this->width = width;
	this->height = height;
}
