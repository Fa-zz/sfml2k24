#include "World.hpp"
#include "Terrain.hpp"

World::World() {
    loadTerrainTextures();
    Terrain* grass1 = new Terrain(64, 0, 16, 16, groundTexture_);
    Terrain* grass2 = new Terrain(88, 0, 16, 16, groundTexture_);
    allTerrains_.push_back(grass1);
    allTerrains_.push_back(grass2);

    Terrain* house1 = new Terrain(0, 0, 65, 56, buildingTexture_);
    allTerrains_.push_back(house1);
}

World::~World() {
    for (Terrain* terrain : allTerrains_) {
        delete terrain;
    }
}

// TODO: genTiles should pull from csv files located in ./levels , not generate world itself !
void World::genTiles(int height, int width) {
    groundTiles_.resize(height);  // Resize outer vector to the desired height
    for (int i = 0; i < height; ++i) {
        groundTiles_[i].resize(width, nullptr);  // Resize inner vector to the desired width, initializing to nullptr
    }
    buildingTiles_.resize(height);
    for (int i = 0; i < height; ++i) {
        buildingTiles_[i].resize(width, nullptr);  // Resize inner vector to the desired width, initializing to nullptr
    }

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            groundTiles_[i][j] = allTerrains_[0];
        }
    }
    buildingTiles_[15][25] = allTerrains_[2];
}

Terrain& World::getGroundTileAtPos(int y, int x) {
    return *groundTiles_[y][x];
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
