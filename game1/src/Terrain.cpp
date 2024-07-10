#include "Terrain.hpp"

// Terrain::Terrain(int x, int y, float tileSizeX, float tileSizeY, const sf::Texture& texture, string tileStatus, string tileType, int* tileStats, int* tileMissions)
Terrain::Terrain(int x, int y, float tileSizeX, float tileSizeY, const sf::Texture& texture)
    : tileSizeX_(tileSizeX), tileSizeY_(tileSizeY) {
    // : tileSizeX_(tileSizeX), tileSizeY_(tileSizeY), tileStatus_(tileStatus), tileType_(tileType), tileStats_(tileStats), tileMissions_(tileMissions) {
    sprite_.setTexture(texture);
    sprite_.setTextureRect(sf::IntRect(x, y, tileSizeX, tileSizeY));
    // Set origin for building tiles to bottom-left
    if (tileSizeX > 16 || tileSizeY > 16) {
        sprite_.setOrigin(0.f, tileSizeY);
    }

    // for (int i = 0; i < sizeof(tileStats)/sizeof(tileStats[Data::numTileStats]); i++) {
    //     tileStats_[i] = tileStats[i];
    // }
    // for (int i = 0; i < sizeof(tileMissions)/sizeof(tileMissions[Data::numTileMissions]); i++) {
    //     tileMissions_[i] = tileMissions[i];
    // }

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

// void Terrain::setDummyInfo(int x) { dummyInfo_ = x; }
// int Terrain::getDummyInfo() { return dummyInfo_; };
void Terrain::setTileStatus(string x) { tileStatus_ = x; }
void Terrain::setTileType(string x) { tileType_ = x; }

void Terrain::setTileStats(int* tileStats) {
    for (int i = 0; i < Data::numTileStats; i++) {
        tileStats_[i] = tileStats[i];
    }
}

void Terrain::setTileMissions(int* tileMissions) {
    for (int i = 0; i < sizeof(*tileMissions)/sizeof(tileMissions[0]); i++) {
        tileMissions_[i] = tileMissions[i];
    }
}

string Terrain::getTileType() { return tileType_; };
string Terrain::getTileStatus() { return tileStatus_; };
int* Terrain::getTileStats() { return tileStats_; }
int* Terrain::getTileMissions() { return tileMissions_; }