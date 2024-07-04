#include <SFML/Graphics.hpp>
#pragma once

class Terrain {
public:
    Terrain(int x, int y, float tileSizeX, float tileSizeY, const sf::Texture& texture);
    ~Terrain();

    sf::Sprite& getSprite();
    float getTileSizeX() const; // Gets the size of the tile in the x direction
    float getTileSizeY() const;
    sf::Vector2f getPosition() const;

    void setSpritePos(int x, int y);
    void setDummyInfo(int x);
    int getDummyInfo();

private:
    // int x_; // x: x coordinate of sprite on texture png
    // int y_; // y: y coordinate of sprite on texture png
    float tileSizeX_; // tileSizeX: Size of tile in x direction
    float tileSizeY_; // tileSizeY: Size of tile in y direction
    sf::Sprite sprite_;
    int dummyInfo_;
};
