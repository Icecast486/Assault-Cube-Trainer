// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include "Entity.h"
#include "Offsets.h"


DWORD WINAPI Init(HMODULE hModule);

DWORD WINAPI Init(HMODULE hModule)
{
    using namespace std;

    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");

    Entity* localPlayer;

    while (!GetAsyncKeyState(VK_END) & 1)
    {
        localPlayer = *(Entity**)(moduleBase + OFFSET_LOCALENT);
        localPlayer->mHeatlh = 1000;

        cout << localPlayer->mPos << endl;
    }

        fclose(f);
        FreeConsole();
        FreeLibraryAndExitThread(hModule, 0);
        return 0;

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Init, hModule, 0, 0));
    }

    return TRUE;
}
