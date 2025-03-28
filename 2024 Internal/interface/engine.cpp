#include <iostream>
#include <Windows.h>
#include <stdexcept>
#include <iomanip>

#include "engine.h"
#include "../menu/menu.h"
#include "../hacks/esp.h"
#include "../memory/offsets.h"

/* 
	This is where is goes down!!! :O
	TRANCELINE FUNCTION 0x004CA250
*/


Entity* Engine::getLocalPlayer() {

	if (localPlayer == nullptr) {
		localPlayer = *(Entity**)(moduleBase + OFFSET_LOCALENT);
		std::cout << "[!] LocalPlayer not found, trying to get it.." << std::endl;
		return localPlayer;
	}

	return localPlayer;
}
int Engine::getMaxPlayers() {
	maxPlayers = *(int*)(moduleBase + OFFSET_MAXPLAYERS);
	return maxPlayers;
}
float* Engine::getViewMatrix() {
	viewMatrix = (float*)(moduleBase + OFFSET_VIEWMATRIX);
	return viewMatrix;
}
EntityList* Engine::getEntityList() {
	entityList = *(EntityList**)(moduleBase + OFFSET_ENTLIST);
	return entityList;
}


bool Engine::initializeEngine()
{
	using namespace std;

	cout << "[i] Initializing Engine..." << endl;

	moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");

	if (moduleBase == NULL) {
		cout << "[!] Module base is null!" << endl;
		return false;
	}

	/* initialize variables */
	localPlayer = *(Entity**)(moduleBase + OFFSET_LOCALENT);
	entityList = *(EntityList**)(moduleBase + OFFSET_ENTLIST);
	maxPlayers = *(int*)(moduleBase + OFFSET_MAXPLAYERS);
	viewMatrix = (float*)(moduleBase + OFFSET_VIEWMATRIX);

	if (localPlayer == nullptr) {
		cout << "[!] LocalPlayer not found, aborting!" << endl;
		return false;
	}

	cout << "[i] Initialized Engine!" << endl;

	return true;
}



bool Engine::initializeHooks()
{
	MH_Initialize();

	HMODULE OpenGL = GetModuleHandle(L"opengl32.dll");
	HMODULE SDL2 = GetModuleHandle(L"SDL2.dll");

	if (OpenGL == NULL) {
		std::cout << "[!] OpenGL module not found!" << std::endl;
		return false;
	}

	if (SDL2 == NULL) {
		std::cout << "[!] SDL2 module not found!" << std::endl;
		return false;
	}

	oSDL_SetRelativeMouseMode = (tSDL_SetRelativeMouseMode)GetProcAddress(SDL2, "SDL_SetRelativeMouseMode");

	MH_CreateHook(
		GetProcAddress(OpenGL, "wglSwapBuffers"),
		reinterpret_cast<LPVOID>(hkwglSwapBuffers),
		reinterpret_cast<LPVOID*>(&Engine::owglSwapBuffers)
	);

	MH_EnableHook(MH_ALL_HOOKS);

	menu::initialize();

	return true;
}



bool Engine::unhook()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();
	return true;
}



BOOL __stdcall hkwglSwapBuffers(HDC hDc)
{
	using namespace std;

	if (GetAsyncKeyState(VK_INSERT) & 1)
		menu::toggle();

	if (menu::bGodMode)
		Engine::localPlayer->iHealth = 7777;
	
	if (menu::bInfiniteAmmo)
		*(int*)Engine::localPlayer->pCurretnWeapon->pClip = 7777;
	
	if (menu::bEsp)
		esp::BeginESPDraw();

	if (menu::bAimbot)
		aimbot::execute();

	menu::startMenu();

	return Engine::owglSwapBuffers(hDc);
}
