#include "World.hpp"
#include "Terrain.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

World::World() {
    if (loadTerrainTextures() != 0)
        cerr << "Failed to load terrain textures" << endl;
    loadTerrainMap();
}

World::~World() {
    for (Terrain* terrain : allTerrains_) {
        delete terrain;
    }
}
// TODO: At some later point, genTiles should determine which level's tiles are being obtained
// Instead of having 2 while loops, we should have a helper func that takes as arg map, tiles etc
int World::genTiles(int height, int width) {
    groundTiles_.resize(height);  // Resize outer vector to the desired height
    for (int i = 0; i < height; ++i) {
        groundTiles_[i].resize(width, nullptr);  // Resize inner vector to the desired width, initializing to nullptr
    }
    buildingTiles_.resize(height);
    for (int i = 0; i < height; ++i) {
        buildingTiles_[i].resize(width, nullptr);  // Resize inner vector to the desired width, initializing to nullptr
    }

    // Load ground tiles from CSV
    ifstream groundCSV("levels/level1_ground.csv");
    if (!groundCSV.is_open()) {
        cerr << "Failed to open ground CSV file" << endl;
        return -1;
    }
    string line;
    int y = 0;
    while (getline(groundCSV, line) && y < height) {
        stringstream ss(line);
        string tiledID;
        int x = 0;
        while (getline(ss, tiledID, ',') && x < width) {
            if (groundMap_.find(tiledID) != groundMap_.end()) {
                groundTiles_[y][x] = groundMap_.at(tiledID);
                cout << "Ground tile at x: " << x << " y: " << y << " is " << tiledID << " , or " << groundMap_.at(tiledID) << endl;
            } else {
                groundTiles_[y][x] = nullptr; // ID is not found, there is nothing at the tile
            }
            x++;
        }
        y++;
    }

    // Load building tiles from CSV
    ifstream bldgCSV("levels/level1_buildings.csv");
    if (!bldgCSV.is_open()) {
        cerr << "Failed to open building CSV file" << endl;
        return -1;
    }
    int y2 = 0;
    while (getline(bldgCSV, line) && y2 < height) {
        stringstream ss(line);
        string tiledID2;
        int x2 = 0;
        while (getline(ss, tiledID2, ',') && x2 < width) {
            if (buildingMap_.find(tiledID2) != buildingMap_.end()) {
                buildingTiles_[y2][x2] = buildingMap_.at(tiledID2);
                cout << "Building tile at x: " << x2 << " y: " << y2 << " is " << tiledID2 << " , or " << buildingMap_.at(tiledID2) << endl;
            } else {
                buildingTiles_[y2][x2] = nullptr; // ID is not found, there is nothing at the tile
            }
            x2++;
        }
        y2++;
    }

    return 0;
}

Terrain* World::getGroundTileAtPos(int y, int x) {
    if (groundTiles_[y][x] == nullptr) {
        return nullptr;
        //throw runtime_error("Attempted to access null ground tile");
    }
    return groundTiles_[y][x];
}

Terrain* World::getBuildingTileAtPos(int y, int x) {
    return buildingTiles_[y][x];
}

int World::loadTerrainTextures() {
    if (!groundTexture_.loadFromFile("assets/groundtiles.png")) {
        return -1;
    }
    if (!buildingTexture_.loadFromFile("assets/buildingsMergedHoriz.png")) {
        return -1;
    }

    return 0;
}

int World::loadCharacterTextures() {
    if (!groundTexture_.loadFromFile("assets/characters.png")) {
        return -1;
    }

    return 0;
}

int World::loadTerrainMap() {
    // TODO: Some terrain is only generated at certain levels
    // ground tiles
    groundMap_["-1"] = nullptr;
    groundMap_["4"] = new Terrain(64, 0, 16, 16, groundTexture_);
    groundMap_["46"] = new Terrain(64, 48, 16, 16, groundTexture_);
    groundMap_["88"] = new Terrain(64, 96, 16, 16, groundTexture_);
    groundMap_["10"] = new Terrain(160, 0, 16, 16, groundTexture_);
    groundMap_["172"] = new Terrain(64, 192, 16, 16, groundTexture_);
    groundMap_["255"] = new Terrain(48, 288, 16, 16, groundTexture_);
    groundMap_["130"] = new Terrain(64, 144, 16, 16, groundTexture_);
    groundMap_["297"] = new Terrain(48, 336, 16, 16, groundTexture_);

    // building tiles
    buildingMap_["-1"] = nullptr;
    buildingMap_["0"] = new Terrain(0, 0, 120, 167, buildingTexture_); // apartment
    buildingMap_["4"] = new Terrain(392, 0, 48, 48, buildingTexture_); // hot dog stand
    buildingMap_["8"] = new Terrain(864, 0, 64, 56, buildingTexture_); // small house
    buildingMap_["9"] = new Terrain(928, 0, 96, 88, buildingTexture_); // shop
    buildingMap_["10"] = new Terrain(1024, 0, 64, 48, buildingTexture_); // woodcutter house
    

    // Track all dynamically allocated terrains for deletion in the destructor
    for (const auto& pair : groundMap_) {
        if (pair.second != nullptr) {
            allTerrains_.push_back(pair.second);
        }
    }
    for (const auto& pair : buildingMap_) {
        if (pair.second != nullptr) {
            pair.second->getSprite().setOrigin(0.f, (pair.second->getTileSizeY())); 
            allTerrains_.push_back(pair.second);
        }
    }

    return 0;
}

int World::loadCharacters() {

    return 0;
}