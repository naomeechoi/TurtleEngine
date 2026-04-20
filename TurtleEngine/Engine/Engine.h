#pragma once
#include <CommonDefine.h>

class Engine
{
public:
	Engine(const wchar_t* name, uint32 width, uint32 height);
	~Engine();
	void Run();
};

