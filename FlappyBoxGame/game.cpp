#include "iostream"
#include "raylib.h"

// Count Water Pipe <= Count Water Pipe / 2 && Count Water Pipe >= 2
const int MAX = 6;

// Properties of Round Sphere (Main character)
int radius = 30;

// Properties of "water pipes"
int posX = 0;
int posY[MAX] = {};
int width = 80;
int height = 200;
Color color = GREEN;

int main()
{
    InitWindow(800, 450, "classic game: floppy");

    // posY Rectangle Water Pipe
    for (int i = 0; i < MAX; i += 2)
    {
        posY[i] = GetRandomValue(-50, 0);
    }

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();

        // Round Sphere (Main character)
        DrawCircle(400, 250, radius, BLUE);

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

        posX = 0;

        for (int i = 0; i < MAX; i += 2)
        {
            DrawRectangle(posX, posY[i], width, height, color);
            DrawRectangle(posX, height + posY[i] + radius * 2 + 40, width, height, color);

            posX += 250;
            std::cout << "posX = " << posX << "\n";
        }

        // Background
        ClearBackground(WHITE);

        EndDrawing();
    }

    return 0;
}