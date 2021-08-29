#include "raylib.h"
#include "Player.h"


Player::Player(Vector2 posisi, Texture2D img) :pos(posisi), texture(img), resetPos(posisi) {}


void Player::Update(float deltaTime)
{

    if (alive)
    {
        if (IsKeyDown(KEY_D))pos.x += speed * deltaTime;
        if (IsKeyDown(KEY_A))pos.x -= speed * deltaTime;
        if (IsKeyDown(KEY_W))pos.y -= speed * deltaTime;
        if (IsKeyDown(KEY_S))pos.y += speed * deltaTime;
    }

    rect.x = pos.x;
    rect.y = pos.y;
    rect.width = texture.width * scale;
    rect.height = texture.width * scale;

    runningTime += deltaTime;
    if (runningTime >= lastUpdate)
    {
        if (!alive)
        {
            pos = resetPos;
            health = 100;
            live -= 1;
            alive = true;
        }
        runningTime = 0.0;
    }


    // Draw live player
    for (int i = 0; i < live; i++)
    {
        DrawTextureEx(texture, Vector2{ 45.f * static_cast<float>(i) + 350, 20 }, 0.0, 0.3, WHITE);
    }

    // Draw health player
    Color colorHealth = GREEN;
    if (health <= 60) colorHealth = YELLOW;
    if (health <= 30) colorHealth = RED;

    DrawRectangle(10, 20, health, 20, colorHealth);

    // Draw player
    if (alive) DrawTextureEx(texture, pos, 0.0, scale, WHITE);

    // Draw rectangle around him, for checking collision (delete later)
    // DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, YELLOW);

}

void Player::takeDamage(int damage)
{
    if (health > 0)
    {
        health -= damage;
    }
    else
    {

        PlaySound(explodeSfx);
        alive = false;

    }
}