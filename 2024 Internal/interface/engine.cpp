#include <iostream>
#include <Windows.h>
#include <stdexcept>

#include "engine.h"
#include "../hacks/esp.h"
#include "../memory/offsets.h"



namespace Test
{
	inline Aimbot* aimbot;
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
	viewMatrix = (float*)(moduleBase + OFFSET_VIREMATRIX);

	if (localPlayer == nullptr)
	{
		std::cout << "[!] LocalPlayer not found, aborting!" << std::endl;
		return false;
	}
	
	
	if (entityList == nullptr)
	{
		std::cout << "[!] EntityList not found, aborting!" << std::endl;
		std::cout << "[i] Make sure you're in a game when injecting!" << std::endl;
		return false;
	}
	
	
	if (viewMatrix == nullptr)
	{
		std::cout << "[!] ViewMatrix not found, aborting!" << std::endl;
		return false;
	}

	/* Initializing Hacks */
	Test::aimbot = new Aimbot;

	std::cout << "[i] Initialized Engine!" << std::endl;

	return true;
}


bool Engine::addHook(const char* exportName, const char* modName, BYTE* dst, BYTE* PtrToGatewayFnPtr, size_t len)
{
	Hook newHook{ exportName, modName, dst, PtrToGatewayFnPtr, len };
	hooks.emplace_back(newHook);
	return true;
}


bool Engine::addHook(Hook& newHook)
{
	hooks.emplace_back(newHook);
	return true;
}


bool Engine::initializeHooks()
{
	/* hook som functions :O */
	Engine::addHook("wglSwapBuffers", "opengl32.dll", (BYTE*)hkwglSwapBuffers, (BYTE*)&Engine::wglSwapBuffersGateway, 5);

	for (Hook& h : hooks)
		h.Enable();

	return true;
}


Entity* Engine::getLocalPlayer()
{
	if (localPlayer == nullptr)
	{
		std::cout << "[!] LocalPlayer not found, aborting!" << std::endl;
		return nullptr;
	}

	return localPlayer;
}


int Engine::getMaxPlayers()
{
	return maxPlayers;
}

float* Engine::getViewMatrix()
{
	return viewMatrix;
}


EntityList* Engine::getEntityList()
{
	return entityList;
}


bool Engine::unhook()
{
	for (Hook& h : hooks)
		h.Disable();

	/* deleting cheats */
	delete Test::aimbot;

	return true;
}



void Draw()
{
	GL::Font glFont;
	const int FONT_HEIGHT = 15;
	const int FONT_WIDTH = 9;

	const char* example = "ESP Box";
	const char* example2 = "Why Would I crash?";

	HDC currentHDC = wglGetCurrentDC();

	/* if the font isn't built, build it */
	if (!glFont.bBuilt || currentHDC != glFont.hdc)
	{
		glFont.Build(FONT_HEIGHT);
	}

	ESP esp;

	GL::SetUpOrtho();

	esp.Draw(glFont);

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
		Test::aimbot->toggle();

		if (Test::aimbot->isActive())
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

		if (bESP)
		{
			cout << "[ACTIVE] ESP activated!" << endl;
		}
		else
		{
			cout << "[DISABLE] ESP disabled!" << endl;
		}
	}

	if (Test::aimbot->isActive())
	{
		Test::aimbot->execute();
	}

	if (bGodMode)
	{
		localPlayer->mHealth = 7777;
	}

	if (bInfiniteAmmo)
	{
		localPlayer->mCurrentWeaponAmmo = 7777;
		localPlayer->mCurrentWeaponReserve = 7777;
	}
	
	if (bESP)
	{
		Draw();
	}

	return Engine::wglSwapBuffersGateway(hDc); /* run stolen bytes */
}