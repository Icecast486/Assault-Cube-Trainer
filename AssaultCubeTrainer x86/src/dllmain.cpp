#define WIN32_LEAN_AND_MEAN            

#include <windows.h>
#include <iostream>

#include "trainer/trainer.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        const auto handle = CreateThread(
            nullptr,
            0,
            reinterpret_cast<LPTHREAD_START_ROUTINE>(trainer::setup_trainer),
            hModule,
            0,
            nullptr);

        if (!handle) {
            return FALSE;
        }

        CloseHandle(handle);
    }

    return TRUE;
}

