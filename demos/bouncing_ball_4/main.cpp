#include "raylib.h"

struct Ball
{
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
};

constexpr const Vector2 GRAVITY_VEC = {0.0f, -9.82f};

Ball CreateBall();
void DrawBall(const Ball &ball);
void UpdateBall(Ball &ball);
void CheckBallCollision(Ball &ball);

int main(void)
{
    // start the game
    InitWindow(800, 450, "Crafting A Game Engine!");

    // set the frames per second
    SetTargetFPS(60);

    // create our ball
    Ball ball = CreateBall();

    // enter the game loop
    while (!WindowShouldClose()) // window close button or ESC key
    {
        // apply forces to the ball
        UpdateBall(ball);

        // check for collisions on screen edges
        CheckBallCollision(ball);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw a ball
        DrawBall(ball);

        DrawFPS(10, 10);
        EndDrawing();
    }

    // close the game
    CloseWindow();

    return 0;
}

Ball CreateBall()
{
    Ball ball;
    ball.position = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    ball.velocity = {5, 0};
    ball.radius = 20;
    ball.color = RED;

    return ball;
}

void DrawBall(const Ball &ball)
{
    DrawCircleV(ball.position, ball.radius, ball.color);
}

void UpdateBall(Ball &ball)
{
    ball.velocity.x += GRAVITY_VEC.x * GetFrameTime();
    ball.velocity.y += GRAVITY_VEC.y * GetFrameTime();

    ball.position.x += ball.velocity.x;
    ball.position.y -= ball.velocity.y;
}

void CheckBallCollision(Ball &ball)
{
    if (ball.position.x >= GetScreenWidth() - ball.radius)
    {
        ball.position.x = GetScreenWidth() - ball.radius;
        ball.velocity.x *= -0.6f;
    }
    else if (ball.position.x <= ball.radius)
    {
        ball.position.x = ball.radius;
        ball.velocity.x *= -0.4f;
    }

    if (ball.position.y >= GetScreenHeight() - ball.radius)
    {
        ball.position.y = GetScreenHeight() - ball.radius;
        ball.velocity.y *= -0.9f;
    }
    else if (ball.position.y <= ball.radius)
    {
        ball.position.y = ball.radius;
        ball.velocity.y *= -0.9f;
    }
}