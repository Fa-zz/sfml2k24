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

void Terrain::setTileStatsInt(int index, int newStat) {
    tileStats_[index] = newStat;
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

void Terrain::setTileMissionsString(string mission, bool activate) {
    for (int i = 0; i < Data::numTileMissions; i++) {
        if (mission == Data::tileMissionsText[i]) {
            tileMissions_[i] = activate;
            break;
        }
    }
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

void Terrain::setMission(string objective, vector<int> assigned, int danger, int daysToTake) {
    missionObjective_ = objective;
    assignedToMission_ = assigned;
    danger_ = danger;
    days_ = daysToTake;
}

void Terrain::setDays(int days) { days_ = days;}

string Terrain::getMission() {
    string mission = "Obj: " + missionObjective_ + " danger: " + to_string(danger_) + " days_: " + to_string(days_);
    mission += " Assigned to mission, IDs: ";
    for (int i = 0; i < assignedToMission_.size(); i++) {
        mission += to_string( assignedToMission_[i] ) + " ";
    }
    return mission;
}
string Terrain::getObjective() { return missionObjective_; }
vector<int> Terrain::getAssigned() {  return assignedToMission_; }
int Terrain::getDanger() { return danger_; }
int Terrain::getDays(){ return days_; }
void Terrain::clearMission() {
    missionObjective_ = "";
    assignedToMission_.clear();
    danger_ = -1;
    days_ = -1;
}
void Terrain::updateDaysToTake() {
    // Decrements a day
    days_ = days_ - 1;
}