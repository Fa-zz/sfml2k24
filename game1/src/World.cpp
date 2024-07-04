#include "World.hpp"
#include "Terrain.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

World::World() {
    srand(static_cast<unsigned int>(time(0)));
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
        groundTiles_[i].resize(width, nullptr);
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
                if (groundTiles_[y][x] != nullptr) {
                    groundTiles_[y][x]->setDummyInfo(rand() % 100 + 1);
                }
                //cout << "Ground tile at x: " << x << " y: " << y << " is " << tiledID << " , or " << groundMap_.at(tiledID) << endl;
            } else {
                groundTiles_[y][x] = nullptr; // ID is not found, there is nothing at the tile
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
    if (!groundTexture_.loadFromFile("assets/groundtiles.png")) {
        return -1;
    }
    return 0;
}

int World::loadTerrainMap() {
    // Ground tiles initialization
    groundMap_["-1"] = nullptr;
    groundMap_["4"] = new Terrain(64, 0, 16, 16, groundTexture_);
    groundMap_["46"] = new Terrain(64, 48, 16, 16, groundTexture_);
    groundMap_["88"] = new Terrain(64, 96, 16, 16, groundTexture_);
    groundMap_["10"] = new Terrain(160, 0, 16, 16, groundTexture_);
    groundMap_["172"] = new Terrain(64, 192, 16, 16, groundTexture_);
    groundMap_["255"] = new Terrain(48, 288, 16, 16, groundTexture_);
    groundMap_["130"] = new Terrain(64, 144, 16, 16, groundTexture_);
    groundMap_["297"] = new Terrain(48, 336, 16, 16, groundTexture_);

    // Track all dynamically allocated terrains for deletion in the destructor
    for (const auto& pair : groundMap_) {
        if (pair.second != nullptr) {
            allTerrains_.push_back(pair.second);
        }
    }
    return 0;
}
