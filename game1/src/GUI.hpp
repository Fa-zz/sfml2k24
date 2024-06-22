#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
using namespace std;

class GUI {
public:
    GUI();
    GUI(sf::Vector2u windowSize, int initChoice);
    ~GUI();
    void initMainMenuElems();
    void createTopAndBottomWindow();
    void setDrawingTopAndBottomWindow(bool drawing);
    void setDrawingMainMenu(bool drawing);
    void setWindowSize(sf::Vector2u windowSize);
    bool hoveringOverMMPlayB(sf::Vector2f mouseCords);
    void renderGUIElems(sf::RenderTarget& rt);
private:
    sf::Vector2u windowSize_;
    sf::Font font_;
    sf::Text topWindowText_;
    // sf::Texture windowTexture_;
    // sf::Sprite topWindowLeft_;
    // sf::Sprite topWindowRight_;
    sf::RectangleShape* topWindow_;
    // float topWindowSizeX, topWindowSizeY;
    sf::RectangleShape* topWindowPortrait_;
    sf::RectangleShape* bottomWindow_;
    // vector<sf::RectangleShape*> buttons_;
    sf::Text mainMenuPlayButtonText_;
    sf::RectangleShape* mainMenuPlayButton_;

    vector<sf::Text*> textContainer_;
    vector<sf::RectangleShape*> guiContainer_;

    bool drawTopAndBottomWindow_;
    bool drawMainMenu_;
    bool hoveringMMStartB_;

    void initFont();
    // void initGUIElems();
    void initTopAndBottomWindow();
};