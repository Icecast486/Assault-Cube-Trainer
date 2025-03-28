#ifndef MENU_H
#define MENU_H

#include <Windows.h>
#include <gl/GL.h>

#include "../interface/engine.h"
#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_impl_opengl2.h"
#include "../dependencies/imgui/imgui_impl_win32.h"

namespace menu
{
	inline WNDPROC origionalWindowProc;
	inline HWND gameWindow;
	

	inline bool bIsOpen;
	inline bool bInitialized;

	inline bool bGodMode;
	inline bool bInfiniteAmmo;
	inline bool bAimbot;

	inline bool bEsp;
	inline bool bBoxEsp;
	inline bool bHealthEsp;
	inline bool bNameEsp;

	void toggle();
	void initialize();
    void startMenu();
	void render();
} 

#endif // !MENU_H
