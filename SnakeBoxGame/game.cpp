#include "iostream"
#include "raylib.h"

// Global Variables Declaration
static const int screenWidth = 800;
static const int screenHeight = 450;

// Module Functions Declaration (local)
// static void InitGame();        // Initialize game
static void DrawGame(); // Draw game (one frame)
// static void UpdateGame();      // Update game (one frame)
static void UpdateDrawFrame(); // Update and Draw
static void ShowFPS();         // Show FPS on screen        // Show FPS on screen

// Module Functions Init (local)
void DrawGame()
{
    BeginDrawing();

    // Background
    ClearBackground(WHITE);

    EndDrawing();
}

void UpdateDrawFrame()
{
    // UpdateGame();
    DrawGame();
}

void ShowFPS()
{
    DrawFPS(0, 10);
}

int main()
{
    InitWindow(screenWidth, screenHeight, "classic game: snake");

    SetTargetFPS(60);

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        ShowFPS();

        UpdateDrawFrame();
    }
}