#include "Terrain.hpp"

// Terrain::Terrain(int x, int y, float tileSizeX, float tileSizeY, const sf::Texture& texture, string tileStatus, string tileType, int* tileStats, int* tileMissions)
Terrain::Terrain(int x, int y, float tileSizeX, float tileSizeY, int tileMapX_, int tileMapY_, const sf::Texture& texture)
    : tileSizeX_(tileSizeX), tileSizeY_(tileSizeY), tileMapX_(tileSizeX), tileMapY_(tileSizeY) {
    sprite_.setTexture(texture);
    sprite_.setTextureRect(sf::IntRect(x, y, tileSizeX, tileSizeY));
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

void Terrain::setTileStatus(string x) { 
    tileStatus_ = x; 
    // sf::Color(180,0,0) bloody red color. Lower R value, more darker
    // sf::Color(0,0,0,255) is black (undiscovered)
    // sf::Color(155,155,255,50) is a murky, foggy color (wild)
    // sf::Color(255,255,255) regular (reclaimed)
    if (tileStatus_ == Data::undiscoveredTile) {
        sprite_.setColor(sf::Color(0,0,0,255));
    } else if (tileStatus_ == Data::wildTile) {
        sprite_.setColor(sf::Color(50,155,155,50));
    } else if (tileStatus_ == Data::reclaimedTile) {
        sprite_.setColor(sf::Color(255,255,255));
    } else if (tileStatus_ == Data::activeTile) {
        sprite_.setColor(sf::Color::Yellow);
    }
}
void Terrain::setTileType(string x) { tileType_ = x; }

void Terrain::setTileStats(int* tileStats) {
    for (int i = 0; i < Data::numTileStats; i++) {
        tileStats_[i] = tileStats[i];
    }
}

void Terrain::setTileMissionsArr(int* tileMissions) {
    for (int i = 0; i < Data::numTileMissions; i++) {
        tileMissions_[i] = tileMissions[i];
    }
}

// setTileMissionsInt takes the mission index to change. it is simply flipped
void Terrain::setTileMissionsInt(int missionInt, bool activate) {
    tileMissions_[missionInt] = activate;
}

string Terrain::getTileType() { return tileType_; };
string Terrain::getTileStatus() { return tileStatus_; };
int* Terrain::getTileStats() { return tileStats_; }
int* Terrain::getTileMissions() { return tileMissions_; }

void Terrain::setTileStatStateColor(int tileStatsIndex) {
    if (tileStats_[tileStatsIndex] == 0) {
        tileStatStateColor_ = sf::Color(sf::Color::White);
    } else {
        if (tileStatsIndex == 0) {
            if (tileStats_[tileStatsIndex] == 1)
                tileStatStateColor_ = DefinedColors::foodLow;
            if (tileStats_[tileStatsIndex] == 2)
                tileStatStateColor_ = DefinedColors::foodMed;
            if (tileStats_[tileStatsIndex] == 3)
                tileStatStateColor_ = DefinedColors::foodHigh;
        } else if (tileStatsIndex == 1) {
            if (tileStats_[tileStatsIndex] == 1)
                tileStatStateColor_ = DefinedColors::zombLow;
            if (tileStats_[tileStatsIndex] == 2)
                tileStatStateColor_ = DefinedColors::zombMed;
            if (tileStats_[tileStatsIndex] == 3)
                tileStatStateColor_ = DefinedColors::zombHigh;
        } else if (tileStatsIndex == 2) {
            if (tileStats_[tileStatsIndex] == 1)
                tileStatStateColor_ = DefinedColors::survLow;
            if (tileStats_[tileStatsIndex] == 2)
                tileStatStateColor_ = DefinedColors::survMed;
            if (tileStats_[tileStatsIndex] == 3)
                tileStatStateColor_ = DefinedColors::survHigh;
        }

    }

}

sf::Color Terrain::getTileStatStateColor() { return tileStatStateColor_; }

void Terrain::setMission(string objective, vector<int> assigned, string danger, string daysToTake) {
    missionObjective_ = objective;
    assignedToMission_ = assigned;
    danger_ = danger;
    daysToTake_ = daysToTake;
}
string Terrain::getObjective() { return missionObjective_; }
vector<int> Terrain::getAssigned() {  return assignedToMission_; }
string Terrain::getDanger() { return danger_; }
string Terrain::getDays(){ return daysToTake_; }
void Terrain::clearMission() {
    missionObjective_ = "";
    assignedToMission_.clear();
    danger_ = "";
    daysToTake_ = "";
}
void Terrain::updateDaysToTake() {
    // Decrements a day
    daysToTake_ = to_string( stoi( daysToTake_ ) - 1 );
}
