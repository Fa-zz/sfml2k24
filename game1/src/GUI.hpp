#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
using namespace std;

class GUI {
public:
    GUI();
    ~GUI();
    void renderGUIElems(sf::RenderTarget& rt, const sf::Vector2u& windowSize);

private:
    sf::Font font_;
    sf::Text topWindowText_;
    // sf::Texture windowTexture_;
    // sf::Sprite topWindowLeft_;
    // sf::Sprite topWindowRight_;
    sf::RectangleShape* topWindow_;
    sf::RectangleShape* topWindowPortrait_;
    sf::RectangleShape* bottomWindow_;
    vector<sf::RectangleShape*> shapes;
    // float topWindowSizeX, topWindowSizeY;

    void initFont();
    void initGUIElems();
};