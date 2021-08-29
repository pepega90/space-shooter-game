#include "raylib.h"

class Bullet
{
public:
    Texture2D img;
    Rectangle rect;
    bool active;
    int speedX;
    int speedY;
};