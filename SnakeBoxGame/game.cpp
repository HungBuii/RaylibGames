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

// Food
struct Food
{
    Vector2 position;
    Vector2 size;
    Color color;
};

// Global Variables Declaration
static const int screenWidth = 800;
static const int screenHeight = 450;

static int frame_counter = 0;

static Vector2 offset;

static Snake snake;
static int snake_length = 0;

static Food food;

// Module Functions Declaration (local)
static void InitGame();        // Initialize game
static void DrawGame();        // Draw game (one frame)
static void UpdateGame();      // Update game (one frame)
static void UpdateDrawFrame(); // Update and Draw
static void ShowFPS();         // Show FPS on screen        // Show FPS on screen

// Logic Functions Declaration
void DrawPlatform();
void SnakeInit();
void FoodInit();

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

void SnakeInit()
{
    snake_length = 1;
    snake.position = (Vector2){offset.x / 2, offset.y / 2};
    snake.size = {SIZE_SQUARE, SIZE_SQUARE};
    snake.color = DARKBLUE;
    snake.speed = Vector2{SIZE_SQUARE, 0};
}

void FoodInit()
{
    food.position = (Vector2){
        GetRandomValue(0, (screenWidth / SIZE_SQUARE - 1)) * SIZE_SQUARE + offset.x / 2,
        GetRandomValue(0, (screenHeight / SIZE_SQUARE - 1)) * SIZE_SQUARE + offset.y / 2,
    };
    food.size = {SIZE_SQUARE, SIZE_SQUARE};
    food.color = GREEN;
}

// Module Functions Init (local)
void InitGame()
{
    // x, y coordinates according to screen resolution
    offset.x = screenWidth % SIZE_SQUARE;
    offset.y = screenHeight % SIZE_SQUARE;

    // Frame
    frame_counter = 0;

    // Init "Snake"
    SnakeInit();

    // Init "Food"
    FoodInit();
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

    // Food
    DrawRectangleV(food.position, food.size, food.color);

    EndDrawing();
}

void UpdateGame()
{
    // Input
    if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && (snake.speed.y == 0))
        snake.speed = Vector2{0, SIZE_SQUARE};
    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && (snake.speed.y == 0))
        snake.speed = Vector2{0, -SIZE_SQUARE};
    if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && (snake.speed.x == 0))
        snake.speed = Vector2{-SIZE_SQUARE, 0};
    if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && (snake.speed.x == 0))
        snake.speed = Vector2{SIZE_SQUARE, 0};

    // Snake movement
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