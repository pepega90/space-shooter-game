#include "raylib.h"


class Enemy
{
public:
    Texture2D img;
    Vector2 pos;
    Rectangle rect;
    bool alive;
    Vector2 vel;
    Texture2D bullet{ LoadTexture("texture/laserRed05.png") };
    Vector2 bulletPos{};
    Rectangle bulletRect{ bulletPos.x, bulletPos.y, bullet.width * 0.8f, bullet.height * 0.8f };
    bool bulletActive{};
    int bulletSpeed{ 10 };
    bool explode{ false };
    Vector2 lastPos;
};