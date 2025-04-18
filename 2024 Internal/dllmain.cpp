// dllmain.cpp : Defines the entry point for the DLL application.

#include <Windows.h>
#include <iostream>

#include "interface/engine.h"


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

    while (true) {  }

    cout << "[i] Unhooking." << endl;

    fclose(f);
    FreeLibraryAndExitThread(hModule, 0);

    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        HANDLE Thread = CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(Init), hModule, NULL, NULL);
        if (Thread)
        {
            CloseHandle(Thread);
        }
        break;
    }
    case DLL_PROCESS_DETACH:
        Engine::unhook();
        FreeConsole();
        break;
    }

    return TRUE;

}
