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
	inline bool isOpen;
	inline bool initialized;

	inline bool bGodMode;
	inline bool bInfiniteAmmo;
	inline bool bAimbot;
	inline bool bEsp;

	inline ImGuiIO& io;

	void toggle();
	void initialize(HDC hDc);
    void startMenu(HDC hDc);
	void render();
} 

#endif // !MENU_H
