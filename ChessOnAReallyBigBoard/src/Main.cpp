#include "Core/Engine/Engine.h"

int main()
{
    Engine* GEngine = new Engine();
    GEngine->Run();
    delete GEngine;

    return 0;
}