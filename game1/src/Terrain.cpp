#include "Terrain.hpp"

Terrain::Terrain(int x, int y, int tileSize, const sf::Texture& texture)
    : x_(x), y_(y), tileSize_(tileSize) {
    sprite_.setTexture(texture);
    sprite_.setTextureRect(sf::IntRect(x, y, tileSize, tileSize));
}

Terrain::~Terrain() { }

int Terrain::getTileSize() const { return tileSize_; }

const sf::Sprite& Terrain::getSprite() const {
    return sprite_;
}

void Terrain::setSpritePos(int x, int y) {
    sprite_.setPosition(x * tileSize_, y * tileSize_);
}
