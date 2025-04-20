#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <raylib.h>
#include "enemy.hpp"

const int worldWidth = 4000;
const int tilesCountY = 18;
const int tilesCountX = 100;
const float tileSize = 40;

class Levels {
public:
    explicit Levels(int levelId);
    ~Levels();

    void Draw();
    void LoadLevelFromFile(const std::string& filename);
    void UnloadTextures();
    void ResetLevel();
    void UpdateEnemies(float dt);

    std::vector<Enemy> enemies;
    static std::vector<std::vector<int>> map;

private:
    void LoadTextures();

    int levelId;
    Texture2D
        topLeft,
        topMiddle,
        topRight,
        middleLeft,
        middleMid,
        middleRight,
        kiwi,
        cherry,
        enemy,
        finish;
};