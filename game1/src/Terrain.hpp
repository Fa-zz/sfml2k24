#pragma once
#include <SFML/Graphics.hpp>
#include "Data.hpp"
#include <string>
#include <vector>
using namespace std;

class Terrain {
public:
    // Terrain(int x, int y, float tileSizeX, float tileSizeY, const sf::Texture& texture, string tileStatus, string tileType, int* tileStats, int* tileMissions);
    Terrain(int x, int y, float tileSizeX, float tileSizeY, const sf::Texture& texture);
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
    void setTileMissions(int* tileMissions);
    string getTileType();
    string getTileStatus();
    int* getTileStats();
    int* getTileMissions();

private:
    // int x_; // x: x coordinate of sprite on texture png
    // int y_; // y: y coordinate of sprite on texture png
    float tileSizeX_; // tileSizeX: Size of tile in x direction
    float tileSizeY_; // tileSizeY: Size of tile in y direction
    sf::Sprite sprite_;
    // int dummyInfo_;
    string tileStatus_;
    string tileType_;
    // int tileStats_[Data::numTileStats];
    // int tileMissions_[Data::numTileMissions];
    // vector<int> tileStats_;
    // vector<int> tileMissions_;
    int tileStats_[Data::numTileStats];
    int tileMissions_[Data::numTileMissions];
};
