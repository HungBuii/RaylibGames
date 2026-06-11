#include "iostream"
#include "raylib.h"

#define SIZE_SQUARE 31
#define SNAKE_LENGTH 350

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
    bool active;
};

// Global Variables Declaration
static const int screenWidth = 800;
static const int screenHeight = 450;

static int frame_counter = 0;

static Vector2 offset;

static Snake snake[SNAKE_LENGTH];
static int snake_length = 0;
static int counterTail = 1;
static Vector2 snakeTailPos[SNAKE_LENGTH];

static Food food;

static int score = 0;
static int hiScore = 0;

static bool gameOver = false;

// Module Functions Declaration (local)
static void InitGame();        // Initialize game
static void DrawGame();        // Draw game (one frame)
static void UpdateGame();      // Update game (one frame)
static void UpdateDrawFrame(); // Update and Draw
static void ShowFPS();         // Show FPS on screen

// Logic Functions Declaration
void DrawPlatform();
void SnakeInit();
void FoodInit();
void Input();
void Movement();
void SpawnFood();
void Eat();
void StatusCharacter();

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
    counterTail = 1;
    snake_length = 1;
    for (int i = 0; i < SNAKE_LENGTH; i++)
    {
        snake[i].position = (Vector2){offset.x / 2, offset.y / 2};
        snake[i].size = (Vector2){SIZE_SQUARE, SIZE_SQUARE};
        snake[i].speed = (Vector2){SIZE_SQUARE, 0};

        if (i == 0)
            snake[i].color = DARKBLUE;
        else
            snake[i].color = BLUE;
    }

    for (int i = 0; i < SNAKE_LENGTH; i++)
    {
        snakeTailPos[i] = (Vector2){0.0f, 0.0f};
    }
}

void FoodInit()
{
    food.position = (Vector2){
        GetRandomValue(0, (screenWidth / SIZE_SQUARE) - 1) * SIZE_SQUARE + offset.x / 2,
        GetRandomValue(0, (screenHeight / SIZE_SQUARE) - 1) * SIZE_SQUARE + offset.y / 2};
    food.size = {SIZE_SQUARE, SIZE_SQUARE};
    food.color = GREEN;
    food.active = false;
}

void Input()
{
    if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && (snake[0].speed.y == 0))
        snake[0].speed = Vector2{0, SIZE_SQUARE};
    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && (snake[0].speed.y == 0))
        snake[0].speed = Vector2{0, -SIZE_SQUARE};
    if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && (snake[0].speed.x == 0))
        snake[0].speed = Vector2{-SIZE_SQUARE, 0};
    if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && (snake[0].speed.x == 0))
        snake[0].speed = Vector2{SIZE_SQUARE, 0};
}

void Movement()
{
    for (int i = 0; i < counterTail; i++)
    {
        snakeTailPos[i] = snake[i].position;
    }

    if (frame_counter % 5 == 0)
    {
        for (int i = 0; i < counterTail; i++)
        {
            if (i == 0)
            {
                snake[0].position.x += snake[0].speed.x;
                snake[0].position.y += snake[0].speed.y;
            }
            else
                snake[i].position = snakeTailPos[i - 1];
        }
    }
    frame_counter++;
}

void SpawnFood()
{
    if (!food.active)
    {
        food.active = true;

        for (int i = 0; i < counterTail; i++)
        {
            while ((food.position.x == snake[i].position.x) && (food.position.y == snake[i].position.y))
            {
                food.position = (Vector2){
                    GetRandomValue(0, (screenWidth / SIZE_SQUARE) - 1) * SIZE_SQUARE + offset.x / 2,
                    GetRandomValue(0, (screenHeight / SIZE_SQUARE) - 1) * SIZE_SQUARE + offset.y / 2};

                i = 0;
            }
        }
    }
}

void Eat()
{
    if ((snake[0].position.x == food.position.x) && (snake[0].position.y == food.position.y))
    {
        snake[counterTail].position = snakeTailPos[counterTail - 1];
        counterTail++;

        score += 100;
        if (hiScore < score)
            hiScore = score;

        food.active = false;
    }
}

void StatusCharacter()
{
    // "Snake" collision "Wall"
    if ((snake[0].position.x < offset.x / 2) || (snake[0].position.x >= screenWidth - offset.x / 2) || (snake[0].position.y < offset.y / 2) || (snake[0].position.y >= screenHeight - offset.y / 2))
    {
        gameOver = true;
    }

    // "Snake" collsion "Tail" itself
    for (int i = 1; i < counterTail; i++)
    {
        if ((snake[0].position.x == snake[i].position.x) && snake[0].position.y == snake[i].position.y)
        {
            gameOver = true;
            break;
        }
    }
}

// Module Functions Init (local)
void InitGame()
{
    // x, y coordinates according to screen resolution
    offset.x = screenWidth % SIZE_SQUARE;
    offset.y = screenHeight % SIZE_SQUARE;

    // Frame
    frame_counter = 0;

    // Score
    score = 0;

    // status game
    gameOver = false;

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

    if (gameOver)
    {
        char textGameOver[] = "Game Over! Press [ENTER] To Play Again";
        DrawText(textGameOver, GetScreenWidth() / 2 - MeasureText(textGameOver, 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);

        char textScore[] = "Score :";
        int posXTextScore = GetScreenWidth() / 2 - MeasureText(textScore, 20) / 2;
        int posYTextScore = GetScreenHeight() / 2 - 40 + 30;
        DrawText(textScore, posXTextScore, posYTextScore, 20, GRAY);
        DrawText(TextFormat("%01i", score), posXTextScore + 90, posYTextScore, 20, GRAY);

        char textHiScore[] = "Hi Score :";
        int posXTextHiScore = GetScreenWidth() / 2 - MeasureText(textScore, 20) / 2;
        int posYTextHiScore = GetScreenHeight() / 2 - 40 + 60;
        DrawText(textHiScore, posXTextHiScore, posYTextHiScore, 20, GRAY);
        DrawText(TextFormat("%01i", hiScore), posXTextHiScore + 110, posYTextHiScore, 20, GRAY);
    }

    else
    {
        // Platform
        DrawPlatform();

        // Snake
        for (int i = 0; i < counterTail; i++)
        {
            DrawRectangleV(snake[i].position, snake[i].size, snake[i].color);
        }

        // Food
        DrawRectangleV(food.position, food.size, food.color);

        // Score
        DrawText(TextFormat("%04i", score), 20, 40, 30, RED);
        // DrawText(TextFormat("%04i", hiScore), 20, 80, 30, RED);
    }

    EndDrawing();
}

void UpdateGame()
{
    if (!gameOver)
    {
        // Input
        Input();

        // Snake movement
        Movement();

        // "Food" spawn
        SpawnFood();

        // "Snake" eat "Food"
        Eat();

        // Game status
        StatusCharacter();
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            gameOver = false;

            InitGame();
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
    DrawFPS(screenWidth - 75, 10);
}

int main()
{
    InitWindow(screenWidth, screenHeight, "classic game: snake");

    SetTargetFPS(60);

    InitGame();

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        ShowFPS();

        UpdateDrawFrame();
    }
}