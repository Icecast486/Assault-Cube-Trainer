#include "menu.h"


void menu::toggle()
{
    menu::isOpen = !menu::isOpen;

    ImGuiIO& io = ImGui::GetIO();

    io.WantCaptureMouse = menu::isOpen;
    io.WantCaptureKeyboard = menu::isOpen;
    io.MouseDrawCursor = menu::isOpen;
    Engine::oSDL_SetRelativeMouseMode(!menu::isOpen); /* unlock that mouse */
}


void menu::initialize(HDC hDc)
{
    if (!initialized)
    {
        // Initialize ImGui context
        ImGui::CreateContext();
        io = ImGui::GetIO();

        HWND hwnd = WindowFromDC(hDc);

        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplOpenGL2_Init();
        ImGui::StyleColorsDark();

        //ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

        initialized = true;
    }
}

void menu::startMenu(HDC hDc)
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
    if (menu::isOpen)
    {
        ImGui::SetNextWindowSize(ImVec2(400, 300));
        ImGui::Begin("AssaultCube Trainer - OpenGL");

        ImGui::Separator();
        ImGui::Text("Player");
        ImGui::Checkbox("GodMod", &bGodMode);
        ImGui::Checkbox("Infinite Ammo", &bInfiniteAmmo);

        ImGui::Separator();
        ImGui::Text("Aim");
        ImGui::Checkbox("Aimbot", &bAimbot);

        ImGui::Separator();
        ImGui::Text("Visuals");
        ImGui::Checkbox("ESP", &bEsp);

        ImGui::End();
    }
}



LRESULT CALLBACK hkWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}