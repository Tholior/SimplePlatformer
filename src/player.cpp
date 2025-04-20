#include "player.hpp"

Player::Player() {
    image = LoadTexture("assets/player.png");
    position.x = 0;
    position.y = GetScreenHeight() - playerOffsetY - image.height;
    velocity = {0, 0};
    isPlayerOnGround = true;
    isPlayerJumping = false;
    camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;
    camera.target = position;
}

Player::~Player() {
    UnloadTexture(image);
}

void Player::Draw() {
    DrawTextureV(image, position, WHITE);
}

void Player::MoveLeft() {
    velocity.x = -playerMovementSpeed;
    if (position.x < 0) {
        position.x = 0;
    }
}

void Player::MoveRight() {
    velocity.x = playerMovementSpeed;
    if (position.x > worldWidth - image.width) {
        position.x = worldWidth - image.width;
    }
}

void Player::Jump() {
    if (isPlayerOnGround || coyoteTimer > 0.0f){
        velocity.y = playerJumpPower;
        isPlayerOnGround = false;
        isPlayerJumping = true;
    }
}

void Player::JumpCutOff() {
    if (isPlayerJumping && velocity.y < playerJumpCutOff) {
        velocity.y = playerJumpCutOff;
    }
}

void Player::Update(float dt) {
    if (!isPlayerOnGround) {
        velocity.y += (velocity.y < 0 ? gravityUp : gravityDown) * dt;
        coyoteTimer -= dt;
    }
    else {
        coyoteTimer = coyoteTime;
    }
    position.x += velocity.x;
    ResolveCollisionX();

    position.y += velocity.y * dt;
    ResolveCollisionY();
}

void Player::ResolveCollisionX() {
    Rectangle playerRect = GetRect();

    for (int i = 0; i < tilesCountY; i++) {
        for (int j = 0; j < tilesCountX; j++) {
            if (Levels::map[i][j] > 0 && Levels::map[i][j] < 7) {
                Rectangle tile = {
                    j * tileSize,
                    i * tileSize,
                     tileSize,
                     tileSize
                };

                if (CheckCollisionRecs(playerRect, tile)) {
                    if (velocity.x > 0) {
                        position.x = tile.x - playerRect.width;
                    } else if (velocity.x < 0) {
                        position.x = tile.x + tileSize;
                    }

                    velocity.x = 0;
                    playerRect = GetRect(); // Refresh rect after change
                }
            }
        }
    }
}

void Player::ResolveCollisionY() {
    Rectangle playerRect = GetRect();
    isPlayerOnGround = false;

    for (int i = 0; i < tilesCountY; i++) {
        for (int j = 0; j < tilesCountX; j++) {
            if (Levels::map[i][j] > 0 && Levels::map[i][j] < 7) {
                Rectangle tile = {
                    j * tileSize,
                    i * tileSize,
                    tileSize,
                    tileSize
                };

                if (CheckCollisionRecs(playerRect, tile)) {
                    float playerBottom = playerRect.y + playerRect.height;
                    float tileTop = tile.y;
                    float playerTop = playerRect.y;
                    float tileBottom = tile.y + tile.height;

                    if (velocity.y > 0 && playerBottom - velocity.y <= tileTop + 1) {
                        position.y = tile.y - playerRect.height;
                        velocity.y = 0;
                        isPlayerOnGround = true;
                        playerRect = GetRect();
                    }
                    else if (velocity.y < 0) {
                        if (playerTop >= tileBottom - 10) {
                            position.y = tileBottom;
                            velocity.y = 0;
                            playerRect = GetRect();
                        }
                    }
                }
            }
        }
    }
}

Rectangle Player::GetRect() {
    return {position.x, position.y, static_cast<float>(image.width), static_cast<float>(image.height)};
}

Vector2 Player::GetPosition() {
    return position;
}

void Player::UpdateCamera() {
    // Horizontally follow player (centered on X), but fixed Y**
    camera.target.x = position.x + image.width / 2.0f;
    camera.target.y = GetScreenHeight() / 2.0f;

    // World bounds
    float halfScreenWidth = GetScreenWidth() / 2.0f;

    // Clamp camera X
    if (camera.target.x < halfScreenWidth) camera.target.x = halfScreenWidth;
    if (camera.target.x > worldWidth - halfScreenWidth) camera.target.x = worldWidth - halfScreenWidth;
}

void Player::Respawn() {
    position.x = 0;
    position.y = GetScreenHeight() - playerOffsetY - image.height;
    velocity = {0, 0};
}

