#include "iostream"
#include "raylib.h"

#define NUM_BULLET 50
#define NUM_ENEMY 50
#define NUM_ENEMY_ROUND_1 5
#define NUM_ENEMY_ROUND_2 10
#define NUM_ENEMY_ROUND_3 15

// Enum "Round"
enum Round
{
    Round1,
    Round2,
    Round3
};

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

// Enemy
struct Enemyship
{
    Rectangle rec;
    Vector2 speed;
    Color color;
};

// Global Variables Declaration
static const int screenWidth = 800;
static const int screenHeight = 450;

static Spaceship spaceship;

static Bullet bullet[NUM_BULLET];
static int shootRate = 0; // Used to prevent "bullets" from being fired continuously.

static Enemyship enemyship[NUM_ENEMY];

static int score = 0;
static int enemyKilled = 0;
static int enemyEliminate = 0;

static bool gameOver = false;
static bool gameWin = false;

static float alpha = 0.f;
static bool textVisible = false;
static Round round;

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
static void EnemyMovement();
static void CheckCollision();

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

void EnemyMovement()
{
    for (int i = 0; i < NUM_ENEMY; i++)
    {
        enemyship[i].rec.x -= enemyship[i].speed.x;
        if (enemyship[i].rec.x < 0)
        {
            enemyship[i].rec.x = GetRandomValue(screenWidth, screenWidth + 1000);
            enemyship[i].rec.y = GetRandomValue(0, screenHeight - enemyship[i].rec.height);
        }
    }
}

void CheckCollision()
{

    for (int i = 0; i < NUM_ENEMY; i++)
    {
        // Enemy ship vs Space ship
        if (CheckCollisionRecs(enemyship[i].rec, spaceship.rec))
        {
            gameOver = true;
            break;
        }

        // Enemy ship vs Bullet
        for (int j = 0; j < NUM_BULLET; j++)
        {
            if (bullet[j].active && CheckCollisionRecs(enemyship[i].rec, bullet[j].rec))
            {
                enemyKilled++;
                score += 100;
                bullet[j].active = false;
                enemyship[i].rec.x = GetRandomValue(screenWidth, screenWidth + 1000);
                enemyship[i].rec.y = GetRandomValue(0, screenHeight - enemyship[i].rec.height);
            }
        }
    }
}

// Module Functions Init
void InitGame()
{
    // Init variables
    score = 0;
    gameOver = false;
    shootRate = 0;
    round = Round1;
    alpha = 0.f;
    textVisible = false;
    enemyKilled = 0;
    enemyEliminate = NUM_ENEMY_ROUND_1;
    gameWin = false;

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

    // Init enemyship
    for (int i = 0; i < NUM_ENEMY; i++)
    {
        enemyship[i].rec.width = spaceship.rec.width / 2;
        enemyship[i].rec.height = 15;
        enemyship[i].rec.x = GetRandomValue(screenWidth, screenWidth + 1000);
        enemyship[i].rec.y = GetRandomValue(0, screenHeight - enemyship[i].rec.height);
        enemyship[i].speed.x = 5;
        enemyship[i].speed.y = 0;
        enemyship[i].color = GREEN;
    }
}

void DrawGame()
{
    BeginDrawing();

    // Background
    ClearBackground(WHITE);

    // Check Game Over
    if (!gameOver)
    {
        if (gameWin)
        {
            char textGameWin[] = "Win Game! Press [ENTER] To Play Again";
            DrawText(textGameWin, GetScreenWidth() / 2 - MeasureText(textGameWin, 20) / 2, GetScreenHeight() / 2 - 40, 20, GRAY);

            char textEnemyKilled[] = "Enemy Killed :";
            int posXTextEnemyKilled = GetScreenWidth() / 2 - MeasureText(textEnemyKilled, 20) / 2;
            int posYTextEnemyKilled = GetScreenHeight() / 2 - 40 + 30;
            DrawText(textEnemyKilled, posXTextEnemyKilled, posYTextEnemyKilled, 20, GRAY);

            DrawText(TextFormat("%01i", enemyKilled), posXTextEnemyKilled + 150, posYTextEnemyKilled, 20, GRAY);

            char textScore[] = "Score :";
            int posXTextScore = GetScreenWidth() / 2 - MeasureText(textEnemyKilled, 20) / 2;
            int posYTextScore = GetScreenHeight() / 2 - 40 + 60;
            DrawText(textScore, posXTextScore, posYTextScore, 20, GRAY);

            DrawText(TextFormat("%01i", score), posXTextScore + 100, posYTextScore, 20, GRAY);
        }
        else
        {
            // Draw objects
            DrawRectangleRec(spaceship.rec, spaceship.color); // Main ship

            for (int i = 0; i < NUM_BULLET; i++)
            {
                if (bullet[i].active)
                    DrawRectangleRec(bullet[i].rec, bullet[i].color); // Bullet
            }

            for (int i = 0; i < NUM_ENEMY; i++)
            {
                DrawRectangleRec(enemyship[i].rec, enemyship[i].color); // Enemy ship
            }

            // Score
            DrawText(TextFormat("%04i", score), 5, 40, 30, RED);

            // Text each "Round"
            if (round == Round1)
            {
                DrawText("Round 1", GetScreenWidth() / 2 - MeasureText("Round 1", 40) / 2, GetScreenHeight() / 2 - 40, 40, Fade(GRAY, alpha));
            }
            if (round == Round2)
            {
                DrawText("Round 2", GetScreenWidth() / 2 - MeasureText("Round 2", 40) / 2, GetScreenHeight() / 2 - 40, 40, Fade(GRAY, alpha));
            }
            if (round == Round3)
            {
                DrawText("Round 3", GetScreenWidth() / 2 - MeasureText("Round 3", 40) / 2, GetScreenHeight() / 2 - 40, 40, Fade(GRAY, alpha));
            }
        }
    }
    else
    {
        char textGameOver[] = "Game Over! Press [ENTER] To Play Again";
        DrawText(textGameOver, GetScreenWidth() / 2 - MeasureText(textGameOver, 20) / 2, GetScreenHeight() / 2 - 40, 20, GRAY);

        char textEnemyKilled[] = "Enemy Killed :";
        int posXTextEnemyKilled = GetScreenWidth() / 2 - MeasureText(textEnemyKilled, 20) / 2;
        int posYTextEnemyKilled = GetScreenHeight() / 2 - 40 + 30;
        DrawText(textEnemyKilled, posXTextEnemyKilled, posYTextEnemyKilled, 20, GRAY);

        DrawText(TextFormat("%01i", enemyKilled), posXTextEnemyKilled + 150, posYTextEnemyKilled, 20, GRAY);
    }

    EndDrawing();
}

void UpdateGame()
{
    if (!gameOver)
    {
        if (!gameWin)
        {
            // Spaceship movement
            MoveButton();
            Movement();

            // Fire
            Fire();

            // Enemy movement
            EnemyMovement();

            // Check collision
            CheckCollision();

            // The effect of the text across each "round"
            switch (round)
            {
            case Round1:

                if (!textVisible)
                {
                    alpha += 0.02f;

                    if (alpha >= 1.f)
                        textVisible = true;
                }
                if (textVisible)
                {
                    alpha -= 0.02f;
                }
                if (enemyKilled == enemyEliminate)
                {
                    textVisible = false;
                    round = Round2;
                    alpha = 0.f;
                    enemyEliminate = NUM_ENEMY_ROUND_2;
                }

                break;

            case Round2:

                if (!textVisible)
                {
                    alpha += 0.02f;

                    if (alpha >= 1.f)
                        textVisible = true;
                }
                if (textVisible)
                {
                    alpha -= 0.02f;
                }
                if (enemyKilled >= enemyEliminate) // must ">=" replace "==" because when the score is increased suddenly, the system will not be able to check the conditions in time.
                {
                    textVisible = false;
                    round = Round3;
                    alpha = 0.f;
                    enemyEliminate = NUM_ENEMY_ROUND_3;
                }

                break;

            case Round3:

                if (!textVisible)
                {
                    alpha += 0.02f;

                    if (alpha >= 1.f)
                        textVisible = true;
                }
                if (textVisible)
                {
                    alpha -= 0.02f;
                }
                if (enemyKilled == enemyEliminate)
                {
                    gameWin = true;
                }

                break;

            default:
                break;
            }
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            gameOver = false;
            InitGame();
        }
    }

    if (gameWin)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            gameWin = false;
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