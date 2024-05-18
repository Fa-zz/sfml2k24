#include <SFML/Graphics.hpp>
#pragma once

class Terrain {
public:
    Terrain(int x, int y, int tileSize, const sf::Texture& texture);
    ~Terrain();

    const sf::Sprite& getSprite() const;
    int getTileSize() const;

    void setSpritePos(int x, int y);

private:
    int x_, y_, tileSize_;
    sf::Sprite sprite_;
};
