#pragma once
#include <SFML/Graphics.hpp>
#include "Data.hpp"
#include "Colors.hpp"
#include <string>
#include <vector>
using namespace std;

class Terrain {
public:
    // Terrain(int x, int y, float tileSizeX, float tileSizeY, const sf::Texture& texture, string tileStatus, string tileType, int* tileStats, int* tileMissions);
    Terrain(int x, int y, float tileSizeX, float tileSizeY, int tileMapX_, int tileMapY_, const sf::Texture& texture);
    ~Terrain();

    sf::Sprite& getSprite();
    float getTileSizeX() const; // Gets the size of the tile in the x direction
    float getTileSizeY() const;
    sf::Vector2f getPosition() const;

    void setSpritePos(int x, int y);
    // void setDummyInfo(int x);
    // int getDummyInfo();
    void setTileStatus(string x);
    void setTileType(string x);
    void setTileStats(int* tileStats);
    void setTileMissionsArr(int* tileMissions);
    void setTileMissionsInt(int missionIndex, bool activate);
    string getTileType();
    string getTileStatus();
    int* getTileStats();
    int* getTileMissions();
    void setTileStatStateColor(int tileStatsIndex);
    sf::Color getTileStatStateColor();

    void setMission(string objective, vector<int> assigned, string danger, string daysToTake);
    string getObjective();
    vector<int> getAssigned();
    string getDanger();
    string getDays();
    void clearMission();
    void updateDaysToTake();

private:
    // int x_; // x: x coordinate of sprite on texture png
    // int y_; // y: y coordinate of sprite on texture png
    float tileSizeX_; // tileSizeX: Size of tile in x direction
    float tileSizeY_; // tileSizeY: Size of tile in y direction
    int tileMapX_, tileMapY_; // coordinates of sprite on the tileMap
    sf::Sprite sprite_;
    string tileStatus_;
    string tileType_;
    sf::Color tileStatStateColor_;
    // int tileStats_[Data::numTileStats];
    // int tileMissions_[Data::numTileMissions];
    // vector<int> tileStats_;
    // vector<int> tileMissions_;
    int tileStats_[Data::numTileStats];
    int tileMissions_[Data::numTileMissions];

    // Mission infos
    string missionObjective_;
    vector<int> assignedToMission_;
    // int missionY_, missionX_;
    string danger_, daysToTake_;

};
