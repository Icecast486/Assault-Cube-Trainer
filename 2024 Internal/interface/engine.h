#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include "../memory/gamestructures.h"
#include "../memory/mem.h"
#include "../opengl draw/glDraw.h"
#include "../hacks/aimbot.h"
#include "../hacks/esp.h"
#include "../dependencies/minhook/include/MinHook.h"

/* Engine is the brain of the cheat.. */

BOOL __stdcall hkwglSwapBuffers(HDC hDc);

namespace Engine
{
	inline uintptr_t moduleBase;

	/* ----------- Hook prototypes ------------ */
	
	typedef BOOL(__stdcall* twglSwapBuffers) (HDC hDc);
	inline twglSwapBuffers owglSwapBuffers;

	typedef int(__cdecl* tSDL_SetRelativeMouseMode) (int bUnlockCursor);
	inline tSDL_SetRelativeMouseMode oSDL_SetRelativeMouseMode;
	
	/* ------------ Game Structures ------------ */

	inline Entity* localPlayer;
	inline EntityList* entityList;
	inline int maxPlayers;
	inline float* viewMatrix;

	Entity* getLocalPlayer();
	EntityList* getEntityList();
	int getMaxPlayers();
	float* getViewMatrix();

	/* ----------- Utiliy functions ----------- */

	bool initializeEngine();
	bool initializeHooks();
	bool unhook();

	/* ------------ Hacks ------------ */

	inline bool bGodMode = false;
	inline bool bInfiniteAmmo = false;
	inline bool aimbot = false;
	inline bool bESP = false;
};

#endif