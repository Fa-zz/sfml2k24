#include "Terrain.hpp"

Terrain::Terrain(int x, int y, float tileSizeX, float tileSizeY, const sf::Texture& texture)
    // : x_(x), y_(y), tileSizeX_(tileSizeX), tileSizeY_(tileSizeY) {
    : tileSizeX_(tileSizeX), tileSizeY_(tileSizeY) {
    sprite_.setTexture(texture);
    sprite_.setTextureRect(sf::IntRect(x, y, tileSizeX, tileSizeY));
    // Set origin for building tiles to bottom-left
    if (tileSizeX > 16 || tileSizeY > 16) {
        sprite_.setOrigin(0.f, tileSizeY);
    }
}

Terrain::~Terrain() { }

float Terrain::getTileSizeX() const { return tileSizeX_; }
float Terrain::getTileSizeY() const { return tileSizeY_; }

sf::Sprite& Terrain::getSprite() {
    return sprite_;
}

sf::Vector2f Terrain::getPosition() const {
    return sprite_.getPosition();
}

void Terrain::setSpritePos(int x, int y) {
    if (sprite_.getOrigin().y != 0.f) {
        sprite_.setPosition(x * 16.f, (y + 1) * 16.f);
    } else {
        sprite_.setPosition(x * 16.f, y * 16.f);
    }
}

void Terrain::setDummyInfo(int x) { dummyInfo_ = x; }
int Terrain::getDummyInfo() { return dummyInfo_; };
