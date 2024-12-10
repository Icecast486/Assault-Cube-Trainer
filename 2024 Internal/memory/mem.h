#pragma once

#ifndef MEM_H
#define MEM_H

#include <Windows.h>

namespace Mem
{
	bool detour32(BYTE* src, BYTE* dst, size_t len);
	BYTE* TrampHook32(BYTE* src, BYTE* dst, size_t len);

	void patch(BYTE* dst, BYTE* src, size_t size);
	void Nop(BYTE* dst, size_t size);

	void patchEx(HANDLE hProc, BYTE* dst, BYTE* src, size_t size);
}

struct Hook
{
	bool bStatus{ false };
	BYTE* src{ nullptr };
	BYTE* dst{ nullptr };
	BYTE* PtrToGatewayFnPtr{ nullptr };
	size_t len{ 0 };

	BYTE originalBytes[10]{ 0 };

	Hook(BYTE* src, BYTE* dst, BYTE* PtrToGatewayPtr, size_t len);
	Hook(const char* exportName, const char* modName, BYTE* dst, BYTE* PtrTOGatewayPtr, size_t len);

	void Enable();
	void Disable();
	void Toggle();
};

#endif