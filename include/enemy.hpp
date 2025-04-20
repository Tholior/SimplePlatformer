#pragma once
#include <raylib.h>

class Enemy {
public:
    Enemy(Vector2 startPos, Texture2D tex, float spd);

    Vector2 position;
    Vector2 spawnPosition;
    Texture2D texture;
    float speed;
    bool movingRight;

    void Update(float dt);
    void Draw();
    Rectangle GetRect();
};