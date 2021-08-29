#include "raylib.h"

class Player
{
public:
    Player(Vector2 posisi, Texture2D img);
    void Update(float deltaTime);
    Rectangle getRect() { return rect; }
    void takeDamage(int damage);
    void setAlive(bool alive) { this->alive = alive; }
    bool getAlive() { return alive; }
    void setHealth(int heal) { health = heal; }
    int getLive() { return live; }
    void setLive(int live) { this->live = live; }
private:
    bool alive{ true };
    int live{ 3 };
    int health{ 100 };
    Texture2D texture;
    Vector2 pos{};
    Vector2 resetPos{};
    Rectangle rect{};
    int speed{ 200 };
    float scale{ 0.5 };
    float runningTime{};
    float lastUpdate{ 1.0 };
    Sound explodeSfx = LoadSound("sound/rumble1.ogg");
};