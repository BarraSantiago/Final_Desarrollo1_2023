#include "MenuManager.h"

MenuManager::MenuManager()
{
    background = LoadTexture("../res/background.png");
    logo = LoadTexture("../res/BarbaGames-Logo.png");


    float initialY = 150;
    menuOptions.push_back(TextToRec(playText, initialY));
    menuOptions.push_back(TextToRec(creditsText, initialY * 2));
    menuOptions.push_back(TextToRec(exitText, initialY * 3));


    menuOptions[0].width *= 2.5f;
    menuOptions[0].x -= menuOptions[0].width / 10;
    menuOptions[1].width *= 4;
    menuOptions[1].x -= menuOptions[1].width / 25;
    menuOptions[2].width *= 3.f;
    menuOptions[2].x -= menuOptions[2].width / 10;
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

bool MenuManager::InitGame() const
{
    return initGame;
}

bool MenuManager::ExitGame() const
{
    return exitGame;
}

void MenuManager::DrawMenu() const
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexture(background, 0, 0,WHITE);
    DrawTexture(logo, 0, static_cast<int>(screenHeight) - logo.height,WHITE);

    DrawRules();

    constexpr int yPos = 150;

    const int titleFontSize = static_cast<int>(screenHeight) / 8;

    for (Rectangle rec : menuOptions)
    {
        DrawRectangleLines(rec.x, rec.y, rec.width, rec.height, GOLD);
    }

    DrawText(titleText, halfWidth - MeasureText(titleText, titleFontSize / 2),
             static_cast<int>(screenHeight) / 25, titleFontSize, GOLD);

    PrintText(playText, yPos, fontSize, WHITE);
    PrintText(creditsText, yPos * 2, fontSize, WHITE);
    PrintText(exitText, yPos * 3, fontSize, WHITE);

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
                while (!InputRecived())
                {
                    DrawCredits();
                }
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

void MenuManager::DrawCredits() const
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(background, 0, 0,WHITE);
    PrintText(creditText, screenHeight / 4, fontSize, NEONCYAN);
    PrintText(continueClick, screenHeight / 1.5, fontSize / 2, WHITE);
    EndDrawing();
}

void MenuManager::DrawRules() const
{
    DrawText(rules1, 400, static_cast<int>(screenHeight - logo.height * 1.1), fontSize / 4, GOLD);
    DrawText(rules3, 400, static_cast<int>(screenHeight - logo.height / 1.4), fontSize / 4, GOLD);
    DrawText(rules2, 400, static_cast<int>(screenHeight) - logo.height / 3, fontSize / 4, GOLD);
}

void MenuManager::PrintText(const char* text, int yPos, int fSize, Color color) const
{
    DrawText(text, GetTextX(text, fSize), yPos, fSize, color);
}

int MenuManager::GetTextX(const char* text, int fSize) const
{
    return halfWidth - MeasureText(text, fSize) / 2;
}

Rectangle MenuManager::TextToRec(const char* text, float yPos) const
{
    const float xPos = static_cast<float>(GetTextX(text, fontSize));
    return {xPos, yPos, static_cast<float>(fontSize), static_cast<float>(fontSize)};
}

bool MenuManager::InputRecived()
{
    for (int key = 0; key < 512; key++)
    {
        if (IsKeyPressed(key)) return true;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return true;
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) return true;

    return false;
}
