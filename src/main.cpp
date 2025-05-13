#include "Core/Application.h"

int main()
{
    Application app;
    if (!app.Init(800, 600, "Model Viewer"))
        return -1;

    app.Run();
    return 0;
}
