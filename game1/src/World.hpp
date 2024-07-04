#pragma once
#include "Terrain.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>  
#include <ctime>  
using namespace std;

class World {
public:
    World();
    ~World();
    int genTiles(int height, int width);
    Terrain* getGroundTileAtPos(int y, int x);
    Terrain* getBuildingTileAtPos(int y, int x);
    // vector<vector<Terrain*>> getBuildingTiles();
    vector<vector<int>> getCollisionTiles();
private:
    sf::Texture groundTexture_; // groundTexture_: Tex for ground tiles, loaded in from assets
    // sf::Texture buildingTexture_; // buildingTexture_: Tex for building tiles, loaded in from assets
    vector<Terrain*> allTerrains_; // allTerrains_: Every vector we create from the loaded textures is added to this vector
    // NOTE: If allTerrains_ is just used for destructor, I think we can just iterate over groundMap_ and delete each, making it obsolete
    unordered_map<string, Terrain*> groundMap_; // groundMap_: This maps every terrain object to an ID provided from Tiled. Used to determine ground tile at every location of the game board. See genTiles()
    // unordered_map<string, Terrain*> buildingMap_; // groundMap_: This maps every terrain object to an ID provided from Tiled. Used to determine ground tile at every location of the game board. See genTiles()
    // unordered_map<string, int> collisionMap_;
    vector<vector<Terrain*>> groundTiles_; // groundTiles_: All ground tiles present for every location of the game board. Rendered first
    vector<vector<Terrain*>> buildingTiles_; // buildingTiles_: All building tiles present for every location of the game board. Rendered second
    // vector<vector<int>> collisionTiles_;

    int loadTerrainTextures(); // Loads ground, building, and other textures
    int loadTerrainMap(); // Loads pieces of terrains
};