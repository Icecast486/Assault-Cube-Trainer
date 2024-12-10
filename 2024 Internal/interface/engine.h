#ifndef ENGINE_H
#define ENGINE_H

#include "../memory/gamestructures.h"
#include "../memory/mem.h"
#include "../opengl draw/glDraw.h"
#include "../hacks/aimbot.h"
#include <vector>

/* Engine is the brain of the cheat.. */


namespace Engine
{
	/* Hook prototypes */
	typedef BOOL(__stdcall* twglSwapBuffers) (HDC hDc);

	inline twglSwapBuffers wglSwapBuffersGateway;  /* the gateway to run stolen bytes */
	inline twglSwapBuffers wglSwapBuffers;         /* the original SwapBuffers */


	inline uintptr_t moduleBase;
	inline std::vector<Hook> hooks;

	/* Game Structures */
	inline Entity* localPlayer;
	inline EntityList* entityList;
	inline int maxPlayers;
	inline float* viewMatrix;


	bool initializeEngine();
	bool initializeHooks();

	bool addHook(const char* exportName, const char* modName, BYTE* dst, BYTE* PtrToGatewayFnPtr, size_t len);
	bool addHook(Hook& newHk);

	Entity* getLocalPlayer();
	EntityList* getEntityList();
	int getMaxPlayers();
	float* getViewMatrix();
	
	bool unhook();
};


/* swapbuffers stuff */
BOOL __stdcall hkwglSwapBuffers(HDC hDc);
void Draw();

#endif