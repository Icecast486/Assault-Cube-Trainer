// dllmain.cpp : Defines the entry point for the DLL application.

#include <Windows.h>
#include <iostream>

#include "interface/engine.h"

DWORD WINAPI Init(HMODULE hModule);


DWORD WINAPI Init(HMODULE hModule)
{
    using namespace std;

    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    /* Initializes the moduleBase */
    if (!Engine::initializeEngine())
    {
        cout << "[!] See ya!" << endl;
        Sleep(5000);

        fclose(f);
        FreeConsole();
        FreeLibraryAndExitThread(hModule, 0);

        return 0;
    }

    Engine::initializeHooks();

    //while (!GetAsyncKeyState(VK_END)) { }
    while (true) { } /* doesnt exit thread due to a bug */

    cout << "[i] Unhooking." << endl;

    Engine::unhook();

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);

    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        const auto handle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Init, hModule, 0, 0);

        if (handle)
        {
            CloseHandle(handle);
        }
    }

    return TRUE;

}
