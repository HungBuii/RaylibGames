#include "iostream"
#include "raylib.h"

#define NUM_BULLET 10

// Spaceship (main character)
struct Spaceship
{
    Rectangle rec;
    Vector2 speed;
    Color color;
};

// Global Variables Declaration
static const int screenWidth = 800;
static const int screenHeight = 450;

static Spaceship spaceship;

// Module Functions Declaration
static void ShowFPS();         // Show FPS on screen
static void InitGame();        // Initialize game
static void DrawGame();        // Draw game (one frame)
static void UpdateGame();      // Update game (one frame)
static void UpdateDrawFrame(); // Update and Draw

// Logic Functions Declaration
static void MoveButton();
static void Movement();

// Logic Functions Init
void MoveButton()
{
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        spaceship.rec.y -= spaceship.speed.y;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        spaceship.rec.y += spaceship.speed.y;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        spaceship.rec.x -= spaceship.speed.x;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        spaceship.rec.x += spaceship.speed.x;
}

void Movement()
{
    if (spaceship.rec.x <= 0)
        spaceship.rec.x = 0;
    if (spaceship.rec.x >= screenWidth - spaceship.rec.width)
        spaceship.rec.x = screenWidth - spaceship.rec.width;
    if (spaceship.rec.y <= 0)
        spaceship.rec.y = 0;
    if (spaceship.rec.y >= screenHeight - spaceship.rec.height)
        spaceship.rec.y = screenHeight - spaceship.rec.height;
}

// Module Functions Init
void InitGame()
{
    // Init spaceship object
    spaceship.rec.x = 20;
    spaceship.rec.y = 50;
    spaceship.rec.width = 40;
    spaceship.rec.height = 20;
    spaceship.speed.x = 5;
    spaceship.speed.y = 5;
    spaceship.color = BLUE;
}

void DrawGame()
{
    BeginDrawing();

    // Background
    ClearBackground(WHITE);

    // Draw objects
    DrawRectangle(spaceship.rec.x, spaceship.rec.y, spaceship.rec.width, spaceship.rec.height, spaceship.color); // Main ship

    // DrawRectangle(50, 50, 40, 20, BLUE);  // Main ship
    // DrawRectangle(100, 50, 20, 10, BLUE); // Bullet
    // DrawRectangle(50, 100, 20, 20, BLUE); // Enemy

    EndDrawing();
}

void UpdateGame()
{
    // Spaceship movement
    MoveButton();
    Movement();

    //
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

    InitGame();

    SetTargetFPS(60);

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        ShowFPS();

        UpdateDrawFrame();
    }

    return 0;
}