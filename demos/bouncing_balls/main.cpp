#include "raylib.h"

#include <vector>

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
void CheckBallCollision(Ball &ball, std::vector<Ball> &balls);

std::vector<Ball> balls(60);

int main(void)
{
    // start the game
    InitWindow(800, 450, "Crafting A Game Engine!");

    // set the frames per second
    SetTargetFPS(60);

    // create our balls
    for (int i = 0; i < balls.size(); i++)
    {
        balls[i] = CreateBall();
    }

    // enter the game loop
    while (!WindowShouldClose()) // window close button or ESC key
    {
        // apply forces to the ball
        for (auto &ball : balls)
        {
            UpdateBall(ball);
        }

        // check for collisions on ball
        for (auto &ball : balls)
        {

            CheckBallCollision(ball, balls);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw all balls
        for (const auto &ball : balls)
        {
            DrawBall(ball);
        }

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

    // randomize the position
    ball.position = {static_cast<float>(GetRandomValue(0, GetScreenWidth())), static_cast<float>(GetRandomValue(0, GetScreenHeight()))};

    // randomize the velocity
    ball.velocity = {static_cast<float>(GetRandomValue(-3, 3)), 0};

    ball.radius = static_cast<float>(GetRandomValue(10, 30));
    ball.color = {static_cast<unsigned char>(GetRandomValue(0, 255)), static_cast<unsigned char>(GetRandomValue(0, 255)), static_cast<unsigned char>(GetRandomValue(0, 255)), 255};

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

void CheckBallCollision(Ball &ball, std::vector<Ball> &balls)
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

    for (auto &other : balls)
    {
        if (&ball != &other)
        {
            float dx = ball.position.x - other.position.x;
            float dy = ball.position.y - other.position.y;
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance < ball.radius + other.radius)
            {
                // 1. Calculate the basis vector (x-axis) in the direction of collision
                Vector2 xAxis = {dx / distance, dy / distance};

                // 2. Calculate velocities in the direction of the basis vector
                float v1x = xAxis.x * ball.velocity.x + xAxis.y * ball.velocity.y;
                float v2x = xAxis.x * other.velocity.x + xAxis.y * other.velocity.y;

                // 3. Calculate perpendicular velocities
                Vector2 v1xVec = {xAxis.x * v1x, xAxis.y * v1x};
                Vector2 v2xVec = {xAxis.x * v2x, xAxis.y * v2x};

                Vector2 v1yVec = {ball.velocity.x - v1xVec.x, ball.velocity.y - v1xVec.y};
                Vector2 v2yVec = {other.velocity.x - v2xVec.x, other.velocity.y - v2xVec.y};

                // 4. Calculate masses
                float m1 = ball.radius; // Use radius as a proxy for mass, assuming uniform density
                float m2 = other.radius;

                // 5. Update velocities using the formulas
                ball.velocity.x = v1xVec.x * (m1 - m2) / (m1 + m2) + v2xVec.x * (2 * m2) / (m1 + m2) + v1yVec.x;
                ball.velocity.y = v1xVec.y * (m1 - m2) / (m1 + m2) + v2xVec.y * (2 * m2) / (m1 + m2) + v1yVec.y;

                other.velocity.x = v1xVec.x * (2 * m1) / (m1 + m2) + v2xVec.x * (m2 - m1) / (m1 + m2) + v2yVec.x;
                other.velocity.y = v1xVec.y * (2 * m1) / (m1 + m2) + v2xVec.y * (m2 - m1) / (m1 + m2) + v2yVec.y;

                // 6. Resolve overlap by moving the balls apart
                float overlap = 0.5f * (ball.radius + other.radius - distance);
                ball.position.x += xAxis.x * overlap;
                ball.position.y += xAxis.y * overlap;
                other.position.x -= xAxis.x * overlap;
                other.position.y -= xAxis.y * overlap;
            }
        }
    }
}