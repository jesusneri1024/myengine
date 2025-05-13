#include <glad/glad.h>
#include "Core/Application.h"

int main()
{
    Application app;
    if (!app.Init(800, 600, "Game Engine (Neri)"))
        return -1;

    app.Run();
    return 0;
}
