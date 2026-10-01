#include <windows.h>
#include <iostream>

#include "game.h"

#include "../features/visuals/esp.h"

#include "../trainer/trainer.h"
#include "../game/offsets.h"



/* wglSwapBuffers*/
BOOL __stdcall assault_game::hook::hk_wglSwapBuffers(HDC hDc) {

    if (GetAsyncKeyState(VK_INSERT) & 1)
        menu::toggle();

    if (menu::menu_is_open)
        menu::start_menu();

    if (menu::features::visuals::b_esp)
        esp::BeginESPDraw(hDc);

    if (menu::features::player::b_god_mode)
        assault_game::global::g_local_player->Health = 90909;

    if (menu::features::player::b_infinit_ammo && (global::g_local_player->pCurretnWeapon != nullptr) )
        *(assault_game::global::g_local_player->pCurretnWeapon->pClip) = 90909;
	
	return original_function::o_wglSwapBuffers(hDc);
}



void __stdcall assault_game::hook::hk_doDamageWrapper(int weapon_dmg, int hit_ent, int shooter_ent, unsigned int param_4, BYTE param_5, char param_6, char param_7) {
    std::cout << "An ent was hit\n";
    assault_game::original_function::o_doDamageWrapper(weapon_dmg, hit_ent, shooter_ent, param_4, param_5, param_6, param_7);
}



/* CallWindowProc */
LRESULT __stdcall assault_game::hook::hk_CallWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (menu::menu_is_open) {
        if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam)) /* handle the menu input */
            return 0;

        switch (uMsg) {
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_CHAR:
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
            return 0;
        }
    }

    return CallWindowProc(menu::o_window_process, hwnd, uMsg, wParam, lParam);
}




bool assault_game::is_team_game() {
    assault_game::global::g_gamemode = *reinterpret_cast<uintptr_t*>(assault_game::module_base + OFFSET_GAMEMODE);
    GAMETYPE current_mode = (GAMETYPE)assault_game::global::g_gamemode;

    switch (current_mode)
    {
    case NONE:
        return false;
        break;
    case TEAM_DEATHMATCH:
        return true;
        break;
    case FREE_FOR_ALL:
        return false;
        break;
    case ONE_SHOT_ONE_KILL:
        return false;
        break;
    case LAST_SWISS_STANDING:
        return false;
        break;
    case TEAM_SURVIVOR:
        return true;
        break;
    case TEAM_ONE_SHOT_ONE_KILL:
        return true;
        break;
    default:
        break;
    }

    return false;
}




/* I don't like the way I did this... */
/* TODO: Change this shiii... */
Entity* assault_game::get_local_player() {
    global::g_local_player = *reinterpret_cast<Entity**>(module_base + OFFSET_LOCALENT);

    if (global::g_local_player == nullptr) {
        return nullptr;
    }

    return global::g_local_player;
}



float* assault_game::get_view_matrix() {
    global::g_view_matrix = reinterpret_cast<float*>(module_base + OFFSET_VIEWMATRIX);

    if (global::g_view_matrix == nullptr) {
        return nullptr;
    }

    return global::g_view_matrix;
}



EntityList* assault_game::get_entity_list() {
    global::g_entity_list = *reinterpret_cast<EntityList**>(module_base + OFFSET_ENTLIST);
    
    if (global::g_entity_list == nullptr) {
        return nullptr;
    }

    return global::g_entity_list;
}


uint32_t assault_game::get_max_players() {
    global::g_max_players = *reinterpret_cast<uint32_t*>(module_base + OFFSET_MAXPLAYERS);
    return global::g_max_players;
}