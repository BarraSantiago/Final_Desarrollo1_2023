#include "MenuManager.h"

MenuManager::MenuManager()
{
    background = LoadTexture("../res/background.png");
    logo = LoadTexture("../res/BarbaGames-Logo.png");


    float initialY = 150;
    menuOptions.push_back(TextToRec(playText, initialY));
    menuOptions.push_back(TextToRec(creditsText, initialY * 2));
    menuOptions.push_back(TextToRec(exitText, initialY * 3));
}

MenuManager::~MenuManager()
{
    UnloadTexture(background);
    UnloadTexture(logo);
}

void MenuManager::MenuLoop()
{
    DrawMenu();
    CheckInput();
}

bool MenuManager::InitGame()
{
    return initGame;
}

bool MenuManager::ExitGame()
{
    return exitGame;
}

void MenuManager::DrawMenu() const
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(background, 0, 0,WHITE);
    DrawTexture(logo, 0, static_cast<int>(screenHeight) - logo.height,WHITE);
    constexpr int yPos = 150;

    const int titleFontSize = static_cast<int>(screenHeight) / 8;

    DrawText(titleText, halfWidth - MeasureText(titleText, titleFontSize / 2),
             static_cast<int>(screenHeight) / 25, titleFontSize, GOLD);

    PrintText(playText, yPos, WHITE);
    PrintText(creditsText, yPos * 2, WHITE);
    PrintText(exitText, yPos * 3, WHITE);

    EndDrawing();
}

void MenuManager::CheckInput()
{
    if (!IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) return;
    Vector2 mousePos = GetMousePosition();
    for (int i = 0; i < menuOptions.size(); ++i)
    {
        if (CheckCollisionPointRec(mousePos, menuOptions[i]))
        {
            switch (i)
            {
            case 0:
                initGame = true;
                break;
            case 1:
                DrawCredits();
                break;
            case 2:
                exitGame = true;
                break;
            default:
                break;
            }
        }
    }
}

void MenuManager::DrawCredits()
{
    BeginDrawing();
    PrintText(creditText, screenHeight/2, NEONCYAN);
    EndDrawing();
}

void MenuManager::PrintText(const char* text, int yPos, Color color) const
{
    DrawText(text, GetTextX(text), yPos, fontSize, color);
}

int MenuManager::GetTextX(const char* text) const
{
    return halfWidth - MeasureText(text, fontSize) / 2;
}

Rectangle MenuManager::TextToRec(const char* text, float yPos) const
{
    const float xPos = static_cast<float>(GetTextX(text));
    return {xPos, yPos, static_cast<float>(fontSize), static_cast<float>(fontSize)};
}
