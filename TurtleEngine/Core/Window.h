#pragma once
#include <CommonDefine.h>

class Window
{
public:
	Window(const wchar_t* name, uint32 width, uint32 height, WNDPROC windowProcedure);
	~Window();

	const wchar_t* Name() const { return name; }
	uint32 Width() const { return width; }
	uint32 Height() const { return height; }

	void SetWidth(uint32 width);
	void SetHeight(uint32 height);
	void SetWidthAndHeight(uint32 width, uint32 height);

	HINSTANCE Instance() const { return instance; }
	HWND Handle() const { return handle; }

private:
	wchar_t* name = nullptr;
	uint32 width = 0u;
	uint32 height = 0u;

	HINSTANCE instance = nullptr;
	HWND handle = nullptr;
};

