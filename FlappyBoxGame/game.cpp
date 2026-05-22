#include "iostream"
#include "raylib.h"

// Define value
#define MAX_PIPES 100 // Count Water Pipe <= Count Water Pipe / 2 && Count Water Pipe >= 2
#define WPWidth 80
#define WPHeight 300
#define RADIUS 30

// Round Sphere Object (Main character - Flappy)
struct Flappy
{
    Vector2 position;
    int radius;
    Color color;
};

// Obstacle Object (Water Pipe)
typedef struct WaterPipe
{
    Rectangle rec;
    Color color;
} WP;

// Global Variables Declaration
static const int screenWidth = 800;
static const int screenHeight = 450;

static Flappy flappy;
static WP wp[MAX_PIPES] = {0};
static Vector2 wpPos[MAX_PIPES] = {0};

static int speedX = 0;

// Module Functions Declaration (local)
static void InitGame();        // Initialize game
static void DrawGame();        // Draw game (one frame)
static void UpdateGame();      // Update game (one frame)
static void UpdateDrawFrame(); // Update and Draw
static void ShowFPS();         // Show FPS on screen

void InitGame()
{
    speedX = 2;

    flappy.radius = RADIUS;
    flappy.color = BLUE;
    flappy.position = (Vector2){80, screenHeight / 2};

    for (int i = 0; i < MAX_PIPES; i++)
    {
        wpPos[i].x = 400 + 250 * i;
        wpPos[i].y = GetRandomValue(-150, 0);
    }

    for (int i = 0; i < MAX_PIPES; i += 2)
    {
        wp[i].rec.x = wpPos[i / 2].x;
        wp[i].rec.y = wpPos[i / 2].y;
        wp[i].rec.width = WPWidth;
        wp[i].rec.height = WPHeight;

        wp[i + 1].rec.x = wpPos[i / 2].x;
        wp[i + 1].rec.y = wp[i].rec.height + wpPos[i / 2].y + RADIUS * 2 + 40;
        wp[i + 1].rec.width = WPWidth;
        wp[i + 1].rec.height = WPHeight;
    }
}

void DrawGame()
{
    BeginDrawing();

    // Background
    ClearBackground(WHITE);

    // Round Sphere (Main character)
    DrawCircle(flappy.position.x, flappy.position.y, flappy.radius, flappy.color);

    for (int i = 0; i < MAX_PIPES; i += 2)
    {
        DrawRectangle(wp[i].rec.x, wp[i].rec.y, wp[i].rec.width, wp[i].rec.height, GREEN);
        DrawRectangle(wp[i + 1].rec.x, wp[i + 1].rec.y, wp[i + 1].rec.width, wp[i + 1].rec.height, GREEN);
    }

    EndDrawing();
}

void UpdateGame()
{
    for (int i = 0; i < MAX_PIPES; i++)
    {
        wpPos[i].x -= speedX;
    }

    for (int i = 0; i < MAX_PIPES; i += 2)
    {
        wp[i].rec.x = wpPos[i / 2].x;
        wp[i + 1].rec.x = wpPos[i / 2].x;
    }
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

int main()
{
    InitWindow(screenWidth, screenHeight, "classic game: floppy");

    InitGame();

    SetTargetFPS(60);

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        ShowFPS();

        UpdateDrawFrame();
    }

    return 0;
}