#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

class Camera;
class UIManager
{
public:
    static void Init(GLFWwindow *window);
    static void BeginFrame();
    static void EndFrame();
    static void Shutdown();
    static void RenderMainUI();

    static void Log(const std::string &message);

    static void SetCamera(Camera *camera); // 👈 nuevo

private:
    static inline std::vector<std::string> s_LogMessages;
    static inline bool s_ShowConsole = true;
    static inline char s_InputBuffer[256] = "";

    // Nuevo: Procesar comandos escritos
    static void ExecuteCommand(const std::string &command);
    static Camera *s_Camera;
};
