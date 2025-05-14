#include "UIManager.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <iostream>
#include <InputManager.h>

Camera *UIManager::s_Camera = nullptr;

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
    ImGui::Text("Modo: %s", InputManager::IsCursorEnabled() ? "UI" : "Camara");

    if (ImGui::Button("Hola mundo"))
    {
        Log("¡Botón 'Hola mundo' presionado!");
    }

    static int renderMode = 0;
    const char *modes[] = {"Fill", "Wireframe", "Point"};
    if (ImGui::Combo("Render Mode", &renderMode, modes, IM_ARRAYSIZE(modes)))
    {
        switch (renderMode)
        {
        case 0:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case 1:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case 2:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            break;
        }
        Log(std::string("Render mode cambiado a: ") + modes[renderMode]);
    }

    if (ImGui::Button("Toggle Consola"))
    {
        s_ShowConsole = !s_ShowConsole;
    }

    if (s_Camera && ImGui::Button("Resetear Camara"))
    {
        // Esto reemplaza el estado actual con el inicial
        *s_Camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f),
                           -90.0f, 0.0f);
        UIManager::Log("Camara reseteada.");
    }

    ImGui::End();

    if (s_ShowConsole)
    {
        ImGui::Begin("Consola interna", &s_ShowConsole);

        // Mostrar historial
        for (const auto &line : s_LogMessages)
            ImGui::TextUnformatted(line.c_str());

        ImGui::Separator();

        // Input para comandos
        ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion;
        if (ImGui::InputText("Comando", s_InputBuffer, IM_ARRAYSIZE(s_InputBuffer), ImGuiInputTextFlags_EnterReturnsTrue))
        {
            std::string command = s_InputBuffer;
            Log("> " + command);
            ExecuteCommand(command);
            s_InputBuffer[0] = '\0';
            ImGui::SetKeyboardFocusHere(); // Vuelve a enfocar
        }

        if (ImGui::Button("Limpiar"))
            s_LogMessages.clear();

        ImGui::End();
    }
}

void UIManager::Log(const std::string &message)
{
    s_LogMessages.push_back(message);
}

void UIManager::ExecuteCommand(const std::string &command)
{
    if (command == "help")
    {
        Log("Comandos disponibles:");
        Log("  help      - Muestra esta ayuda");
        Log("  clear     - Limpia la consola");
        Log("  fps       - Muestra el FPS actual");
        Log("  mode      - Muestra el modo de cámara");
    }
    else if (command == "clear")
    {
        s_LogMessages.clear();
    }
    else if (command == "fps")
    {
        float fps = ImGui::GetIO().Framerate;
        Log("FPS: " + std::to_string(fps));
    }
    else if (command == "mode")
    {
        Log(std::string("Modo actual: ") + (InputManager::IsCursorEnabled() ? "UI" : "Cámara"));
    }
    else
    {
        Log("Comando no reconocido: " + command);
    }
}

void UIManager::SetCamera(Camera *cam)
{
    s_Camera = cam;
}