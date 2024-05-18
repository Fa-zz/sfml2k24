#include "World.hpp"

#include "World.hpp"
#include "Terrain.hpp"

World::World() {
    loadTerrainTextures();
    Terrain* grass1 = new Terrain(64, 0, 16, overworldTexture_);
    Terrain* grass2 = new Terrain(88, 0, 16, overworldTexture_);
    allTerrains_.push_back(grass1);
    allTerrains_.push_back(grass2);
}

World::~World() {
    for (Terrain* terrain : allTerrains_) {
        delete terrain;
    }
}

void World::genTiles(int height, int width) {
    tiles_.resize(height);  // Resize outer vector to the desired height
    for (int i = 0; i < height; ++i) {
        tiles_[i].resize(width, nullptr);  // Resize inner vector to the desired width, initializing to nullptr
    }

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            tiles_[i][j] = allTerrains_[0];
        }
    }
}

Terrain& World::getTile(int y, int x) {
    return *tiles_[y][x];
}

int World::loadTerrainTextures() {
    if (!overworldTexture_.loadFromFile("assets/Tiles_FinalLayout.png")) {
        return -1;
    }
    return 0;
}
