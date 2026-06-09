#include "iostream"
#include "raylib.h"

#define SIZE_SQUARE 31
// #define SNAKE_LENGTH 350

// Snake
struct Snake
{
    Vector2 position;
    Vector2 size;
    Vector2 speed;
    Color color;
};

// Global Variables Declaration
static const int screenWidth = 800;
static const int screenHeight = 450;

static int frame_counter = 0;

static Vector2 offset;

static Snake snake;
static int snake_length = 0;

// Module Functions Declaration (local)
static void InitGame();        // Initialize game
static void DrawGame();        // Draw game (one frame)
static void UpdateGame();      // Update game (one frame)
static void UpdateDrawFrame(); // Update and Draw
static void ShowFPS();         // Show FPS on screen        // Show FPS on screen

// Logic Functions Declaration
void DrawPlatform();

// Logic Functions Init
void DrawPlatform()
{
    // Horizontal lines "Platform"
    for (int i = 0; i <= screenHeight / SIZE_SQUARE; i++)
    {
        DrawLineV(
            (Vector2){offset.x / 2, (offset.y / 2) + (SIZE_SQUARE * i)},
            (Vector2){screenWidth - (offset.x / 2), (offset.y / 2) + (SIZE_SQUARE * i)},
            GRAY);
    }

    // Vertical lines "Platform"
    for (int i = 0; i <= screenWidth / SIZE_SQUARE; i++)
    {
        DrawLineV(
            (Vector2){(offset.x / 2) + (SIZE_SQUARE * i), offset.y / 2},
            (Vector2){(offset.x / 2) + (SIZE_SQUARE * i), screenHeight - (offset.y / 2)},
            GRAY);
    }
}

// Module Functions Init (local)
void InitGame()
{
    // x, y coordinates according to screen resolution
    offset.x = screenWidth % SIZE_SQUARE;
    offset.y = screenHeight % SIZE_SQUARE;

    // frame
    frame_counter = 0;

    // init "Snake"
    snake_length = 1;
    snake.position = (Vector2){offset.x / 2, offset.y / 2};
    snake.size = {SIZE_SQUARE, SIZE_SQUARE};
    snake.color = DARKBLUE;
    snake.speed = Vector2{SIZE_SQUARE, 0};
}

void DrawGame()
{
    BeginDrawing();

    // Background
    ClearBackground(WHITE);

    // Platform
    DrawPlatform();

    // Snake
    DrawRectangleV(snake.position, snake.size, snake.color);

    EndDrawing();
}

void UpdateGame()
{
    if (frame_counter % 5 == 0)
    {
        snake.position.x += snake.speed.x;
        snake.position.y += snake.speed.y;
    }

    frame_counter++;
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
    InitWindow(screenWidth, screenHeight, "classic game: snake");

    SetTargetFPS(60);

    InitGame();

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // ShowFPS();

        UpdateDrawFrame();
    }
}