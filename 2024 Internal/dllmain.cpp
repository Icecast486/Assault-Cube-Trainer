// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL HackThread(HMODULE hModule);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        HANDLE hThread;

        hThread = CreateRemoteThread(NULL, nullptr, NULL, (LPTHREAD_START_ROUTINE)HackThread, hModule, NULL, NULL);

        if (hThread == NULL)
        {
            return FALSE;
        }

        return TRUE;
    }

    return FALSE;
}



BOOL HackThread(HMODULE hModule)
{
}
