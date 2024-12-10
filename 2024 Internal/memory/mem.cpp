#include "mem.h"
#include <iostream>


void Mem::patch(BYTE* dst, BYTE* src, size_t size)
{
	DWORD oldProtect;

	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldProtect, &oldProtect);
}	



void Mem::Nop(BYTE* dst, size_t size)
{
	DWORD oldProtect;

	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldProtect, &oldProtect);
}



void Mem::patchEx(HANDLE hProc, BYTE* dst, BYTE* src, size_t size)
{
	DWORD oldProtect;

	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	WriteProcessMemory(hProc, dst, src, size, nullptr);
	VirtualProtect(dst, size, oldProtect, &oldProtect);
}


bool Mem::detour32(BYTE* src, BYTE* dst, size_t len)
{
	if (len < 5)
		return false;

	DWORD curProtection;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

	uintptr_t relativeAddress = dst - src - 5;

	*src = 0xE9;							  /* JMP ???? */
	*(uintptr_t*)(src + 1) = relativeAddress; /* writing the location to jump to */

	VirtualProtect(src, len, curProtection, &curProtection);

	return true;
}


BYTE* Mem::TrampHook32(BYTE* src, BYTE* dst, size_t len)
{
	if (len < 5)
		return 0;

	BYTE* gateway = (BYTE*)VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	memcpy_s(gateway, len, src, len);

	uintptr_t gatewayRelativeAddr = src - gateway - 5;

	*(gateway + len) = 0xE9;											/* writing the jump back to the funciton */
	*(uintptr_t*)((uintptr_t)gateway + len + 1) = gatewayRelativeAddr;  /* writing the address to the jump back */
	
	detour32(src, dst, len);

	return gateway;
}


/* hook functions */

Hook::Hook(BYTE* src, BYTE* dst, BYTE* PtrToGatewayFnPtr, size_t len) : src(src), dst(dst) , PtrToGatewayFnPtr(PtrToGatewayFnPtr), len(len) { }
Hook::Hook(const char* exportName, const char* modName, BYTE* dst, BYTE* PtrToGatewayFnPtr, size_t len) : dst(dst), PtrToGatewayFnPtr(PtrToGatewayFnPtr), len(len)
{
	std::cout << "[i] Attempting to get export from library [" << modName << "]" << std::endl;

	HMODULE hMod = GetModuleHandleA(modName);
	
	std::cout << "   [i] hMod " << modName << " [0x" << hMod << "]" << std::endl;
	std::cout << "   [i] procAddr " << exportName << " [0x" << GetProcAddress(hMod, exportName) << "]" << std::endl;

	this->src = (BYTE*)GetProcAddress(hMod, exportName);
}



void Hook::Enable()
{
	memcpy(originalBytes, src, len);
	*(uintptr_t*)PtrToGatewayFnPtr = (uintptr_t)Mem::TrampHook32(src, dst, len); /* returns the memory location of the gateway */
	bStatus = true;
}



void Hook::Disable()
{	
	Mem::patch(src, originalBytes, len);
	//VirtualFree(dst, len, MEM_DECOMMIT);
	bStatus = false;
}



void Hook::Toggle()
{
	if (!bStatus)
		Enable();
	else
		Disable();
}