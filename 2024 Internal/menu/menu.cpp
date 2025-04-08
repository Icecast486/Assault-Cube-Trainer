#include "menu.h"

#include "../hacks/game.h"


LRESULT CALLBACK hkWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void menu::toggle()
{
    menu::bIsOpen = !menu::bIsOpen;
    ImGuiIO& io = ImGui::GetIO();

    io.WantCaptureMouse = menu::bIsOpen;
    io.WantCaptureKeyboard = menu::bIsOpen;
    io.MouseDrawCursor = menu::bIsOpen;

    Engine::oSDL_SetRelativeMouseMode(!menu::bIsOpen); /* unlock that mouse */
}


void menu::initialize()
{
    if (!bInitialized)
    {
        // Initialize ImGui context
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        menu::gameWindow = FindWindowA(NULL, "AssaultCube");
        menu::origionalWindowProc = (WNDPROC)SetWindowLongPtr(menu::gameWindow, GWLP_WNDPROC, (LONG_PTR)hkWndProc);

        ImGui_ImplWin32_Init(menu::gameWindow);
        ImGui_ImplOpenGL2_Init();
        ImGui::StyleColorsDark();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

        bInitialized = true;
    }
}

void menu::startMenu()
{
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();
    menu::render();
    ImGui::Render();

    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void menu::render()
{
    if (menu::bIsOpen)
    {
        ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Once);
        ImGui::Begin("AssaultCube Trainer x86 - OpenGL", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        
        if (ImGui::BeginTabBar("Tabs")) /* Begin Tab Bar */
        {
           
            if (ImGui::BeginTabItem("Player"))
            {
                ImGui::SeparatorText("Player");
                ImGui::Checkbox("God Mode", &menu::bGodMode);
                ImGui::Checkbox("Infinite Ammo", &menu::bInfiniteAmmo);
                ImGui::EndTabItem();
            }


            if (ImGui::BeginTabItem("Aim"))
            {
                ImGui::SeparatorText("Aim");

                ImGui::Checkbox("Aimbot", &menu::bAimbot);
                ImGui::Separator();
                ImGui::EndTabItem();
            }


            if (ImGui::BeginTabItem("Visuals"))
            {
                ImGui::SeparatorText("Visuals");
                ImGui::Checkbox("ESP", &bEsp);
                ImGui::Separator();

                if (menu::bEsp) 
                {
                    ImGui::Checkbox("Box", &menu::bBoxEsp);
                    ImGui::Checkbox("Ammo", &menu::bAmmoEsp);
                    ImGui::Checkbox("Health", &menu::bHealthEsp);
                    ImGui::Checkbox("Name", &menu::bNameEsp);
					ImGui::Checkbox("Outline", &menu::bOutlineEsp);
                }

                ImGui::EndTabItem();
            }


            if (ImGui::BeginTabItem("Game"))
            {
                ImGui::SeparatorText("Game");
                ImGui::Text("Not Implemented");
                ImGui::EndTabItem();
            }
            
            
            if (ImGui::BeginTabItem("Misc"))
            {
                ImGui::SeparatorText("Miscellaneous");
                //ImGui::Checkbox("Debug Mode", &menu::bDebugMode);
                ImGui::Text("Not Implemented");
                ImGui::EndTabItem();
            }

			if (menu::bDebugMode)
			{
                if (ImGui::BeginTabItem("Debug"))
                {
                    ImGui::SeparatorText("Debug");

					ImGui::Text("View Matrix: %p", Engine::viewMatrix);

                    for (int i = 0; i < 16; i += 4)
                    {
						ImGui::Text("[%.1f] [%.1f] [%.1f] [%.1f]\n", i, Engine::viewMatrix[i], Engine::viewMatrix[i + 1], Engine::viewMatrix[i + 2], Engine::viewMatrix[i + 3]);
                    }

                    ImGui::EndTabItem();
                }
			}
            

            if (ImGui::BeginTabItem("Credits"))
            {
                ImGui::SeparatorText("AssaultCube Trainer x86");
                ImGui::LabelText("Icecast486", "Developer: ");

                ImGui::SeparatorText("Tanks :)");
                ImGui::Text("Thanks to Guided Hacking for giving me the knowledge\ntodo all of this!");

                ImGui::SeparatorText("https://github.com/Icecast486");

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar(); /* End Of Tab Bar */
        }

        ImGui::End();
    }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/* Ignore user input in the assult cube process */
LRESULT CALLBACK hkWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    if (menu::bIsOpen)
    {
        if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
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

    return CallWindowProc(menu::origionalWindowProc, hwnd, uMsg, wParam, lParam);
}