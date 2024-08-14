#include "raylib.h"

struct Ball
{
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
};

constexpr const Vector2 GRAVITY_VEC = {0.0f, -9.82f};

int main(void)
{
    // start the game
    InitWindow(800, 450, "Crafting A Game Engine!");

    // set the frames per second
    SetTargetFPS(60);

    // create our ball
    Vector2 initPos = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    Vector2 initVel = {5, 0};
    Ball ball{initPos, initVel, 20, RED};

    // enter the game loop
    while (!WindowShouldClose()) // window close button or ESC key
    {
        // apply forces to the ball
        ball.velocity.x += GRAVITY_VEC.x * GetFrameTime();
        ball.velocity.y += GRAVITY_VEC.y * GetFrameTime();

        ball.position.x += ball.velocity.x;
        ball.position.y -= ball.velocity.y; // inverted y-axis because of raylib

        // check for collisions on screen edges
        if (ball.position.x >= GetScreenWidth() - ball.radius)
        {
            // correct position
            ball.position.x = GetScreenWidth() - ball.radius;

            // invert and reduce velocity by 40%
            ball.velocity.x *= -0.6f;
        }
        else if (ball.position.x <= ball.radius)
        {
            // correct position
            ball.position.x = ball.radius;

            // invert and reduce velocity by 40%
            ball.velocity.x *= -0.6f;
        }

        if (ball.position.y >= GetScreenHeight() - ball.radius)
        {
            // correct position
            ball.position.y = GetScreenHeight() - ball.radius;

            // invert and reduce velocity by 10%
            ball.velocity.y *= -0.9f;
        }
        else if (ball.position.y <= ball.radius)
        {
            // correct position
            ball.position.y = ball.radius;

            // invert and reduce velocity by 10%
            ball.velocity.y *= -0.9f;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw a ball
        DrawCircleV(ball.position, ball.radius, ball.color);

        DrawFPS(10, 10);

        EndDrawing();
    }

    // close the game
    CloseWindow();

    return 0;
}