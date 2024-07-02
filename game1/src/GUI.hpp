#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <unordered_map>
using namespace std;

class GUI {
public:
    GUI();
    GUI(sf::Vector2u windowSize, int initChoice);
    ~GUI();
    void initAll();
    void initMainMenuElems();
    void initHighlight();
    void setWindowSize(sf::Vector2u windowSize);
    void createTopAndBottomWindow();
    void setDrawingTopAndBottomWindow(bool drawing);
    void setDrawingMainMenu(bool drawing);
    void setDrawingHighlight(bool drawing);
    void setHighlightPos(int x, int y);
    bool hoveringOverMMPlayB(sf::Vector2f mouseCords);
    void hoveringOverObject(sf::Vector2i drawCords);
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
    sf::RectangleShape* highlightedObject_;

    vector<sf::Text*> textContainer_;
    vector<sf::RectangleShape*> guiContainer_;
    unordered_map<string, sf::RectangleShape*> guiMap_;

    bool drawTopAndBottomWindow_;
    bool drawMainMenu_;
    // bool hoveringMMStartB_;
    bool drawHighlight_;

    void initFont();
    // void initGUIElems();
    void initTopAndBottomWindow();
};