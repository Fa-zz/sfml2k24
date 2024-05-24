#include "Terrain.hpp"

Terrain::Terrain(int x, int y, int tileSizeX, int tileSizeY, const sf::Texture& texture)
    : x_(x), y_(y), tileSizeX_(tileSizeX), tileSizeY_(tileSizeY) {
    sprite_.setTexture(texture);
    sprite_.setTextureRect(sf::IntRect(x, y, tileSizeX, tileSizeY));
}

Terrain::~Terrain() { }

int Terrain::getTileSizeX() const { return tileSizeX_; }
int Terrain::getTileSizeY() const { return tileSizeY_; }

sf::Sprite &Terrain::getSprite() {
    return sprite_;
}

void Terrain::setSpritePos(int x, int y) {
    sprite_.setPosition(x * 16, y * 16);
}
