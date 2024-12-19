#include <iostream>
#include <Windows.h>
#include <stdexcept>
#include <iomanip>

#include "engine.h"
#include "../hacks/esp.h"
#include "../memory/offsets.h"

/* 
	This is where is goes down!!! :O

	TRANCELINE FUNCTION 0x004CA250
*/

namespace Features
{
	inline Aimbot* aimbot;
	inline ESP* esp;
}



bool Engine::initializeEngine()
{
	std::cout << "[i] Initializing Engine..." << std::endl;

	moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");



	if (moduleBase == NULL)
	{
		std::cout << "[!] Module base is null!" << std::endl;
		return false;
	}

	/* initialize variables */
	localPlayer = *(Entity**)(moduleBase + OFFSET_LOCALENT);
	entityList = *(EntityList**)(moduleBase + OFFSET_ENTLIST);
	maxPlayers = *(int*)(moduleBase + OFFSET_MAXPLAYERS);
	viewMatrix = (float*)(moduleBase + OFFSET_VIEWMATRIX);

	if (localPlayer == nullptr)
	{
		std::cout << "[!] LocalPlayer not found, aborting!" << std::endl;
		return false;
	}

	/* Initializing Hacks */
	Features::aimbot = new Aimbot;
	Features::esp = new ESP;

	std::cout << "[i] Initialized Engine!" << std::endl;

	return true;
}
bool Engine::addHook(const char* exportName, const char* modName, BYTE* dst, BYTE* PtrToGatewayFnPtr, size_t len)
{
	Hook* newHook = new Hook{ exportName, modName, dst, PtrToGatewayFnPtr, len };
	hooks.emplace_back(newHook);
	return true;
}
bool Engine::addHook(Hook* newHook)
{
	hooks.emplace_back(newHook);
	return true;
}
bool Engine::unhook()
{
	/* deleting features */
	delete Features::aimbot;
	delete Features::esp;

	for (Hook* h : hooks) {
		h->Disable();
		delete h;
	}

	return true;
}
bool Engine::initializeHooks()
{
	/* hook som functions :O */
	Engine::addHook("wglSwapBuffers", "opengl32.dll", (BYTE*)hkwglSwapBuffers, (BYTE*)&Engine::wglSwapBuffersGateway, 5);

	for (Hook* h : hooks) {
		h->Enable();
	}

	return true;
}

Entity* Engine::getLocalPlayer()
{
	if (localPlayer == nullptr)
	{
		localPlayer = *(Entity**)(moduleBase + OFFSET_LOCALENT);
		std::cout << "[!] LocalPlayer not found, trying to get it.." << std::endl;
		return localPlayer;
	}

	return localPlayer;
}
int Engine::getMaxPlayers()
{
	maxPlayers = *(int*)(moduleBase + OFFSET_MAXPLAYERS);
	return maxPlayers;
}
float* Engine::getViewMatrix()
{
	viewMatrix = (float*)(moduleBase + OFFSET_VIEWMATRIX);
	return viewMatrix;
}
EntityList* Engine::getEntityList()
{
	entityList = *(EntityList**)(moduleBase + OFFSET_ENTLIST);
	return entityList;
}


void Draw()
{
	GL::Font glFont;
	const int FONT_HEIGHT = 15;
	const int FONT_WIDTH = 9;

	HDC currentHDC = wglGetCurrentDC();

	/* if the font isn't built, build it */
	if (!glFont.bBuilt || currentHDC != glFont.hdc)
	{
		glFont.Build(FONT_HEIGHT);
	}

	GL::SetUpOrtho();

	Features::esp->Draw(glFont);

	GL::RestoreGL();
}

bool bGodMode = false;
bool bInfiniteAmmo = false;
bool bESP = false;

BOOL __stdcall hkwglSwapBuffers(HDC hDc)
{
	using namespace std;

	Entity* localPlayer = Engine::getLocalPlayer();
	
	if (GetAsyncKeyState(VK_F1) & 1)
	{
		bGodMode = !bGodMode;

		if (bGodMode)
		{
			cout << "[ACTIVE] Infinite Health activated!" << endl;
		}
		else
		{
			cout << "[DISABLE] Infinite Health  disabled!" << endl;
		}
	}	

	if (GetAsyncKeyState(VK_F2) & 1)
	{
		bInfiniteAmmo = !bInfiniteAmmo;

		if (bInfiniteAmmo)
		{
			cout << "[ACTIVE] Infinite Ammo activated!" << endl;
		}
		else
		{
			cout << "[DISABLE] Infinite Ammo disabled!" << endl;
		}
	}
	
	if (GetAsyncKeyState(VK_F3) & 1)
	{
		Features::aimbot->toggle();

		if (Engine::getEntityList() == nullptr)
		{
			std::cout << "[!] You need to enter a game to enable aimbot!" << std::endl;
			Features::aimbot->toggle();
		}

		if (Features::aimbot->isActive())
		{
			cout << "[ACTIVE] Aimbot activated!" << endl;
		}
		else
		{
			cout << "[DISABLE] Aimbot disabled!" << endl;
		}
	}

	if (GetAsyncKeyState(VK_F4) & 1)
	{
		bESP = !bESP;

		if (Engine::getEntityList() == nullptr)
		{
			std::cout << "[!] You need to enter a game to enable ESP!" << std::endl;
			bESP = false;
		}

		if (bESP)
		{
			cout << "[ACTIVE] ESP activated!" << endl;
		}
		else
		{
			cout << "[DISABLE] ESP disabled!" << endl;
		}
	}

	if (Features::aimbot->isActive())
	{
		Features::aimbot->execute();
	}

	if (bGodMode)
	{
		localPlayer->iHealth = 7777;
	}

	if (bInfiniteAmmo)
	{
		*(int*)localPlayer->pCurretnWeapon->pClip = 999999;
	}

	if (bESP)
	{
		Draw();
	}

	return Engine::wglSwapBuffersGateway(hDc); /* run stolen bytes */
}