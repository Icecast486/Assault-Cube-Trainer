// dllmain.cpp : Defines the entry point for the DLL application.

#include "pch.h"

#include "gamestructures.h"
#include "offsets.h"
#include "engine.h"
#include "aimbot.h"

DWORD WINAPI Init(HMODULE hModule);


DWORD WINAPI Init(HMODULE hModule)
{
    using namespace std;

    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    Engine::initializeEngine();

    Entity* localPlayer = Engine::getLocalPlayer();

    /* Toggles */
    bool bAimBot = false;
    bool bHealth = false;

    while (!GetAsyncKeyState(VK_END) & 1)
    {

        if (GetAsyncKeyState(VK_F1) & 1)
        {
            bHealth = !bHealth;

            if (bHealth)
            {
                std::cout << "health :: [on]\n";
            }

            else
            {
                std::cout << "health :: [off]\n";
            }
        }

        if (GetAsyncKeyState(VK_F2) & 1)
        {

            bAimBot = !bAimBot;

            if (bAimBot)
            {
                std::cout << "aimbot :: [on]\n";
            }

            else
            {
                std::cout << "aimbot :: [off]\n";
            }
        }


        if (bHealth)
        {
            localPlayer->mHealth = 7777;
            localPlayer->mCurrentWeaponAmmo = 7777;
        }

        if (bAimBot)
        {
            Aimbot::execute();
        }
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
