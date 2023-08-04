#pragma once
#include <raylib.h>
#include <vector>

class MenuManager
{
public:
    MenuManager();
    ~MenuManager();
    void MenuLoop();
    bool InitGame() const;
    bool ExitGame() const;
        
private:
    void DrawMenu() const;
    void CheckInput();
    void DrawCredits() const;
    void DrawRules() const;
    void PrintText(const char* text, int yPos, int fSize, Color color) const;
    int GetTextX(const char* text, int fSize) const;
    Rectangle TextToRec(const char* text, float yPos) const;
    bool InputRecived();

    std::vector<Rectangle> menuOptions;

    Texture2D background{};
    Texture2D logo{};

    bool initGame = false;
    bool exitGame = false;
    
    const char* titleText = "8Bit Battle Simulator";
    const char* playText = "Play";
    const char* creditsText = "Credits";
    const char* creditText = "Made by Santiago Barra";
    const char* continueClick = "Press any key to continue!";
    const char* exitText = "EXIT";
    const char* rules1 = "Press Q, W or E to spawn controllable units";
    const char* rules2 = "Press 1, 2 or 3 to spawn enemy units";
    const char* rules3 = "Left Click select units, Right click move them";

    const float screenWidth = static_cast<float>(GetScreenWidth());
    const float screenHeight = static_cast<float>(GetScreenHeight());

    const int halfWidth = static_cast<int>(screenWidth) / 2;
    const int fontSize = static_cast<int>(screenHeight) / 9;

    const float xPosition = screenWidth / 25.0f;
    const float yPosition = screenHeight / 9.0f;
    const float xRepos = xPosition - xPosition / 5;
    const float yRepos = yPosition / 20;

    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
};
