// #pragma once
// #include "Data.hpp"
// #include "Terrain.hpp"
// #include <vector>
// #include <unordered_map>
// #include <iostream>  
// #include <cstdlib> 
// using namespace std;

// class World {
// public:
//     World();
//     ~World();
//     int genTiles(int height, int width);
//     Terrain* getGroundTileAtPos(int y, int x);
//     // Terrain* getBuildingTileAtPos(int y, int x);
//     // vector<vector<Terrain*>> getBuildingTiles();
//     // vector<vector<int>> getCollisionTiles();
//     sf::Vector2u getStartingLoc();
// private:
//     int worldHeight_, worldWidth_;
//     sf::Texture groundTexture_; // groundTexture_: Tex for ground tiles, loaded in from assets
//     // sf::Texture buildingTexture_; // buildingTexture_: Tex for building tiles, loaded in from assets
//     vector<Terrain*> allTerrains_; // allTerrains_: Every vector we create from the loaded textures is added to this vector
//     unordered_map<string, Terrain*> groundMap_; // groundMap_: This maps every terrain object to an ID provided from Tiled. Used to determine ground tile at every location of the game board. See genTiles()
//     // unordered_map<string, Terrain*> buildingMap_; // groundMap_: This maps every terrain object to an ID provided from Tiled. Used to determine ground tile at every location of the game board. See genTiles()
//     // unordered_map<string, int> collisionMap_;
//     vector<vector<Terrain*>> groundTiles_; // groundTiles_: All ground tiles present for every location of the game board. Rendered first
//     // vector<vector<Terrain*>> buildingTiles_; // buildingTiles_: All building tiles present for every location of the game board. Rendered second
//     // vector<vector<int>> collisionTiles_;
//     sf::Vector2u startingLoc_ = {1000,1000};
// 	vector<pair<int, int>> wildTilesCoords;
//     int loadTerrainTextures(); // Loads ground, building, and other textures
//     int loadTerrainMap(); // Loads pieces of terrains
//     int* getRandomStatsArray();
// };