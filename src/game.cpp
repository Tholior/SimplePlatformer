#include "game.hpp"

Game::Game() {
    state = GameState::MENU;
    run = true;
    livesImage = LoadTexture("assets/player.png");
}

Game::~Game() {
    UnloadTexture(livesImage);
    levels.UnloadTextures();
}

void Game::Draw() {
    switch (state) {
        case GameState::MENU:
            menu.Draw();
            break;

        case GameState::PLAYING:
            BeginMode2D(GetCamera());
            levels.Draw();
            player.Draw();
            EndMode2D();
            RenderUI();
            CheckForHighscore();
            break;

        case GameState::PAUSED:
            DrawText("Game Paused\nPress P to resume", 100, 100, 30, DARKGRAY);
            break;

        case GameState::CONTROLS:
            DrawText("Controls:\nArrow keys to move\nSpace to jump\nP to pause\n\nBACKSPACE to go back to Main Menu", 100, 100, 20, DARKGRAY);
            break;

        case GameState::GAME_COMPLETE:
            if (IsKeyPressed(KEY_ENTER)) {
                state = GameState::MENU;
            }
            break;

        case GameState::EXIT:
            break;
    }
}

void Game::Update(float dt) {
    HandleInput();

    switch (state) {
        case GameState::MENU:
            menu.Update();
            HandleMenuSelection();
            break;

        case GameState::PLAYING:
            if (IsKeyPressed(KEY_P)) {
                state = GameState::PAUSED;
                break;
            }
            player.Update(dt);
            player.UpdateCamera();
            CheckForCollisions();
            HandleMovement();
            levels.UpdateEnemies(dt);
            break;

        case GameState::PAUSED:
            if (IsKeyPressed(KEY_P)) {
                state = GameState::PLAYING;
            }
            break;

        case GameState::CONTROLS:
            if (IsKeyPressed(KEY_BACKSPACE)) {
                state = GameState::MENU;
            }
            break;

        case GameState::GAME_COMPLETE: {
            std::string completeText = "Congratulations on finishing the game!\nYour score: " + std::to_string(score);
            DrawText(completeText.c_str(), 100, 100, 30, DARKGREEN);
            DrawText("Press ENTER to return to the menu", 100, 200, 20, DARKGRAY);
            break;
        }

        case GameState::EXIT:
            run = false;
            break;
    }
}

Camera2D& Game::GetCamera() {
    return player.camera;
}

void Game::StartNewGame() {
    player.Respawn();
    lives = 3;
    score = 0;
    levels.enemies.clear();
    highscore = LoadHighscoreFromFile();
    levels.ResetLevel();
}

void Game::HandleInput() {
    moveLeft = IsKeyDown(KEY_LEFT);
    moveRight = IsKeyDown(KEY_RIGHT);
    if (IsKeyPressed(KEY_SPACE)) jumpPressed = true;
    if (IsKeyReleased(KEY_SPACE)) jumpReleased = true;
}

void Game::HandleMovement() {
    player.velocity.x = 0;
    if (moveLeft){
        player.MoveLeft();
    }
    if (moveRight) {
        player.MoveRight();
    }
    if (jumpPressed) {
        player.Jump();
        jumpPressed = false;
    }
    if (jumpReleased) {
        player.JumpCutOff();
        jumpReleased = false;
    }
}

void Game::HandleMenuSelection() {
    switch (menu.GetSelection()) {
        case 1:
            state = GameState::PLAYING;
            StartNewGame();
            break;
        case 2:
            state = GameState::CONTROLS;
            break;
        case 3:
            state = GameState::EXIT;
            break;
    }
    menu.ResetSelection();
}

void Game::CheckForCollisions() {
    Rectangle playerRect = player.GetRect();

    // Falling off the map
    Vector2 position = player.GetPosition();
    if (position.y > GetScreenHeight()) {
        if (lives <= 1) {
            GameOver();
        }
        else {
            lives--;
            player.Respawn();
        }
    }

    // Collisions with enemies
    for (Enemy& enemy : levels.enemies) {
        Rectangle enemyRect = enemy.GetRect();
        if (CheckCollisionRecs(playerRect, enemyRect)) {
            HandleEnemyCollision(enemyRect);
        }
    }

    // Collisions with collectibles
    for (int i = 0; i < tilesCountY; i++) {
        for (int j = 0; j < tilesCountX; j++) {
            int tileType = Levels::map[i][j];
            if (tileType == 7 || tileType == 8) {
                Rectangle collectibleTile = {
                    j * tileSize,
                    i * tileSize,
                    tileSize,
                    tileSize
                };
                if (CheckCollisionRecs(playerRect, collectibleTile)) {
                    HandleCollectibleCollision(tileType, collectibleTile);
                }
            }
            else if (tileType == 10) {
                Rectangle exitTile = {
                    j * tileSize,
                    i * tileSize,
                    tileSize,
                    tileSize
                };

                if (CheckCollisionRecs(playerRect, exitTile)) {
                    LevelComplete();
                    return;
                }
            }
        }
    }
}

void Game::HandleCollectibleCollision(int tileType, Rectangle &collectibleTile) {
    if (tileType == 7) {
        score += 500;
    }
    else if (tileType == 8) {
        score += 2000;
    }
    Levels::map[collectibleTile.y / tileSize][collectibleTile.x / tileSize] = 0;
}

void Game::HandleEnemyCollision(Rectangle &enemyTile) {
    lives--;
    player.Respawn();
    if (lives <= 0) {
        GameOver();
    }
}

void Game::LevelComplete() {
    state = GameState::GAME_COMPLETE;
}

void Game::GameOver() {
    state = GameState::MENU;
}

void Game::DrawLives() {
    float x = 20;
    for (int i = 0; i < lives; i++) {
        DrawTextureV(livesImage, {x, 20}, WHITE);
        x += 50;
    }
}

void Game::DrawScore() {
    std::string scoreText = "Score: " + std::to_string(score);
    int fontSize = 20;
    int x = GetScreenWidth() - MeasureText(scoreText.c_str(), fontSize) - 20;
    int y = 20;
    DrawText(scoreText.c_str(), x, y, fontSize, DARKGRAY);
}

void Game::DrawHighscore() {
    std::string highscoreText = "High Score: " + std::to_string(highscore);
    int fontSize = 20;
    int x = GetScreenWidth() - MeasureText(highscoreText.c_str(), fontSize) - 20;
    int y = 50;
    DrawText(highscoreText.c_str(), x, y, fontSize, DARKGRAY);
}

void Game::RenderUI() {
    DrawLives();
    DrawScore();
    DrawHighscore();
}

void Game::CheckForHighscore() {
    if (score > highscore) {
        highscore = score;
        SaveHighscoreToFile(highscore);
    }
}

void Game::SaveHighscoreToFile(int highscore) {
    std::ofstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open()) {
        highscoreFile << highscore;
        highscoreFile.close();
    }
    else {
        std::cerr << "Failed to save highscore to file" << std::endl;
    }
}

int Game::LoadHighscoreFromFile() {
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open()) {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    }
    else {
        std::cerr << "Failed to load highscore from file." << std::endl;
    }
    return loadedHighscore;
}