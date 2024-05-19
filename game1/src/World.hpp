#pragma once
#include "Terrain.hpp"
#include<vector>
using namespace std;

class World {
public:
    World();
    ~World();
    void genTiles(int height, int width);
    Terrain& getGroundTileAtPos(int y, int x);
    Terrain* getBuildingTileAtPos(int y, int x);
private:
    vector<Terrain*> allTerrains_;
    sf::Texture groundTexture_;
    sf::Texture buildingTexture_;
    // vector<Terrain*> tiles_;
    // Terrain* tiles_[30][30];
    vector<vector<Terrain*>> groundTiles_;
    vector<vector<Terrain*>> buildingTiles_;
    
    int loadTerrainTextures();
    
    // Terrain grassTerrain_;
    // Terrain hillTerrain_;
    // Terrain riverTerrain_;

};