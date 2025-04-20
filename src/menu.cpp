#include "menu.hpp"

Menu::Menu() {
    int screenWidth = GetScreenWidth();
    btnStart = { screenWidth / 2.0f - 100, 150, 200, 50 };
    btnControls = { screenWidth / 2.0f - 100, 220, 200, 50 };
    btnExit = { screenWidth / 2.0f - 100, 290, 200, 50 };
    selection = 0;
}

void Menu::Update() {
    Vector2 mouse = GetMousePosition();

    if (CheckCollisionPointRec(mouse, btnStart) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selection = 1;
    } else if (CheckCollisionPointRec(mouse, btnControls) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selection = 2;
    } else if (CheckCollisionPointRec(mouse, btnExit) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selection = 3;
    }
}

void Menu::Draw() {
    DrawText("Main Menu", GetScreenWidth()/2 - MeasureText("Main Menu", 40)/2, 80, 40, DARKGRAY);

    DrawRectangleRec(btnStart, GetButtonColor(btnStart));
    DrawText("Start Game", btnStart.x + 40, btnStart.y + 10, 20, BLACK);

    DrawRectangleRec(btnControls, GetButtonColor(btnControls));
    DrawText("Controls", btnControls.x + 60, btnControls.y + 10, 20, BLACK);

    DrawRectangleRec(btnExit, GetButtonColor(btnExit));
    DrawText("Exit", btnExit.x + 80, btnExit.y + 10, 20, BLACK);
}

Color Menu::GetButtonColor(const Rectangle &rect) {
    return CheckCollisionPointRec(GetMousePosition(), rect) ? GRAY : LIGHTGRAY;
}


int Menu::GetSelection() {
    return selection;
}

void Menu::ResetSelection() {
    selection = 0;
}