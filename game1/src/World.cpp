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

int World::genTiles(int height, int width) {
    groundTiles_.resize(height);  // Resize outer vector to the desired height
    for (int i = 0; i < height; ++i) {
        groundTiles_[i].resize(width, nullptr);  // Resize inner vector to the desired width, initializing to nullptr
    }
    buildingTiles_.resize(height);
    for (int i = 0; i < height; ++i) {
        buildingTiles_[i].resize(width, nullptr);  // Resize inner vector to the desired width, initializing to nullptr
    }

    ifstream groundCSV("levels/level1_ground.csv");
    if (!groundCSV.is_open()) {
        cerr << "Failed to open CSV file" << endl;
        return -1;
    }

    string line;
    int y = 0;
    while (getline(groundCSV, line) && y < height) {
        stringstream ss(line);
        string tiledID;
        int x = 0;
        while (getline(ss, tiledID, ',') && x < width) {
            if (terrainMap_.find(tiledID) != terrainMap_.end()) {
                groundTiles_[y][x] = terrainMap_.at(tiledID);
                cout << "Ground tile at x: " << x << " y: " << y << " is " << tiledID << " , or " << terrainMap_.at(tiledID) << endl;
            } else {
                groundTiles_[y][x] = nullptr; // Handle case where ID is not found
            }
            x++;
        }
        y++;
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
    if (!groundTexture_.loadFromFile("assets/Tiles_FinalLayout.png")) {
        return -1;
    }
    if (!buildingTexture_.loadFromFile("assets/buildings1.png")) {
        return -1;
    }

    return 0;
}

int World::loadTerrainMap() {
    // TODO: Some terrain is only generated at certain levels
    // ground tiles
    terrainMap_["-1"] = nullptr;
    terrainMap_["4"] = new Terrain(64, 0, 16, 16, groundTexture_);
    terrainMap_["46"] = new Terrain(64, 48, 16, 16, groundTexture_);
    terrainMap_["88"] = new Terrain(64, 96, 16, 16, groundTexture_);
    terrainMap_["10"] = new Terrain(160, 0, 16, 16, groundTexture_);
    terrainMap_["172"] = new Terrain(64, 192, 16, 16, groundTexture_);
    terrainMap_["255"] = new Terrain(48, 255, 16, 16, groundTexture_);
    terrainMap_["130"] = new Terrain(64, 144, 16, 16, groundTexture_);
    terrainMap_["297"] = new Terrain(48, 336, 16, 16, groundTexture_);

    // building tiles

    // Track all dynamically allocated terrains for deletion in the destructor
    for (const auto& pair : terrainMap_) {
        if (pair.second != nullptr) {
            allTerrains_.push_back(pair.second);
        }
    }

    return 0;
}
