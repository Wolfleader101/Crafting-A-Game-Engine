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

        // Draw some text
        DrawText("A Basic Game Loop!", 200, 200, 20, DARKGRAY);
        DrawText("Crafting A Game Engine:", 200, 230, 20, LIGHTGRAY);
        DrawText("Surprisingly Simple!", 200, 260, 20, LIGHTGRAY);

        EndDrawing();
    }

    // close the game
    CloseWindow();

    return 0;
}