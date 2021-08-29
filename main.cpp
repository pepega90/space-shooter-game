// Space shooter game
// created by aji mustofa @pepega90

// assets by kenny 
// https://www.kenney.nl/assets/space-shooter-redux

#include "raylib.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <string>

#define ENEMY_ALIVE 4
using namespace std;

int main(void)
{
    const int WIDTH{ 480 };
    const int HEIGHT{ 600 };

    InitWindow(WIDTH, HEIGHT, "Space Shooter");
    InitAudioDevice();
    SetTargetFPS(60);

    // Background
    Texture2D background{ LoadTexture("texture/bg.png") };

    // Load sound
    Sound shootSound = LoadSound("sound/pew.wav");
    Sound explosion1 = LoadSound("sound/Explosion.wav");
    // SetSoundVolume(explosion1, 0.4);
    Sound explosion2 = LoadSound("sound/Explosion2.wav");
    Sound expSfx[]{ explosion1, explosion2 };

    // Game variabel

    // countdown
    int countdown = 5;
    float runCount{};
    float lastCount{ 1.0 };

    int score{ 0 };
    int highScore{ 0 };
    bool gameOver{};
    bool startgame{};
    Player player{ {WIDTH / 2.0f - 20, HEIGHT - 150}, LoadTexture("texture/playerShip1_orange.png") };
    Bullet playerBullet;
    playerBullet.img = LoadTexture("texture/laserBlue05.png");
    playerBullet.rect.width = playerBullet.img.width * 0.8;
    playerBullet.rect.height = playerBullet.img.height * 0.8;
    playerBullet.active = true;
    playerBullet.speedY = -15;



    // PLayer explosion
    int explosionFrame{ 9 };
    int currentFrame{ 0 };
    float updateTime{ 1.f / 8.f };
    float runningTime{};

    Texture2D explosion[explosionFrame]{
        LoadTexture("texture/sonicExplosion00.png"),
        LoadTexture("texture/sonicExplosion01.png"),
        LoadTexture("texture/sonicExplosion02.png"),
        LoadTexture("texture/sonicExplosion03.png"),
        LoadTexture("texture/sonicExplosion04.png"),
        LoadTexture("texture/sonicExplosion05.png"),
        LoadTexture("texture/sonicExplosion06.png"),
        LoadTexture("texture/sonicExplosion07.png"),
        LoadTexture("texture/sonicExplosion08.png"),
    };

    Rectangle explRect{ player.getRect().x, player.getRect().y, explosion[1].width, explosion[1].height };


    // Init enemy
    // ------------------------------------------------------------
    string enemyImgList[]{ "texture/enemyBlack2.png", "texture/enemyRed1.png", "texture/enemyBlue3.png" };
    int dx[]{ -2,2 };

    Enemy enemyList[ENEMY_ALIVE];
    for (int i = 0; i < ENEMY_ALIVE; i++)
    {
        enemyList[i].alive = true;

        enemyList[i].pos.x = GetRandomValue(0, 470);
        enemyList[i].pos.y = -50;
        enemyList[i].img = LoadTexture(enemyImgList[GetRandomValue(0, 2)].c_str());
        enemyList[i].rect.width = enemyList[i].img.width * 0.5;
        enemyList[i].rect.height = enemyList[i].img.height * 0.5;
        enemyList[i].rect.x = enemyList[i].pos.x;
        enemyList[i].rect.y = enemyList[i].pos.y;
        enemyList[i].vel.x = dx[GetRandomValue(0, 1)];
        enemyList[i].vel.y = GetRandomValue(30, 60);
        enemyList[i].bulletPos.x = enemyList[i].pos.x + 21;
        enemyList[i].bulletRect.x = enemyList[i].bulletPos.x;
        enemyList[i].bulletActive = true;

    }

    // Enemy explosion
    int regularExpFrame{ 9 };
    int regularCurrentFrame{ 0 };
    float regularLastUpdate{ 1.f / 12.f };
    float regularRunningTime{};

    Texture2D regularExp[regularExpFrame]{
        LoadTexture("texture/regularExplosion00.png"),
        LoadTexture("texture/regularExplosion01.png"),
        LoadTexture("texture/regularExplosion02.png"),
        LoadTexture("texture/regularExplosion03.png"),
        LoadTexture("texture/regularExplosion04.png"),
        LoadTexture("texture/regularExplosion05.png"),
        LoadTexture("texture/regularExplosion06.png"),
        LoadTexture("texture/regularExplosion07.png"),
        LoadTexture("texture/regularExplosion08.png"),
    };

    Rectangle regularExpRect{ 0, 0, explosion[1].width, explosion[1].height };

    // Game loop
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        BeginDrawing();
        // Update

        // TODO
        // BIKIN GAME OVER CONDITION dan main menu

        // Draw
        ClearBackground(WHITE);

        DrawTextureEx(background, Vector2{}, 0.0, 1.0, WHITE);

        if (playerBullet.active)
        {
            playerBullet.rect.x = player.getRect().x + 21;
            playerBullet.rect.y = player.getRect().y;
        }

        // player shoot
        if (IsKeyDown(KEY_SPACE) && player.getAlive() && playerBullet.active)
        {
            PlaySound(shootSound);
            playerBullet.active = false;
        }

        if (!playerBullet.active) playerBullet.rect.y += playerBullet.speedY;

        // check jika peluru player, melewati batas bawah layar
        if (playerBullet.rect.y < -35) playerBullet.active = true;

        if (!gameOver)
        {
            // player explosion death animation
            runningTime += dt;

            if (runningTime >= updateTime)
            {
                if (!player.getAlive())
                {
                    currentFrame++;
                    if (currentFrame > explosionFrame)
                    {
                        currentFrame = 0;
                    }
                }

                runningTime = 0.0;
            }



            // check if player death
            if (!player.getAlive())
            {
                explRect.x = player.getRect().x - explRect.width + 87;
                explRect.y = player.getRect().y - 65;

                DrawTextureEx(explosion[currentFrame], Vector2{ explRect.x, explRect.y }, 0.0, 1.0, WHITE);
            }
            else
            {
                currentFrame = 0;
            }

        }

        // Init enemy position
        for (int i = 0; i < ENEMY_ALIVE; i++)
        {

            if (enemyList[i].bulletActive)
            {
                enemyList[i].bulletRect.x = enemyList[i].pos.x + 21;
                enemyList[i].bulletPos.x = enemyList[i].pos.x + 21;
                enemyList[i].bulletPos.y = enemyList[i].pos.y + 5;
            }

            if (!enemyList[i].alive)
            {
                enemyList[i].pos.x = GetRandomValue(0, WIDTH - enemyList[i].img.width);
                enemyList[i].pos.y = -50;
                UnloadTexture(enemyList[i].img);
                enemyList[i].img = LoadTexture(enemyImgList[GetRandomValue(0, 2)].c_str());
                enemyList[i].alive = true;
            }

        }


        for (int i = 0; i < ENEMY_ALIVE; i++)
        {
            if (enemyList[i].alive && !gameOver && countdown < 0)
            {

                enemyList[i].pos.y += enemyList[i].vel.y * dt;
                enemyList[i].pos.x += enemyList[i].vel.x;

                enemyList[i].rect.x = enemyList[i].pos.x;
                enemyList[i].rect.y = enemyList[i].pos.y;


                // check jika player masih hidup, dan enemy bullet active
                if (enemyList[i].pos.y > 0 && player.getAlive() && enemyList[i].bulletActive) enemyList[i].bulletActive = false;

                // jika enemy bullet tidak active, enemy shoot
                if (!enemyList[i].bulletActive)
                {
                    enemyList[i].bulletPos.y += enemyList[i].bulletSpeed;
                    enemyList[i].bulletRect.y = enemyList[i].bulletPos.y;
                }

                // check jika enemy mentok kiri/kanan, kita pantulkan lawan arah
                if ((enemyList[i].pos.x > WIDTH - enemyList[i].rect.width) || (enemyList[i].pos.x < 0))
                {
                    enemyList[i].vel.x *= -1;
                }

                // check jika enemy melewati batas bawah tinggi layar

                if (enemyList[i].pos.y >= HEIGHT)
                {
                    enemyList[i].alive = false;
                }

                // check jika peluru enemy melewati batas bawah tinggi layar

                if (enemyList[i].bulletPos.y >= HEIGHT)
                {
                    enemyList[i].bulletActive = true;
                }
            }
        }



        // check collision, peluru musuh kena player
        for (int i = 0; i < ENEMY_ALIVE; i++)
        {
            if (enemyList[i].alive)
            {
                if (CheckCollisionRecs(player.getRect(), enemyList[i].bulletRect))
                {
                    if (!enemyList[i].bulletActive && player.getAlive())
                    {
                        player.takeDamage(30);
                        enemyList[i].bulletActive = true;
                    }
                }
            }
        }

        // check collision peluru player kena musuh

        for (int i = 0;i < ENEMY_ALIVE; i++)
        {
            if (!playerBullet.active)
            {
                if (CheckCollisionRecs(playerBullet.rect, enemyList[i].rect))
                {
                    playerBullet.active = true;
                    score += 10;
                    PlaySound(expSfx[GetRandomValue(0, 1)]);
                    enemyList[i].lastPos = enemyList[i].pos;
                    enemyList[i].alive = false;
                    enemyList[i].explode = true;
                    enemyList[i].bulletActive = true;
                }
            }
        }


        // draw enemy explode
        for (int i = 0; i < ENEMY_ALIVE; i++)
        {
            if (enemyList[i].explode)
            {

                regularExpRect.x = enemyList[i].lastPos.x;
                regularExpRect.y = enemyList[i].lastPos.y;

                DrawTextureEx(regularExp[regularCurrentFrame], Vector2{ regularExpRect.x, regularExpRect.y }, 0.0, 0.5, WHITE);
            }
        }

        // enemy explosion death animation
        regularRunningTime += dt;

        if (regularRunningTime >= regularLastUpdate)
        {
            for (int i = 0; i < ENEMY_ALIVE; i++)
            {
                if (enemyList[i].explode)
                {
                    regularCurrentFrame++;
                    if (regularCurrentFrame > regularExpFrame)
                    {
                        regularCurrentFrame = 0;
                        enemyList[i].explode = false;
                    }
                }
                regularRunningTime = 0.0;
            }

        }

        // mouse position, for helper
        // string mousePos = "X = " + to_string(GetMouseX()) + ", Y = " + to_string(GetMouseY());

        // DrawText(mousePos.c_str(), GetMouseX() - 100, GetMouseY(), 20, WHITE);

        // start the game
        if (IsKeyReleased(KEY_ENTER)) startgame = true;

        // countdown start game
        if (startgame)
        {
            runCount += dt;
            if (runCount >= lastCount)
            {
                countdown -= 1;

                runCount = 0.0;
            }
        }

        if (IsKeyDown(KEY_R))
        {
            gameOver = false;
            player.setLive(3);
            score = 0;
            player.setHealth(100);
            countdown = 5;

            for (int i = 0; i < ENEMY_ALIVE; i++)
            {
                enemyList[i].alive = false;
                enemyList[i].bulletActive = true;
            }
        }

        if (IsKeyDown(KEY_X)) gameOver = !gameOver;

        if (player.getLive() < 0)
        {
            gameOver = true;
        }



        if (startgame)
        {

            if (!gameOver)
            {

                if (countdown > 0)
                {
                    DrawText(to_string(countdown).c_str(), WIDTH / 2, HEIGHT / 2, 30, WHITE);
                }

                // draw list of enemy
                for (auto e : enemyList)
                {
                    if (e.alive)
                    {
                        // DrawRectangleLines(e.pos.x, e.pos.y, e.rect.width, e.rect.height, RED);
                        // DrawRectangleLines(e.bulletPos.x, e.bulletPos.y, e.bulletRect.width, e.bulletRect.height, YELLOW);
                        DrawTextureEx(e.bullet, e.bulletPos, 0.0, 0.8, WHITE);
                        DrawTextureEx(e.img, e.pos, 0.0, 0.5, WHITE);
                    }
                }

                // draw score
                DrawText(to_string(score).c_str(), WIDTH / 2.f - 20, 20, 35, WHITE);

                // draw player bullet
                if (player.getAlive()) DrawTextureEx(playerBullet.img, Vector2{ playerBullet.rect.x, playerBullet.rect.y }, 0.0, 0.8, WHITE);

                // Draw player
                player.Update(GetFrameTime());
            }
            else
            {
                // check apakah current score lebih besar dari highscore. jika ya maka ganti highscore dengan current score
                if (score > highScore) highScore = score;
                string yourScore = "Score: " + to_string(score);
                string yourHighScore = "High Score: " + to_string(highScore);

                // draw score dan highscore
                DrawText("Permainan Berakhir", WIDTH / 4 - 20, 70, 30, RED);
                DrawText(yourScore.c_str(), WIDTH / 2 - 55, HEIGHT / 3 + 20, 30, WHITE);
                DrawText(yourHighScore.c_str(), WIDTH / 2 - 95, HEIGHT / 2 + 40, 30, WHITE);
                DrawText("Tekan \"R\" untuk restart game", WIDTH / 3 - 60, HEIGHT / 2 + 155, 20, WHITE);
            }
        }
        else
        {
            DrawText("Space Shooter", WIDTH / 4 + 10, HEIGHT / 2 - 60, 30, WHITE);
            DrawText("Tekan \"ENTER\" untuk bermain!", WIDTH / 4 - 25, HEIGHT / 2 + 60, 20, YELLOW);
            DrawText("Create by Aji Mustofa @pepega90", WIDTH / 4, HEIGHT - 20, 15, WHITE);
        }


        EndDrawing();
    }

    // UnloadSound(playerDeathSound);
    UnloadSound(explosion1);
    UnloadSound(explosion2);
    UnloadSound(shootSound);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}