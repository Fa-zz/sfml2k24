#include <SFML/Graphics.hpp>
#pragma once

class Terrain {
public:
    Terrain(int x, int y, int tileSizeX, int tileSizeY, const sf::Texture& texture);
    ~Terrain();

    const sf::Sprite& getSprite() const;
    int getTileSizeX() const;
    int getTileSizeY() const;

    void setSpritePos(int x, int y);

private:
    int x_, y_, tileSizeX_, tileSizeY_;
    sf::Sprite sprite_;
};
