#pragma once

#include "raylib.h"

#include "ISystem.hpp"

class WindowSystem : public ISystem
{
public:
    WindowSystem() {}
    ~WindowSystem() {}

    void PreInit()
    {
        // start the game
        InitWindow(800, 450, "Crafting A Game Engine!");

        // set the frames per second
        SetTargetFPS(60);
    }

    void Init() {}

    void PostInit() {}

    void PreUpdate()
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
    }

    void Tick() {}

    void Update() {}

    void PostUpdate()
    {
        DrawFPS(10, 10);
        EndDrawing();
    }

    void Exit()
    {
        // close the game
        CloseWindow();
    }
};