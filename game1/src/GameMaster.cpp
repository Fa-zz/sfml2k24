#include "GameMaster.hpp"

int GameMaster::loadTerrainTextures() {
    if (!groundTexture_.loadFromFile("assets/groundtiles.png")) {
        return -1;
    }
    return 0;
}

void GameMaster::initGame() {
    // world_ = new World();
    width_ = Data::worldWidth;
    height_ = Data::worldHeight;
    loadTerrainTextures();
    genTiles(height_, width_);
}

void GameMaster::genTiles(int height, int width) {
    groundTiles_.resize(height);  // Resize outer and inner vector
    for (int i = 0; i < height; ++i) {
        groundTiles_[i].resize(width, nullptr);
    }
    int tileMissionsFull[Data::numTileMissions] = {1, 1, 1, 1};

    for (int i = 0; i < groundTiles_.size(); i++) {
        for (int j = 0; j < groundTiles_[i].size(); j++) {

            int lb = 0, ub = Data::numTileType-1;
            int randNum = rand() % (ub - lb + 1) + lb;

            // Create a new Terrain object for each tile
            Terrain* newTile = nullptr;
            switch (randNum) {
                case 0: // apartment
                    newTile = new Terrain(64, 0, 16, 16, j, i, groundTexture_);
                    break;
                case 1: // church
                    newTile = new Terrain(64, 48, 16, 16, j, i, groundTexture_);
                    break;
                case 2: // park
                    newTile = new Terrain(64, 96, 16, 16, j, i, groundTexture_);
                    break;
                case 3: // school
                    newTile = new Terrain(160, 0, 16, 16, j, i, groundTexture_);
                    break;
                case 4: // restaurant
                    newTile = new Terrain(64, 192, 16, 16, j, i, groundTexture_);
                    break;
                case 5: // gas station
                    newTile = new Terrain(48, 288, 16, 16, j, i, groundTexture_);
                    break;
                case 6: // office
                    newTile = new Terrain(64, 144, 16, 16, j, i, groundTexture_);
                    break;
                case 7: // police HQ
                    newTile = new Terrain(48, 336, 16, 16, j, i, groundTexture_);
                    break;
                default:
                    newTile = new Terrain(64, 0, 16, 16, j, i, groundTexture_);
                    break;
            }

            newTile->setTileType(Data::tileTypes[randNum]);
            newTile->setTileStats(getRandomStatsArray());
            newTile->setTileMissions(tileMissionsFull);
            if (i == groundTiles_.size()/2 && j == groundTiles_[i].size()/2) {
                startingLoc_.x = j;
                startingLoc_.y = i;
                newTile->setTileStatus(Data::reclaimedTile);
            } else {
                newTile->setTileStatus(Data::undiscoveredTile);
            }

            groundTiles_[i][j] = newTile;

            // cout << "Tile type: " << newTile->getTileType() << endl;
            // cout << "Tile stats: " << newTile->getTileStats()[0] << " " << newTile->getTileStats()[1] << " " << newTile->getTileStats()[2] << endl;
            // cout << " " << endl;
        }
    }
    // Set the tiles immediately around starting tile to wild
    groundTiles_[startingLoc_.y][startingLoc_.x-1]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y, startingLoc_.x - 1));
    groundTiles_[startingLoc_.y-1][startingLoc_.x-1]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y - 1, startingLoc_.x - 1));
    groundTiles_[startingLoc_.y-1][startingLoc_.x]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y - 1, startingLoc_.x));
    groundTiles_[startingLoc_.y-1][startingLoc_.x+1]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y - 1, startingLoc_.x + 1));
    groundTiles_[startingLoc_.y][startingLoc_.x+1]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y, startingLoc_.x + 1));
    groundTiles_[startingLoc_.y+1][startingLoc_.x+1]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y + 1, startingLoc_.x + 1));
    groundTiles_[startingLoc_.y+1][startingLoc_.x]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y + 1, startingLoc_.x));
    groundTiles_[startingLoc_.y+1][startingLoc_.x-1]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y + 1, startingLoc_.x - 1));
}

void GameMaster::mapMode(int mapMode) {
    switch(mapMode) {
        case 0: // Default
            break;
        case 1: // Food map mode
            for (int i = 0; i < wildTilesCoords.size(); i++) {
                groundTiles_[wildTilesCoords[i].first][wildTilesCoords[i].second]->setTileStatStateColor(0);
            }
            break;
        case 2: // Zombies map mode
            for (int i = 0; i < wildTilesCoords.size(); i++) {
                groundTiles_[wildTilesCoords[i].first][wildTilesCoords[i].second]->setTileStatStateColor(1);
            }
            break;
        case 3: // Survivors map mode
            for (int i = 0; i < wildTilesCoords.size(); i++) {
                groundTiles_[wildTilesCoords[i].first][wildTilesCoords[i].second]->setTileStatStateColor(2);
            }
            break;

    }
}

// CONSTRUCTOR AND DESTRUCTOR
GameMaster::GameMaster(GUI& gui) : gui_(gui) { 

}

GameMaster::~GameMaster() { 
    for (int i = 0; i < groundTiles_.size(); i++) {
        for (int j = 0; j < groundTiles_[i].size(); j++) {
            delete groundTiles_[i][j];
        }
    }
}

Terrain& GameMaster::getGroundTileAtPos(int y, int x) {
    return *groundTiles_[y][x];
}

sf::Vector2u GameMaster::getStartingLoc() {
    return startingLoc_;
}

int* GameMaster::getRandomStatsArray() {
    int lb = 0, ub = Data::numTileStatStates-1;
    static int r[Data::numTileStats] = {0, 0, 0};
    for (int i = 0; i < Data::numTileStats; i++) {
        int randNum = rand() % (ub - lb + 1) + lb;
        // cout << "Random stats arr. RandNum: " << randNum << " at index i: " << i << endl;
        // cout << "Tile stat: " << Data::tileStats[i] << "Tile stat desc: " << Data::tileStatDescs[randNum] << endl;
        r[i] = randNum;
    }
    return r;
}
void GameMaster::addIntroInfobox() {
    if (gui_.getGUIStackEmpty()) {
        gui_.addIntroInfobox( getGroundTileAtPos(startingLoc_.y, startingLoc_.x).getTileType() );
    }
}

void GameMaster::addTileInfobox(float mouseX, float mouseY) {
    if (gui_.getGUIStackEmpty()) {
        gui_.addTileInfobox(
            getGroundTileAtPos(mouseY, mouseX).getTileStatus(),
            getGroundTileAtPos(mouseY, mouseX).getTileType(),
            getGroundTileAtPos(mouseY, mouseX).getTileStats(), 
            getGroundTileAtPos(mouseY, mouseX).getTileMissions()
        );
    }
}

void GameMaster::infoboxMaster(float mouseX, float mouseY, bool clicked, bool scrollDown, bool scrollUp) {
    linkData_ = gui_.getClickData();
    if (linkData_ == Data::onClickClose) {
        gui_.popCurrentState();    
    } else if (linkData_ == Data::onClickCreateMissionChoice) {
        gui_.addInfobox(Data::missionChoice);
    }
    linkData_ = "";
    gui_.passInput(mouseX, mouseY, clicked, scrollDown, scrollUp);
}

void GameMaster::popCurrentInfobox() { gui_.popCurrentState(); }

// sf::Vector2u GameMaster::getPlayerPos() { return world_->getStartingLoc(); }

int GameMaster::getPopulation() {
    return 7;
}