#include "levels.hpp"

std::vector<std::vector<int>> Levels::map;

Levels::Levels(int levelId) {
    this -> levelId = levelId;
    LoadTextures();
}

Levels::~Levels() {
}

void Levels::Draw() {
    for (int i = 0; i < tilesCountY; i++) {
        for (int j = 0; j < tilesCountX; j++) {
            switch (map[i][j]) {
                case 1:
                    DrawTexture(topLeft, static_cast<float>(j) * tileSize, static_cast<float>(i) * tileSize, WHITE);
                    break;
                case 2:
                    DrawTexture(topMiddle, static_cast<float>(j) * tileSize, static_cast<float>(i) * tileSize, WHITE);
                    break;
                case 3:
                    DrawTexture(topRight, static_cast<float>(j) * tileSize, static_cast<float>(i) * tileSize, WHITE);
                    break;
                case 4:
                    DrawTexture(middleLeft, static_cast<float>(j) * tileSize, static_cast<float>(i) * tileSize, WHITE);
                    break;
                case 5:
                    DrawTexture(middleMid, static_cast<float>(j) * tileSize, static_cast<float>(i) * tileSize, WHITE);
                    break;
                case 6:
                    DrawTexture(middleRight, static_cast<float>(j) * tileSize, static_cast<float>(i) * tileSize, WHITE);
                    break;
                case 7:
                    DrawTexture(cherry, static_cast<float>(j) * tileSize, static_cast<float>(i) * tileSize, WHITE);
                    break;
                case 8:
                    DrawTexture(kiwi, static_cast<float>(j) * tileSize, static_cast<float>(i) * tileSize, WHITE);
                    break;
                case 9:
                    for (auto& enemy : enemies) {
                        DrawTexture(enemy.texture, enemy.position.x, enemy.position.y, WHITE);
                    }
                    break;
                case 10:
                    DrawTexture(finish, static_cast<float>(j) * tileSize, static_cast<float>(i) * tileSize, WHITE);
                break;
            }
        }
    }
}

void Levels::LoadLevelFromFile(const std::string &filename) {
    map.clear();
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open level file: " << filename << std::endl;
        return;
    }
    std::string line;
    int i = 0;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        int tile;
        int j = 0;
        while (ss >> tile) {
            row.push_back(tile);
            if (tile == 9) {
                enemies.push_back(Enemy({j * tileSize, i * tileSize}, enemy, 200.0f));
            }
            j++;
        }
        map.push_back(row);
        i++;
    }

    file.close();
}

void Levels::LoadTextures() {
    topLeft = LoadTexture("assets/Glewy.png");
    topMiddle = LoadTexture("assets/Gsrodek.png");
    topRight = LoadTexture("assets/Gprawy.png");
    middleLeft = LoadTexture("assets/Slewy.png");
    middleMid = LoadTexture("assets/Ssrodek.png");
    middleRight = LoadTexture("assets/Sprawy.png");
    kiwi = LoadTexture("assets/kiwi.png");
    cherry = LoadTexture("assets/cherry.png");
    enemy = LoadTexture("assets/enemy.png");
    finish = LoadTexture("assets/finish.png");
}

void Levels::UnloadTextures() {
    UnloadTexture(topLeft);
    UnloadTexture(topMiddle);
    UnloadTexture(topRight);
    UnloadTexture(middleLeft);
    UnloadTexture(middleMid);
    UnloadTexture(middleRight);
    UnloadTexture(kiwi);
    UnloadTexture(cherry);
    UnloadTexture(enemy);
    UnloadTexture(finish);
}

void Levels::ResetLevel() {
    LoadLevelFromFile("assets/level" + std::to_string(levelId) + ".txt");
}

void Levels::UpdateEnemies(float dt) {
    for (auto& enemy : enemies) {
        enemy.Update(dt);
    }
}