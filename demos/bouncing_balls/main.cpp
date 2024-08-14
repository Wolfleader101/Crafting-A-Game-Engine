#include "WindowSystem.hpp"
#include "BallSystem.hpp"

#include <vector>
#include <memory>

int main(void)
{
    std::shared_ptr<ISystem> windowSystem = std::make_shared<WindowSystem>();
    std::shared_ptr<ISystem> ballSystem = std::make_shared<BallSystem>();

    std::vector<std::shared_ptr<ISystem>> systems = {windowSystem, ballSystem};

    // pre init
    for (const auto &system : systems)
    {
        system->PreInit();
    }

    // init
    for (const auto &system : systems)
    {
        system->Init();
    }

    // post init
    for (const auto &system : systems)
    {
        system->PostInit();
    }

    // enter the game loop
    while (!WindowShouldClose())
    {
        // pre update
        for (const auto &system : systems)
        {
            system->PreUpdate();
        }

        // tick
        for (const auto &system : systems)
        {
            system->Tick();
        }

        // update
        for (const auto &system : systems)
        {
            system->Update();
        }

        // post update
        for (const auto &system : systems)
        {
            system->PostUpdate();
        }
    }

    // exit
    for (const auto &system : systems)
    {
        system->Exit();
    }
    return 0;
}
