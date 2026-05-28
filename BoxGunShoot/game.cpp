#include "iostream"
#include "raylib.h"

#define NUM_BULLET 50

// Spaceship (main character)
struct Spaceship
{
    Rectangle rec;
    Vector2 speed;
    Color color;
};

// Bullet
struct Bullet
{
    Rectangle rec;
    Vector2 speed;
    Color color;
    bool active;
};

// Global Variables Declaration
static const int screenWidth = 800;
static const int screenHeight = 450;

static Spaceship spaceship;

static Bullet bullet[NUM_BULLET];
static int shootRate = 0;

// Module Functions Declaration
static void ShowFPS();         // Show FPS on screen
static void InitGame();        // Initialize game
static void DrawGame();        // Draw game (one frame)
static void UpdateGame();      // Update game (one frame)
static void UpdateDrawFrame(); // Update and Draw

// Logic Functions Declaration
static void MoveButton();
static void Movement();
static void Fire();

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

void Fire()
{
    if (IsKeyDown(KEY_SPACE))
    {
        shootRate += 5;

        for (int i = 0; i < NUM_BULLET; i++)
        {
            if (!bullet[i].active && shootRate % 20 == 0)
            {
                bullet[i].rec.x = spaceship.rec.x + spaceship.rec.width;
                bullet[i].rec.y = spaceship.rec.y + spaceship.rec.height / 4;
                bullet[i].active = true;
                break;
            }
        }
    }

    for (int i = 0; i < NUM_BULLET; i++)
    {
        if (bullet[i].active)
        {
            bullet[i].rec.x += bullet[i].speed.x;

            if (bullet[i].rec.x + bullet[i].rec.width >= screenWidth)
            {
                bullet[i].active = false;
                shootRate = 0; // reload bullet
            }
        }
    }
}

// Module Functions Init
void InitGame()
{
    // Init spaceship
    spaceship.rec.x = 20;
    spaceship.rec.y = 50;
    spaceship.rec.width = 40;
    spaceship.rec.height = 20;
    spaceship.speed.x = 5;
    spaceship.speed.y = 5;
    spaceship.color = BLUE;

    // Init bullet
    shootRate = 0;
    for (int i = 0; i < NUM_BULLET; i++)
    {
        bullet[i].rec.x = spaceship.rec.x + spaceship.rec.width;
        bullet[i].rec.y = spaceship.rec.y + spaceship.rec.height / 4;
        bullet[i].rec.width = spaceship.rec.width / 2;
        bullet[i].rec.height = spaceship.rec.height / 2;
        bullet[i].speed.x = 7;
        bullet[i].speed.y = 0;
        bullet[i].color = RED;
        bullet[i].active = false;
    }
}

void DrawGame()
{
    BeginDrawing();

    // Background
    ClearBackground(WHITE);

    // Draw objects
    DrawRectangleRec(spaceship.rec, spaceship.color); // Main ship

    for (int i = 0; i < NUM_BULLET; i++)
    {
        if (bullet[i].active)
            DrawRectangleRec(bullet[i].rec, bullet[i].color);
    }

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

    // Fire
    Fire();
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