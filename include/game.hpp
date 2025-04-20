#pragma once
#include "player.hpp"
#include "levels.hpp"
#include "menu.hpp"
#include "gamestate.hpp"
#include "enemy.hpp"

class Game {
public:
    Game();
    ~Game();

    void Draw();
    void Update(float dt);
    Camera2D& GetCamera();

    bool run;
    int lives;
    int score;
    int highscore;

private:
    void StartNewGame();
    void HandleInput();
    void HandleMovement();
    void HandleMenuSelection();
    void CheckForCollisions();
    void HandleCollectibleCollision(int tileType, Rectangle& collectibleTile);
    void HandleEnemyCollision(Rectangle& enemyTile);
    void LevelComplete();
    void GameOver();
    void DrawLives();
    void DrawScore();
    void DrawHighscore();
    void RenderUI();
    void CheckForHighscore();
    void SaveHighscoreToFile(int highscore);
    int LoadHighscoreFromFile();

    Player player;
    Levels levels = Levels(1);
    Menu menu;
    GameState state;
    Texture2D livesImage;
    bool moveLeft = false;
    bool moveRight = false;
    bool jumpPressed = false;
    bool jumpReleased = false;

};