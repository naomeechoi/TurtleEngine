#pragma once

#include <Windows.h>
#include <comdef.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <d3d11.h>
#include <d3dcompiler.h>

#include <d2d1.h>
#include <dwrite.h>

#define ShowErrorMessage(message, reason)															\
	wchar_t buffer[256];																			\
	wsprintf(buffer, TEXT("[File: %s]\n[Line: %d]\n[Function: %s]\n[Message: %s]\n[Reason: %s]"),	\
		TEXT(__FILE__), __LINE__, TEXT(__FUNCTION__), message, reason);								\
	MessageBox(nullptr, buffer, L"Error", MB_OK);													\


#define ThrowIfFailed(result, message)						\
	if (FAILED(result))										\
	{														\
		_com_error error(result);							\
		ShowErrorMessage(message, error.ErrorMessage());	\
		__debugbreak();										\
	}														\

__forceinline void CopyWideString(wchar_t** destination, const wchar_t* source)
{
	size_t length = lstrlen(source);
	*destination = new wchar_t[length + 1];
	lstrcpyW(*destination, source);
}

template<typename Type>
void SafeDelete(Type*& pointer)
{
	if (pointer != nullptr)
	{
		delete pointer;
		pointer = nullptr;
	}
}

template<typename Type>
void SafeDeleteArray(Type*& pointer)
{
	if (pointer != nullptr)
	{
		delete[] pointer;
		pointer = nullptr;
	}
}

template<typename Type>
void SafeRelease(Type*& pointer)
{
	if (pointer != nullptr)
	{
		pointer->Release();
		pointer = nullptr;
	}
}