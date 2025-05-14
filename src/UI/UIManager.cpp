#include "UIManager.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <iostream>

void UIManager::Init(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void UIManager::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UIManager::EndFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UIManager::RenderMainUI()
{
    ImGui::Begin("Debug Panel");

    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    if (ImGui::Button("Hola mundo"))
    {
        std::cout << "¡Botón presionado!" << std::endl;
    }

    ImGui::End();
}
