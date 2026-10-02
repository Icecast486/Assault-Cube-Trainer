#pragma once

#ifndef MENU_H
#define MENU_H

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "user32.lib")

#include <windows.h>
#include <gl/GL.h>

#include "../dep/imgui/imgui_impl_opengl2.h"
#include "../dep/imgui/imgui_impl_win32.h"
#include "../dep/imgui/imgui.h"

#include "../game/game.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

inline void vec4_to_glbyte(const ImVec4& col, GLubyte out[4]) {
	out[0] = (GLubyte)(col.x * 255.0f + 0.5f);
	out[1] = (GLubyte)(col.y * 255.0f + 0.5f);
	out[2] = (GLubyte)(col.z * 255.0f + 0.5f);
	out[3] = (GLubyte)(col.w * 255.0f + 0.5f);
}

namespace menu 
{
	inline HWND	   game_window;
	inline WNDPROC o_window_process;

	void toggle();
	void initialize();
	void start_menu();
	void render();
	void shutdown();
	void set_color_style();


	inline bool menu_initialized;
	inline bool menu_is_open;

	/* features */
	namespace features {
		namespace  player {
			inline bool b_god_mode;
			inline bool b_infinit_ammo;
		}

		namespace aimbot {
			inline bool b_aimbot;
			inline bool b_smoothing;

			inline float f_smoothing = 1.0f;
		}

		namespace visuals {

			inline ImVec4 t_box_color = { 1.0f, 0.0f, 0.0f, 1.0f };
			inline ImVec4 t_name_color = { 1.0f, 1.0f, 1.0f, 1.0f };
			inline ImVec4 t_team_box_color = { 0.0f, 1.0f, 0.0f, 1.0f };
			inline ImVec4 t_health_color = { 1.0f, 1.0f, 1.0f, 1.0f };

			/* converting to GLcolor */
			inline unsigned char box_color[4]{ 0, 0, 0, 255 };
			inline unsigned char name_color[4]{ 0, 0, 0, 255 };
			inline unsigned char team_box_color[4]{ 0, 0, 0, 255 };

						
			inline bool b_esp;
			inline bool b_name;
			inline bool b_box;
			inline bool b_health;
			inline bool b_health_color;
			inline bool b_ammo;
		}

		namespace exploits {
			inline bool b_instant_kill;
		}
	}


	namespace custom_elements {
		bool square_checkbox(const char* label, bool* v);
		bool rect_colors_selector(const char* label, ImVec4* color, ImVec2 rect_size);
		void right_aligned_colorselector(const char* id, ImVec4* color, float width = 30, float height = 15);
	};

}

#endif