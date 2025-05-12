cmake_minimum_required(VERSION 3.10)
project(MyEngine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glfw)

include_directories(
    external/glfw/include
    external/glad/include
)

add_executable(MyEngine
    src/main.cpp
    external/glad/src/glad.c
)

target_link_libraries(MyEngine glfw)
if (APPLE)
    target_link_libraries(MyEngine "-framework OpenGL")
elseif (WIN32)
    target_link_libraries(MyEngine opengl32)
else()
    target_link_libraries(MyEngine GL)
endif()
