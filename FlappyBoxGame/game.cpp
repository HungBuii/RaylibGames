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
    bool active;
} WP;

// Global Variables Declaration
static const int screenWidth = 800;
static const int screenHeight = 450;

static Flappy flappy;
static WP wp[MAX_PIPES] = {0};
static Vector2 wpPos[MAX_PIPES] = {0};

static int score = 0;
static int hiScore = 0;
static int speedX = 0;
static bool gameOver = false;

// Module Functions Declaration (local)
static void InitGame();        // Initialize game
static void DrawGame();        // Draw game (one frame)
static void UpdateGame();      // Update game (one frame)
static void UpdateDrawFrame(); // Update and Draw
static void ShowFPS();         // Show FPS on screen

// Logic Functions Declaration
void FlappyInfo();
void WaterPipeLocation();
void FlappyMovement();
void WaterPipeAnimation();
void CheckCollision();

// Logic Functions Init
void FlappyInfo()
{
    flappy.radius = RADIUS;
    flappy.color = BLUE;
    flappy.position = (Vector2){80, screenHeight / 2};
}

void WaterPipeLocation()
{
    for (int i = 0; i < MAX_PIPES; i++)
    {
        wpPos[i].x = 450 + 250 * i;
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

        wp[i / 2].active = true;
    }
}

void FlappyMovement()
{
    flappy.position.y += 1;
    if (IsKeyDown(KEY_SPACE))
    {
        flappy.position.y -= 3;
    }
}

void WaterPipeAnimation()
{
    speedX = 2;

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

void CheckCollision()
{
    for (int i = 0; i < MAX_PIPES; i++)
    {
        if (CheckCollisionCircleRec(flappy.position, flappy.radius, wp[i].rec))
        {
            gameOver = true;
            InitGame();
        }
        else
        {
            if (flappy.position.x > wpPos[i].x && wp[i].active)
            {
                score += 100;
                wp[i].active = false;
                if (hiScore < score)
                    hiScore = score;
            }
        }
    }
}

// Module Functions Init (local)
void InitGame()
{
    FlappyInfo();

    WaterPipeLocation();

    score = 0;
}

void DrawGame()
{
    BeginDrawing();

    // Background
    ClearBackground(WHITE);

    if (gameOver)
    {
        char textGameOver[] = "Game Over! Press [ENTER] To Play Again";
        DrawText(textGameOver, GetScreenWidth() / 2 - MeasureText(textGameOver, 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);
    }
    else
    {
        // Round Sphere (Main character)
        DrawCircle(flappy.position.x, flappy.position.y, flappy.radius, flappy.color);

        // Water Pipe
        for (int i = 0; i < MAX_PIPES; i += 2)
        {
            DrawRectangle(wp[i].rec.x, wp[i].rec.y, wp[i].rec.width, wp[i].rec.height, GREEN);
            DrawRectangle(wp[i + 1].rec.x, wp[i + 1].rec.y, wp[i + 1].rec.width, wp[i + 1].rec.height, GREEN);
        }

        DrawText(TextFormat("%04i", score), 20, 40, 30, RED);
        DrawText(TextFormat("HI-SCORE: %04i", hiScore), 10, 70, 20, BLUE);
    }

    EndDrawing();
}

void UpdateGame()
{
    if (!gameOver)
    {
        FlappyMovement();

        WaterPipeAnimation();

        CheckCollision();
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            gameOver = false;
        }
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