#pragma once
#include <raylib.h>

class Menu {
public:
    Menu();
    void Update();
    void Draw();
    Color GetButtonColor(const Rectangle& rect);
    int GetSelection();
    void ResetSelection();

private:
    Rectangle btnStart, btnControls, btnExit;
    int selection;
};