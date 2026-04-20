#pragma once
#include <CommonDefine.h>

class Window
{
public:
	Window(const wchar_t* name, uint32 width, uint32 height, WNDPROC windowProcedure);
	~Window();
};

