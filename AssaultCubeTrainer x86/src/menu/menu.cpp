#include "menu.h"

#include "../dep/imgui/imgui_internal.h"



void menu::initialize() 
{
	if (!menu_initialized) {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        game_window = FindWindowA(NULL, "AssaultCube");
        o_window_process = (WNDPROC)SetWindowLongPtr(game_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(assault_game::hook::hk_CallWindowProc));

        ImGui_ImplWin32_Init(menu::game_window);
        ImGui_ImplOpenGL2_Init();
        menu::set_color_style();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

        menu_initialized = true;
	}
}



void menu::start_menu() 
{
    if (menu_is_open) {
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplWin32_NewFrame();

        ImGui::NewFrame();

        render();
        ImGui::Render();

        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    }
}


void menu::toggle() 
{
    menu_is_open = !menu_is_open;
    ImGuiIO& io = ImGui::GetIO();

    io.WantCaptureMouse = menu_is_open;
    io.WantCaptureKeyboard = menu_is_open;
    io.MouseDrawCursor = menu_is_open;

    assault_game::original_function::o_SDL_SetRelativeMouseMode(!menu_is_open); /* unlock/lock that mouse */
}


void menu::shutdown() 
{
    SetWindowLongPtr(menu::game_window, GWLP_WNDPROC, (LONG_PTR)o_window_process);

    if (menu_is_open)
        menu_is_open = false;

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}


void menu::render()
{
    ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_Once);
    ImGui::Begin("AssaultCube Trainer x86 - Icecast486", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    ImGuiColorEditFlags color_picker_flags =
        ImGuiColorEditFlags_NoInputs |
        ImGuiColorEditFlags_NoLabel |
        ImGuiColorEditFlags_NoAlpha |      // drop the alpha bar too
        ImGuiColorEditFlags_PickerHueWheel; // wheel + triangle instead of square + ba


    if (ImGui::BeginTabBar("Tabs")) {

        if (ImGui::BeginTabItem("Aimbot")) {
            ImGui::SeparatorText(" - Aimbot - ");

            ImGui::Checkbox("Aimbot", &features::aimbot::b_aimbot);
            ImGui::Checkbox("Smoothing", &features::aimbot::b_smoothing);

            if (features::aimbot::b_smoothing) {
                ImGui::SameLine();
                ImGui::SliderFloat("##SmoothAmount", &features::aimbot::f_smoothing, 1, 10);
            }

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Player")) {
            ImGui::SeparatorText(" - Player - ");

            ImGui::Checkbox("Infinite Health", &features::player::b_god_mode);
            ImGui::Checkbox("Infinite Ammo", &features::player::b_infinit_ammo);

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Visuals")) {

            ImGui::SeparatorText(" - Visuals - ");

            ImGui::Checkbox("ESP", &features::visuals::b_esp);

            if (features::visuals::b_esp) {

                ImGui::Checkbox("Box", &features::visuals::b_box);

                ImGui::SameLine();
                ImGui::ColorEdit4("##Enemy Color", reinterpret_cast<float*>(&features::visuals::t_box_color), color_picker_flags); // temp
                ImGui::SameLine();
                ImGui::ColorEdit4("##Team Color", reinterpret_cast<float*>(&features::visuals::t_team_box_color), color_picker_flags); // temp

                ImGui::Checkbox("Name", &features::visuals::b_name);
                ImGui::SameLine();
                ImGui::ColorEdit4("##Name Color", reinterpret_cast<float*>(&features::visuals::t_name_color), color_picker_flags); // temp

                ImGui::Checkbox("Health", &features::visuals::b_health);
            }

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Exploits")) {
            ImGui::SeparatorText(" - Exploits - ");
            ImGui::Text("There are currently none :(");
            //ImGui::Checkbox("instant kill", &features::exploits::b_instant_kill);
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }


    /* convert to glbyte so that we can assign it to a glcolor */
    vec4_to_glbyte(features::visuals::t_box_color, features::visuals::box_color);
    vec4_to_glbyte(features::visuals::t_team_box_color, features::visuals::team_box_color);
    vec4_to_glbyte(features::visuals::t_name_color, features::visuals::name_color);

    ImGui::End();
}



/* STYLE FUNCTIONS */
void menu::set_color_style() {

    return;
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowBorderSize = 5;
    style.ScrollbarRounding = 0;
    style.ScrollbarSize = 11;
    style.FramePadding = ImVec2(12, 2);
    style.ItemInnerSpacing = ImVec2(13, 4);

    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.05f, 0.11f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.29f, 0.03f, 0.21f, 0.52f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.06f, 0.13f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.21f, 0.08f, 0.17f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.13f, 0.05f, 0.11f, 0.81f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.05f, 0.11f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.13f, 0.05f, 0.11f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.05f, 0.11f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.71f, 0.25f, 0.57f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.71f, 0.25f, 0.57f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.71f, 0.25f, 0.57f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.25f, 0.57f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.71f, 0.25f, 0.57f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.71f, 0.25f, 0.57f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.71f, 0.25f, 0.57f, 0.51f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.71f, 0.25f, 0.57f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.71f, 0.25f, 0.57f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.24f, 0.09f, 0.20f, 1.00f);
    colors[ImGuiCol_TabSelected] = ImVec4(0.53f, 0.19f, 0.43f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.22f, 0.09f, 0.19f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.29f, 0.03f, 0.21f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.13f, 0.05f, 0.11f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.13f, 0.05f, 0.11f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.13f, 0.05f, 0.11f, 1.00f);
}


bool menu::custom_elements::square_checkbox(const char* label, bool* v)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *ImGui::GetCurrentContext();
    const ImGuiStyle& style = g.Style;
    ImGuiID id = window->GetID(label);
    float size = ImGui::GetFrameHeight();
    ImVec2 pos = window->DC.CursorPos;

    // Extend the bounding box to include the label
    ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
    ImRect total_bb(pos, ImVec2(pos.x + size + style.ItemInnerSpacing.x + label_size.x, pos.y + size));

    // Separate rect just for the square (for drawing)
    ImRect check_bb(pos, ImVec2(pos.x + size, pos.y + size));

    ImGui::ItemSize(total_bb, style.FramePadding.y);
    if (!ImGui::ItemAdd(total_bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held); // use total_bb so label is clickable
    if (pressed)
        *v = !(*v);

    // Draw checkbox background
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImU32 col = ImGui::GetColorU32(
        (held && hovered) ? ImGuiCol_FrameBgActive
        : hovered ? ImGuiCol_FrameBgHovered
        : ImGuiCol_FrameBg);
    draw_list->AddRectFilled(check_bb.Min, check_bb.Max, col, style.FrameRounding);
    draw_list->AddRect(check_bb.Min, check_bb.Max, ImGui::GetColorU32(ImGuiCol_Border));

    // Draw checkmark when checked
    if (*v) {
        float pad = size * 0.25f;
        ImVec2 min = ImVec2(check_bb.Min.x + pad, check_bb.Min.y + pad);
        ImVec2 max = ImVec2(check_bb.Max.x - pad, check_bb.Max.y - pad);
        draw_list->AddRectFilled(min, max, ImGui::GetColorU32(ImGuiCol_CheckMark));
    }

    // Draw label manually (no SameLine needed since we're managing layout ourselves)
    ImVec2 label_pos = ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, pos.y + style.FramePadding.y);
    draw_list->AddText(label_pos, ImGui::GetColorU32(ImGuiCol_Text), label);

    return pressed;
}
void menu::custom_elements::right_aligned_colorselector(const char* id, ImVec4* color, float width, float height)
{
    ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - width);
    menu::custom_elements::rect_colors_selector(id, color, ImVec2(width, height));
}
bool menu::custom_elements::rect_colors_selector(const char* label, ImVec4* color, ImVec2 rect_size)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *ImGui::GetCurrentContext();
    const ImGuiStyle& style = g.Style;
    ImGuiID id = window->GetID(label);
    ImVec2 pos = window->DC.CursorPos;

    ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
    ImRect bb(pos, ImVec2(pos.x + rect_size.x + style.ItemInnerSpacing.x + label_size.x, pos.y + rect_size.y));

    ImGui::ItemSize(bb, style.FramePadding.y);
    if (!ImGui::ItemAdd(bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);

    // Open color picker popup when clicked
    if (pressed)
        ImGui::OpenPopup(label);

    // Draw the color rectangle
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImRect color_bb(pos, ImVec2(pos.x + rect_size.x, pos.y + rect_size.y));

    // Checkerboard background (for alpha visibility)
    ImU32 checker_col1 = IM_COL32(100, 100, 100, 255);
    ImU32 checker_col2 = IM_COL32(160, 160, 160, 255);
    int checker_size = 5;
    for (int y = (int)color_bb.Min.y; y < (int)color_bb.Max.y; y += checker_size) {
        for (int x = (int)color_bb.Min.x; x < (int)color_bb.Max.x; x += checker_size) {
            bool odd = ((x / checker_size) + (y / checker_size)) % 2;
            ImVec2 cmin = ImVec2((float)x, (float)y);
            ImVec2 cmax = ImVec2(ImMin((float)(x + checker_size), color_bb.Max.x),
                ImMin((float)(y + checker_size), color_bb.Max.y));
            draw_list->AddRectFilled(cmin, cmax, odd ? checker_col2 : checker_col1);
        }
    }

    // Draw the color on top
    draw_list->AddRectFilled(color_bb.Min, color_bb.Max, ImGui::ColorConvertFloat4ToU32(*color), style.FrameRounding);

    // Border — highlight on hover
    ImU32 border_col = ImGui::GetColorU32(hovered ? ImGuiCol_BorderShadow : ImGuiCol_Border);
    draw_list->AddRect(color_bb.Min, color_bb.Max, border_col, style.FrameRounding, 0, hovered ? 2.0f : 1.0f);

    // Draw label
    ImVec2 label_pos = ImVec2(color_bb.Max.x + style.ItemInnerSpacing.x, pos.y + style.FramePadding.y);
    draw_list->AddText(label_pos, ImGui::GetColorU32(ImGuiCol_Text), label);

    // Color picker popup
    bool changed = false;
    ImGui::SetNextWindowPos(ImVec2(color_bb.Min.x, color_bb.Max.y + style.ItemSpacing.y), ImGuiCond_Appearing);
    if (ImGui::BeginPopup(label)) {
        changed = ImGui::ColorPicker4(label, (float*)color,
            ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview);
        ImGui::EndPopup();
    }

    return changed;
}
