#include "raylib.h"

int main(void)
{
    // start the game
    InitWindow(800, 450, "Crafting A Game Engine!");

    // enter the game loop
    while (!WindowShouldClose()) // window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw a bouncing ball!
        DrawCircle(400, 225, 50, RED);

        EndDrawing();
    }

    // close the game
    CloseWindow();

    return 0;
}