#include "interface_system.h"

InterfaceSystem::~InterfaceSystem()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void InterfaceSystem::draw_interface()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Create a window called "My First Tool", with a menu bar.
    ImGui::Begin("Control Panel", &show_window);

    // Create an scene mode section
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Scene mode");
    ImGui::RadioButton("View", &scene_mode, View);
    ImGui::RadioButton("Create", &scene_mode, Create);
    ImGui::RadioButton("Edit", &scene_mode, Edit);
    ImGui::RadioButton("Move", &scene_mode, Move);

    ImGui::End();

    render();
}

void InterfaceSystem::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool InterfaceSystem::scene_mode_modified()
{
    bool modified = _psm != scene_mode;
    if (modified)
        prev_scene_mode = SceneMode(_psm);
    this->_psm = scene_mode;
    return modified;
}
