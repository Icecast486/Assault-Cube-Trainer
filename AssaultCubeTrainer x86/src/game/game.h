#pragma once

#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "../menu/menu.h"
#include "structures.h"

namespace assault_game {
	inline uintptr_t	   module_base{ NULL };

	using wglSwapBuffers_t = BOOL(__stdcall*)(HDC hDc);
	using CallWindowProc_t = LRESULT(__stdcall*)(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	using SDL_SetRelativeMouseMode_t = int(__cdecl*)(int bUnlockCursor);
	using doDamageWrapper_t = void(__stdcall*)(int weapon_dmg, int hit_ent, int shooter_ent, unsigned int param_4, BYTE param_5, char param_6, char param_7);

	namespace global {
		inline Entity*     g_local_player{ NULL };
		inline EntityList* g_entity_list{ NULL };
		inline uint32_t	   g_max_players{ NULL };
		inline float*	   g_view_matrix{ NULL };
		inline uint32_t    g_gamemode{ NULL };
	}


	/* Original Functions */
	namespace original_function {
		inline wglSwapBuffers_t			  o_wglSwapBuffers{ NULL };
		inline CallWindowProc_t			  o_CallWindowProc{ NULL };
		inline SDL_SetRelativeMouseMode_t o_SDL_SetRelativeMouseMode{ NULL };
		inline doDamageWrapper_t		  o_doDamageWrapper{ NULL };
	}


	/* Hook Functions */
	namespace hook {
		LRESULT __stdcall hk_CallWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		BOOL __stdcall hk_wglSwapBuffers(HDC hDc);
		void __stdcall hk_doDamageWrapper(int weapon_dmg, int hit_ent, int shooter_ent, unsigned int param_4, BYTE param_5, char param_6, char param_7);
	}


	Entity* get_local_player();
	EntityList* get_entity_list();
	float* get_view_matrix();
	uint32_t get_max_players();

	bool is_team_game();
}

#endif