cmake_minimum_required(VERSION 3.10)
project(MyEngine)

set(CMAKE_CXX_STANDARD 17)

# === Subdirectorios ===
add_subdirectory(external/glfw)
add_subdirectory(external/assimp)
add_subdirectory(external/imgui)  # <--- ImGui agregado

# === Include directories ===
include_directories(
    external/glfw/include
    external/glad/include
    external/glm
    external/assimp/include
    external/imgui                # <--- ImGui
    external/imgui/backends       # <--- ImGui backends
    src/Graphics     
    src/Model
    src/Scene
    src/Core
    src/UI
    src
)

# === Ejecutable ===
add_executable(MyEngine
    src/main.cpp
    src/Graphics/Shader.cpp  
    src/Graphics/Camera.cpp  
    src/Model/Model.cpp
    src/Model/Mesh.cpp  
    src/Core/Application.cpp  
    src/Core/InputManager.cpp  
    src/Scene/GameObject.cpp
    src/Scene/Scene.cpp
    src/Scene/SceneNivel1.cpp
    src/Scene/SceneNivel2.cpp
    src/UI/UIManager.cpp
    external/glad/src/glad.c
)

# === Librerías ===
target_link_libraries(MyEngine PRIVATE
    glfw
    assimp
    imgui  # <--- ImGui agregado
)

# === OpenGL según plataforma ===
if (APPLE)
    target_link_libraries(MyEngine PRIVATE "-framework OpenGL")
elseif (WIN32)
    target_link_libraries(MyEngine PRIVATE opengl32)
else()
    target_link_libraries(MyEngine PRIVATE GL)
endif()
