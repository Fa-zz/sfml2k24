#pragma once
#include "Terrain.hpp"
#include<vector>
using namespace std;

class World {
public:
    World();
    ~World();
    void genTiles(int height, int width);
    Terrain& getTile(int y, int x);
private:
    vector<Terrain*> allTerrains_;
    sf::Texture overworldTexture_;
    // vector<Terrain*> tiles_;
    // Terrain* tiles_[30][30];
    vector<vector<Terrain*>> tiles_;
    
    int loadTerrainTextures();
    
    // Terrain grassTerrain_;
    // Terrain hillTerrain_;
    // Terrain riverTerrain_;

};