#include "iostream"
#include "raylib.h"

// Round Sphere Object (Main character - Flappy)
typedef struct RSphere
{
    Vector2 position;
    int radius;
    Color color;
} Flappy;

// Obstacle Object (Water Pipe)
typedef struct Obstacle
{
    Rectangle rec;
    Color color;
} WaterPipe;

// Global Variables Declaration
static const int screenWidth = 800;
static const int screenHeight = 450;

static Flappy flappy;
static WaterPipe waterpipe;

// Module Functions Declaration (local)
static void InitGame(); // Initialize game
static void DrawGame(); // Draw game (one frame)

// Count Water Pipe <= Count Water Pipe / 2 && Count Water Pipe >= 2
const int MAX = 6;

// Properties of "water pipes"
// int posX = 0;
// int posY[MAX] = {};
// int width = 80;
// int height = 200;
// Color color = GREEN;

void InitGame()
{
    flappy.radius = 30;
    flappy.color = BLUE;
    flappy.position = (Vector2){80, screenHeight / 2};

    waterpipe.rec.x = 400;
    waterpipe.rec.y = 0;
    waterpipe.rec.width = 80;
    waterpipe.rec.height = 200;
    waterpipe.color = GREEN;
}

void DrawGame()
{
    // Background
    ClearBackground(WHITE);

    // Round Sphere (Main character)
    DrawCircle(flappy.position.x, flappy.position.y, flappy.radius, flappy.color);

    // Rectangle Water Pipe
    DrawRectangle(waterpipe.rec.x, waterpipe.rec.y, waterpipe.rec.width, waterpipe.rec.height, waterpipe.color);
    DrawRectangle(waterpipe.rec.x, waterpipe.rec.height + waterpipe.rec.y + flappy.radius * 2 + 40, waterpipe.rec.width, waterpipe.rec.height, waterpipe.color);
}

int main()
{
    InitWindow(screenWidth, screenHeight, "classic game: floppy");

    // posY Rectangle Water Pipe
    // for (int i = 0; i < MAX; i += 2)
    // {
    //     posY[i] = GetRandomValue(-50, 0);
    // }

    InitGame();

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();

        DrawGame();

        // Rectangle Water Pipe
        // DrawRectangle(400, 0, 80, 200, GREEN);
        // DrawRectangle(400, 200 + 60 + 40, 80, 200, GREEN);

        // DrawRectangle(400 + 250, -20, 80, 200, GREEN);
        // DrawRectangle(400 + 250, 200 - 20 + 60 + 40, 80, 200, GREEN);

        // int radiusCircle = 30;
        // int posX = 0;
        // int width = 80;
        // int height = 200;
        // Color color = GREEN;

        // posX = 0;

        // for (int i = 0; i < MAX; i += 2)
        // {
        //     DrawRectangle(posX, posY[i], width, height, color);
        //     DrawRectangle(posX, height + posY[i] + radius * 2 + 40, width, height, color);

        //     posX += 250;
        //     std::cout << "posX = " << posX << "\n";
        // }

        EndDrawing();
    }

    return 0;
}