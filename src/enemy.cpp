#include "enemy.hpp"

Enemy::Enemy(Vector2 startPos, Texture2D tex, float spd) {
    position = startPos;
    spawnPosition = position;
    texture = tex;
    speed = spd;
    movingRight = true;
}

void Enemy::Update(float dt) {
    if (movingRight) {
        position.x += speed * dt;
    } else {
        position.x -= speed * dt;
    }

    if (position.x >= spawnPosition.x + 120) {
        movingRight = false;
    } else if (position.x <= spawnPosition.x - 120) {
        movingRight = true;
    }
}

void Enemy::Draw() {
    DrawTexture(texture, position.x, position.y, WHITE);
}

Rectangle Enemy::GetRect() {
    return {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};
}
