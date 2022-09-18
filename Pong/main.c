#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "raylib.h"

//------------------------------------------------------------------------------------

Vector2 RandVelocity()
{
    float min = 3;
    float max = 5;

    float x = (min + (float)(rand()) / ((float)(RAND_MAX / (max - min)))) * pow(-1, GetRandomValue(0, 1));
    float y = (min + (float)(rand()) / ((float)(RAND_MAX / (max - min)))) * pow(-1, GetRandomValue(0, 1));

    Vector2 vel = {x, y};

    return vel;
}

// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    srand(time(NULL));
    SetRandomSeed(time(NULL));
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 675;

    InitWindow(screenWidth, screenHeight, "pong");

    int paddleOneLives = 3;
    int paddleTwoLives = 3;

    Vector2 netPosition = {(int)((float)screenWidth / 2 - 2), 10};
    Vector2 netSize = {4, (int)(screenHeight - 20)};

    int ballRadius = 8;
    Vector2 ballPosition = {(float)screenWidth / 2, (float)screenHeight / 2};
    Vector2 ballVelocity = RandVelocity();

    Rectangle paddleOne = {32, (float)screenHeight / 2, 6, 75};
    Rectangle paddleTwo = {(float)screenWidth - 32, (float)screenHeight / 2, 6, 75};

    Texture2D heartTex = LoadTexture("resources/heart.png");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update

        // Ball
        ballPosition.x += ballVelocity.x;
        ballPosition.y += ballVelocity.y;

        if (ballPosition.x < 0)
        {
            paddleOneLives -= 1;
            ballPosition.x = (float)screenWidth / 2;
            ballPosition.y = (float)screenHeight / 2;
            ballVelocity = RandVelocity();
        }

        if (ballPosition.x > screenWidth)
        {
            paddleTwoLives -= 1;
            ballPosition.x = (float)screenWidth / 2;
            ballPosition.y = (float)screenHeight / 2;
            ballVelocity = RandVelocity();
        }

        if (ballPosition.y < 0 || ballPosition.y > screenHeight)
        {
            ballVelocity.y *= -1;
        }

        if (CheckCollisionCircleRec(ballPosition, ballRadius, paddleOne) || CheckCollisionCircleRec(ballPosition, ballRadius, paddleTwo))
        {
            ballVelocity.x *= -1;
        }

        // Paddle One
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_W))
            paddleOne.y -= 4.0f;
        if (IsKeyDown(KEY_S))
            paddleOne.y += 4.0f;
        //----------------------------------------------------------------------------------

        // Paddle Two
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_UP))
            paddleTwo.y -= 4.0f;
        if (IsKeyDown(KEY_DOWN))
            paddleTwo.y += 4.0f;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        if (paddleOneLives <= 0)
        {
            ClearBackground(RAYWHITE);
            DrawText("Player Two Wins!", (float)screenWidth / 2 - 200, (float)screenHeight / 2, 50, BLACK);
        }

        else if (paddleTwoLives <= 0)
        {
            ClearBackground(RAYWHITE);
            DrawText("Player One Wins!", (float)screenWidth / 2 - 200, (float)screenHeight / 2, 50, BLACK);
        }

        else
        {
            ClearBackground(RAYWHITE);
            DrawRectangleV(netPosition, netSize, DARKGRAY);

            DrawText("Move Paddles With W, S, Up, and Down", 10, 10, 20, DARKGRAY);

            for (int i = 0; i < paddleOneLives; i++)
            {
                DrawTexture(heartTex, 48 + (i * 32), 48, BLACK);
            }

            for (int i = paddleTwoLives; i > 0; i--)
            {
                DrawTexture(heartTex, screenWidth - (48 + (i * 32)), 48, BLACK);
            }

            DrawCircleV(ballPosition, ballRadius, BLACK);
            DrawRectangleRec(paddleOne, BLACK);
            DrawRectangleRec(paddleTwo, BLACK);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
