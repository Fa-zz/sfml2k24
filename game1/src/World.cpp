#include "World.hpp"
#include "Terrain.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// CONSTRUCTOR AND DESTRUCTOR 
World::World() {
    // srand(static_cast<unsigned int>(time(0)));
    if (loadTerrainTextures() != 0)
        cerr << "Failed to load terrain textures" << endl;
    // loadTerrainMap();
}

World::~World() {
    // for (auto& pair : groundMap_) {
    //     delete pair.second;
    // }
    // groundMap_.clear();
    for (int i = 0; i < groundTiles_.size(); i++) {
        for (int j = 0; j < groundTiles_[i].size(); j++) {
            delete groundTiles_[i][j];
        }
    }
}

int World::genTiles(int height, int width) {
    groundTiles_.resize(height);  // Resize outer vector to the desired height
    for (int i = 0; i < height; ++i) {
        groundTiles_[i].resize(width, nullptr);
    }
    int tileMissionsFull[Data::numTileMissions] = {1, 1, 1, 1};

    for (int i = 0; i < groundTiles_.size(); i++) {
        for (int j = 0; j < groundTiles_[i].size(); j++) {
            int lb = 0, ub = 7;
            int randNum = rand() % (ub - lb + 1) + lb;
            // cout << "genTiles, randNum = " << randNum << endl;

            // Create a new Terrain object for each tile
            Terrain* newTile = nullptr;
            switch (randNum) {
                case 0:
                    newTile = new Terrain(64, 0, 16, 16, groundTexture_);
                    break;
                case 1:
                    newTile = new Terrain(64, 48, 16, 16, groundTexture_);
                    break;
                case 2:
                    newTile = new Terrain(64, 96, 16, 16, groundTexture_);
                    break;
                case 3:
                    newTile = new Terrain(160, 0, 16, 16, groundTexture_);
                    break;
                case 4:
                    newTile = new Terrain(64, 192, 16, 16, groundTexture_);
                    break;
                case 5:
                    newTile = new Terrain(48, 288, 16, 16, groundTexture_);
                    break;
                case 6:
                    newTile = new Terrain(64, 144, 16, 16, groundTexture_);
                    break;
                case 7:
                    newTile = new Terrain(48, 336, 16, 16, groundTexture_);
                    break;
                default:
                    newTile = new Terrain(64, 0, 16, 16, groundTexture_);
                    break;
            }

            newTile->setTileType(Data::tileTypes[randNum]);
            newTile->setTileStats(getRandomStatsArray());
            newTile->setTileMissions(tileMissionsFull);
            newTile->setTileStatus(Data::wildTile);

            groundTiles_[i][j] = newTile;

            // cout << "Tile type: " << newTile->getTileType() << endl;
            // cout << "Tile stats: " << newTile->getTileStats()[0] << " " << newTile->getTileStats()[1] << " " << newTile->getTileStats()[2] << endl;
            // cout << " " << endl;
        }
    }

    return 0;
}

// int World::genTiles(int height, int width) {
//     groundTiles_.resize(height);  // Resize outer vector to the desired height
//     for (int i = 0; i < height; ++i) {
//         groundTiles_[i].resize(width, nullptr);
//     }
//     int tileMissionsFull[Data::numTileMissions] = {1,1,1,1};
//     // int tileMissionsUndiscovered[Data::numTileMissions] = {1,1,1,1};

//     for (int i = 0; i < groundTiles_.size(); i++)  { 
//         for (int j = 0; j < groundTiles_[i].size(); j++) { 
//             int lb = 0, ub = 7;
//             int randNum = rand() % (ub - lb + 1) + lb;
//             // cout << "genTiles, randNum = " << randNum << endl;
//             switch(randNum) {
//                 case 0:
//                     groundTiles_[i][j] = groundMap_["apartment"];
//                     break;
//                 case 1:
//                     groundTiles_[i][j] = groundMap_["church"];
//                     break;
//                 case 2:
//                     groundTiles_[i][j] = groundMap_["park"];
//                     break;
//                 case 3:
//                     groundTiles_[i][j] = groundMap_["school"];
//                     break;
//                 case 4:
//                     groundTiles_[i][j] = groundMap_["restaurant"];
//                     break;
//                 case 5:
//                     groundTiles_[i][j] = groundMap_["gas station"];
//                     break;
//                 case 6:
//                     groundTiles_[i][j] = groundMap_["office"];
//                     break;
//                 case 7:
//                     groundTiles_[i][j] = groundMap_["police HQ"];
//                     break;
//                 default:
//                     groundTiles_[i][j] = groundMap_["apartment"];
//                     break;
//             }
//             groundTiles_[i][j]->setTileType(Data::tileTypes[randNum]);
//             groundTiles_[i][j]->setTileStats(getRandomStatsArray());
//             groundTiles_[i][j]->setTileMissions(tileMissionsFull);
//             groundTiles_[i][j]->setTileStatus(Data::wildTile);
//             cout << "Tile type: " << groundTiles_[i][j]->getTileType() << endl;
//             cout << "Tile stats: " << groundTiles_[i][j]->getTileStats()[0] << " " << groundTiles_[i][j]->getTileStats()[1] << " " << groundTiles_[i][j]->getTileStats()[2] << endl;
//             // cout << "Tile type: " << groundTiles_[i][j]->getTileType();
//             // cout << "Tile type: " << groundTiles_[i][j]->getTileType();
//             cout << " " << endl;
//         }
//     }
//     // Load ground tiles from CSV
//     // ifstream groundCSV("levels/level1_ground.csv");
//     // if (!groundCSV.is_open()) {
//     //     cerr << "Failed to open ground CSV file" << endl;
//     //     return -1;
//     // }
//     // string line;
//     // int y = 0;
//     // while (getline(groundCSV, line) && y < height) {
//     //     stringstream ss(line);
//     //     string tiledID;
//     //     int x = 0;
//     //     while (getline(ss, tiledID, ',') && x < width) {
//     //         if (groundMap_.find(tiledID) != groundMap_.end()) {
//     //             groundTiles_[y][x] = groundMap_.at(tiledID);
//     //             if (groundTiles_[y][x] != nullptr) {
//     //                 // groundTiles_[y][x]->setDummyInfo(rand() % 100 + 1);
//     //                 groundTiles_[y][x]->setTileStatus(Data::wildTile);
//     //             }
//     //             //cout << "Ground tile at x: " << x << " y: " << y << " is " << tiledID << " , or " << groundMap_.at(tiledID) << endl;
//     //         } else {
//     //             groundTiles_[y][x] = nullptr; // ID is not found, there is nothing at the tile
//     //         }
//     //         x++;
//     //     }
//     //     y++;
//     // }
//     return 0;
// }

Terrain* World::getGroundTileAtPos(int y, int x) {
    if (groundTiles_[y][x] == nullptr) {
        return nullptr;
    }
    return groundTiles_[y][x];
}

// Terrain* World::getBuildingTileAtPos(int y, int x) {
//     return buildingTiles_[y][x];
// }

int World::loadTerrainTextures() {
    if (!groundTexture_.loadFromFile("assets/groundtiles.png")) {
        return -1;
    }
    return 0;
}

int World::loadTerrainMap() {
    // Ground tiles initialization
    // groundMap_["-1"] = nullptr;

    // groundMap_[Data::tileTypes[0]] = new Terrain(64, 0, 16, 16, groundTexture_, Data::undiscoveredTile, Data::tileTypes[0], getRandomStatsArray(), tileMissionsFull);
    // groundMap_[Data::tileTypes[1]] = new Terrain(64, 48, 16, 16, groundTexture_, Data::undiscoveredTile, Data::tileTypes[1], getRandomStatsArray(), tileMissionsFull);
    // groundMap_[Data::tileTypes[2]] = new Terrain(64, 96, 16, 16, groundTexture_, Data::undiscoveredTile, Data::tileTypes[2], getRandomStatsArray(), tileMissionsFull);

    // groundMap_[Data::tileTypes[0]] = new Terrain(64, 0, 16, 16, groundTexture_); // apartment
    // groundMap_[Data::tileTypes[1]] = new Terrain(64, 48, 16, 16, groundTexture_); // church
    // groundMap_[Data::tileTypes[2]] = new Terrain(64, 96, 16, 16, groundTexture_); // park
    // groundMap_[Data::tileTypes[3]] = new Terrain(160, 0, 16, 16, groundTexture_); // school
    // groundMap_[Data::tileTypes[4]] = new Terrain(64, 192, 16, 16, groundTexture_); // restaurant
    // groundMap_[Data::tileTypes[5]] = new Terrain(48, 288, 16, 16, groundTexture_); // gas station
    // groundMap_[Data::tileTypes[6]] = new Terrain(64, 144, 16, 16, groundTexture_); // office
    // groundMap_[Data::tileTypes[7]] = new Terrain(48, 336, 16, 16, groundTexture_); // police HQ

    return 0;
}

int* World::getRandomStatsArray() {
    int lb = 0, ub = 5;
    static int r[Data::numTileStats] = {0, 0, 0};
    for (int i = 0; i < Data::numTileStats; i++) {
        int randNum = rand() % (ub - lb + 1) + lb;
        // cout << "Random stats arr. RandNum: " << randNum << " at index i: " << i << endl;
        // cout << "Tile stat: " << Data::tileStats[i] << "Tile stat desc: " << Data::tileStatDescs[randNum] << endl;
        r[i] = randNum;
    }
    return r;
}