#include "iostream"
#include "raylib.h"

// Global Variables Declaration
static const int screenWidth = 800;
static const int screenHeight = 450;

// Module Functions Declaration
static void ShowFPS();         // Show FPS on screen
static void InitGame();        // Initialize game
static void DrawGame();        // Draw game (one frame)
static void UpdateGame();      // Update game (one frame)
static void UpdateDrawFrame(); // Update and Draw

// Module Functions Init
void InitGame()
{
}

void DrawGame()
{
    BeginDrawing();

    // Background
    ClearBackground(WHITE);

    EndDrawing();
}

void UpdateGame()
{
}

void UpdateDrawFrame()
{
    UpdateGame();
    DrawGame();
}

void ShowFPS()
{
    DrawFPS(0, 10);
}

// Main Program
int main()
{
    InitWindow(screenWidth, screenHeight, "classic game: box gun shoot");

    SetTargetFPS(60);

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        ShowFPS();

        UpdateDrawFrame();
    }

    return 0;
}