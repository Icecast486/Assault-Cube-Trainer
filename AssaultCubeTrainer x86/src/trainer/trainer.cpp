#include "trainer.h"

#include "../game/game.h"
#include "../dep/minhook/include/MinHook.h"

#include "../game/offsets.h"



void trainer::setup_trainer(HMODULE module) 
{
	AllocConsole();

	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	if (!f) return;

	assault_game::module_base = reinterpret_cast<uintptr_t>(GetModuleHandle(L"ac_client.exe"));

	if (!assault_game::module_base) {
		std::cout << "[!] Failed to get module base!\n";
		return;
	}

	initialize_hooks();
	initialize_trainer();

	while (!GetAsyncKeyState(VK_END)) { Sleep(250); }

	std::cout << "[i] Unhooking...\n";
	menu::shutdown();
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	

	Sleep(250);
	MH_Uninitialize();

	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(module, 0);
}



void trainer::initialize_trainer() 
{
	assault_game::get_local_player();
	assault_game::get_entity_list();
	assault_game::get_max_players();
	assault_game::get_view_matrix();

	assault_game::global::g_gamemode = *reinterpret_cast<uintptr_t*>(assault_game::module_base + OFFSET_GAMEMODE);
	std::cout << assault_game::global::g_gamemode << std::endl;
}



bool trainer::initialize_hooks() 
{
	MH_Initialize();

	const auto open_gl = GetModuleHandle(L"opengl32.dll");
	const auto sdl2 = GetModuleHandle(L"SDL2.dll");

    if (!open_gl) {
        std::cout << "[!] opengl32.dll not found!\n";
        return false;
    }

    if (!sdl2) {
        std::cout << "[!] SDL2.dll not found!\n";
    }

    /* initialize sdl_set_relative_mouse_mode*/
    assault_game::original_function::o_SDL_SetRelativeMouseMode =  
        reinterpret_cast<assault_game::SDL_SetRelativeMouseMode_t>(GetProcAddress(sdl2, "SDL_SetRelativeMouseMode"));
    
    MH_CreateHook(
        GetProcAddress(open_gl, "wglSwapBuffers"),
        reinterpret_cast<LPVOID>(assault_game::hook::hk_wglSwapBuffers),
        reinterpret_cast<LPVOID*>(&assault_game::original_function::o_wglSwapBuffers)
    );

	//MH_CreateHook(
	//	reinterpret_cast<LPVOID>(assault_game::module_base + OFFSET_DODAMAGEWRAPPER),
	//	reinterpret_cast<LPVOID>(assault_game::hook::hk_doDamageWrapper),
	//	reinterpret_cast<LPVOID*>(&assault_game::original_function::o_doDamageWrapper)
	//);

	MH_EnableHook(MH_ALL_HOOKS);

    std::cout << std::hex << "Address of module base   = 0x" << assault_game::module_base << "\n";

    menu::initialize();

    return true;
}