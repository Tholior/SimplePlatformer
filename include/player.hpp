#pragma once
#include <raylib.h>
#include "levels.hpp"

class Player {
public:
    Player();
    ~Player();

    void Draw();
    void MoveLeft();
    void MoveRight();
    void Jump();
    void JumpCutOff();
    void Update(float dt);
    void ResolveCollisionX();
    void ResolveCollisionY();
    Rectangle GetRect();
    Vector2 GetPosition();
    void UpdateCamera();
    void Respawn();

    Camera2D camera;
    Vector2 velocity;

private:
    Vector2 position;
    Texture2D image;
    const float playerMovementSpeed = 7;
    const float gravityUp = 1000.0f;
    const float gravityDown = 2000.0f;
    const float playerJumpPower = -550.0f;
    const float playerJumpCutOff = -200.0f;
    float coyoteTime = 0.05f;
    float coyoteTimer = 0.0f;
    bool isPlayerOnGround;
    bool isPlayerJumping;
    const float playerOffsetY = 40; // floor size
};