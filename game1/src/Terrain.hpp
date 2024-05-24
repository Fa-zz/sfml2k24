#include <SFML/Graphics.hpp>
#pragma once

class Terrain {
public:
    Terrain(int x, int y, int tileSizeX, int tileSizeY, const sf::Texture& texture);
    ~Terrain();

    sf::Sprite& getSprite();
    int getTileSizeX() const; // Gets the size of the tile in the x direction
    int getTileSizeY() const;

    void setSpritePos(int x, int y);

private:
    int x_; // x: x coordinate of sprite on texture png
    int y_; // y: y coordinate of sprite on texture png
    int tileSizeX_; // tileSizeX: Size of tile in x direction
    int tileSizeY_; // tileSizeY: Size of tile in y direction
    sf::Sprite sprite_;
};
