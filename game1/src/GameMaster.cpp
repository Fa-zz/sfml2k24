#include "GameMaster.hpp"

int GameMaster::loadTerrainTextures() {
    if (!groundTexture_.loadFromFile(Data::groundTexturePath)) {
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
    initPeople();
}

void GameMaster::initPeople() {
    // Getting male names from .txt file
    ifstream mNameInputFile(Data::mNamesPath); 
    if (!mNameInputFile.is_open()) { 
        cerr << "Error opening the male names file!" << endl; 
    } 
    string maleLine;
    while (getline(mNameInputFile, maleLine)) { 
        maleNames_.push_back(maleLine);
    }
    mNameInputFile.close();

    // Getting female names from .txt file
    ifstream fNameInputFile(Data::fNamesPath);
    if (!fNameInputFile.is_open()) { 
        cerr << "Error opening the female names file!" << endl; 
    }
    string femaleLine;
    while (getline(fNameInputFile, femaleLine)) {
        femaleNames_.push_back(femaleLine);
    }
    fNameInputFile.close();

    // Randomly generating starting 7 citizens
    for (int i = 0; i < 6; i++) {
        int randJob = Data::getRandNum(0, Data::numJobs-1);
        int randSex = Data::getRandNum(0, 1);
        // pulling from men names if sex == 1, pulling from women names if sex == 0
        cout << "GM.cpp, randSex = " << randSex << endl;
        if (randSex == 1) { 
            int randName = Data::getRandNum(0, maleNames_.size()-1);
            personMap_[lastID_] = new Person(lastID_, maleNames_[randName], Data::jobs[randJob]);
        } else if (randSex == 0) {
            int randName = Data::getRandNum(0, femaleNames_.size()-1);
            personMap_[lastID_] = new Person(lastID_, femaleNames_[randName], Data::jobs[randJob]);
        } else {
            int randName = Data::getRandNum(0, femaleNames_.size()-1);
            personMap_[lastID_] = new Person(lastID_, femaleNames_[randName], Data::jobs[randJob]);
        }
        personMap_[lastID_]->print();
        lastID_ += 1;
    }

    gui_.setPersonCount(lastID_+1);
}

void GameMaster::genTiles(int height, int width) {
    groundTiles_.resize(height);  // Resize outer and inner vector
    for (int i = 0; i < height; ++i) {
        groundTiles_[i].resize(width, nullptr);
    }
    int tileMissionsUnd[Data::numTileMissions] = {1, 0, 0, 0};

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
            newTile->setTileMissions(tileMissionsUnd);
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
    // Set the tiles immediately around starting tile to wild, and record each tiles' coord
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

    int arr1[4] = {0,1,1,1};
    int arr2[4] = {0,1,1,0};
    for (int i = 0; i < wildTilesCoords.size(); i++) {
        if (groundTiles_[wildTilesCoords[i].first][wildTilesCoords[i].second]->getTileStats()[1] == 0) {
            groundTiles_[wildTilesCoords[i].first][wildTilesCoords[i].second]->setTileMissions(arr1);
        } else {
            groundTiles_[wildTilesCoords[i].first][wildTilesCoords[i].second]->setTileMissions(arr2);
        }

    }
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
GameMaster::GameMaster(GUI& gui) : gui_(gui), gmcontext_(std::make_shared<GMContext>()) { 
    charSize_ = gui_.getCharSize();
    font_ = gui_.getFont();
}

GameMaster::~GameMaster() { 
    for (int i = 0; i < groundTiles_.size(); i++) {
        for (int j = 0; j < groundTiles_[i].size(); j++) {
            delete groundTiles_[i][j];
        }
    }
    for (auto& pair : personMap_) {
        delete pair.second;
    }
    personMap_.clear();
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
// void GameMaster::addIntroInfobox() {
//     // // Add an intro infobox and pass in the starting tile type, then create it
//     // if (gmcontext_->stateMachine_->IsEmpty()) {
//     //     addInfobox(Data::intro);
//     //     passTileType( getGroundTileAtPos(startingLoc_.y, startingLoc_.x).getTileType() );
//     //     // gui_.addIntroInfobox( getGroundTileAtPos(startingLoc_.y, startingLoc_.x).getTileType() );
//     // }
//     // createInfobox();
// }

// void GameMaster::addTileInfobox(float mouseX, float mouseY, string status, bool create) {
//     currX_ = mouseX;
//     currY_ = mouseY;
//     // string status = getGroundTileAtPos(currY_, currX_).getTileStatus();
//     gmcontext_->stateMachine_->Add(std::make_unique<Infobox>(
//         charSize_, font_, windowSize_.x, windowSize_.y,
//         status,
//         getGroundTileAtPos(currY_, currX_).getTileType(),
//         getGroundTileAtPos(currY_, currX_).getTileStats(), 
//         getGroundTileAtPos(currY_, currX_).getTileMissions())
//     );
//     if (create)
//         createInfobox();
// }

void GameMaster::addInfobox(float mouseX, float mouseY, string status, bool create) {
    // Add an intro infobox and pass in the starting tile type, then create it
    if (status == Data::intro) {
        if (gmcontext_->stateMachine_->IsEmpty()) {
            gmcontext_->stateMachine_->Add(std::make_unique<Infobox>(charSize_, font_, windowSize_.x, windowSize_.y, status), false);
            gmcontext_->stateMachine_->ProcessStateChange();
            passTileType( getGroundTileAtPos(startingLoc_.y, startingLoc_.x).getTileType() );
            // gui_.addIntroInfobox( getGroundTileAtPos(startingLoc_.y, startingLoc_.x).getTileType() );
        }
    } else if ( status != Data::missionChoice ) {
        currX_ = mouseX;
        currY_ = mouseY;
        gmcontext_->stateMachine_->Add(std::make_unique<Infobox>(
            charSize_, font_, windowSize_.x, windowSize_.y,
            getGroundTileAtPos(currY_, currX_).getTileStatus(),
            getGroundTileAtPos(currY_, currX_).getTileType(),
            getGroundTileAtPos(currY_, currX_).getTileStats(), 
            getGroundTileAtPos(currY_, currX_).getTileMissions()));
        gmcontext_->stateMachine_->ProcessStateChange();
    } else if (status == Data::missionChoice) {
        currX_ = mouseX;
        currY_ = mouseY;
        // string status = getGroundTileAtPos(currY_, currX_).getTileStatus();
        gmcontext_->stateMachine_->Add(std::make_unique<Infobox>(
            charSize_, font_, windowSize_.x, windowSize_.y,
            status,
            getGroundTileAtPos(currY_, currX_).getTileType(),
            getGroundTileAtPos(currY_, currX_).getTileStats(), 
            getGroundTileAtPos(currY_, currX_).getTileMissions()));
        gmcontext_->stateMachine_->ProcessStateChange();
    }
    createInfobox();
}

void GameMaster::updateInfobox(float mouseX, float mouseY, bool clicked, bool scrollDown, bool scrollUp) {
    if (gmcontext_->stateMachine_->IsEmpty())   // if there's nothing in the stateMan, return
        return;

    linkData_ = gmcontext_->stateMachine_->GetCurrent()->getData();
    if (linkData_ == Data::onClickClose) {
        popCurrentInfobox();
        return;  
    } else if (linkData_ == Data::onClickCreateMissionChoice) {
        addInfobox(currX_, currY_, Data::missionChoice, true);
    } else if (linkData_ == Data::onClickCreatePersonChoice) {
        addInfobox(currX_, currY_, Data::personChoice, true);
    }
    linkData_ = "";
    passInput(mouseX, mouseY, clicked, scrollDown, scrollUp);
}

bool GameMaster::getInfoboxStackEmpty() { return gmcontext_->stateMachine_->IsEmpty(); }

void GameMaster::popCurrentInfobox() {
    gui_.popInfobox();
    gmcontext_->stateMachine_->PopCurrent();
    gmcontext_->stateMachine_->ProcessStateChange();
}

Infobox* GameMaster::getCurrentInfobox() {
    auto currentState = gmcontext_->stateMachine_->GetCurrent();
    if (currentState) {
        if (Infobox* infoboxState = dynamic_cast<Infobox*>(currentState)) {
            return infoboxState;
        } else {
            std::cerr << "Current state is not an Infobox" << std::endl;
        }
    } else {
        std::cerr << "No current state" << std::endl;
    }
}

void GameMaster::createInfobox() {
    // gmcontext_->stateMachine_->ProcessStateChange(); // stateMan needs to process state change (i.e. push new state onto stack) b4 creating Ibox
    Infobox* currInfobox = getCurrentInfobox();
    currInfobox->createInfobox();
    gui_.pushInfobox(currInfobox);
}

void GameMaster::passTileType(string type) {
    Infobox* currInfobox = getCurrentInfobox();
    currInfobox->setLoc(type);
}

void GameMaster::passInput(float x, float y, bool clicked, bool scrollDown, bool scrollUp) {
    gmcontext_->stateMachine_->GetCurrent()->handleInput(x, y, clicked, scrollDown, scrollUp);
}

// sf::Vector2u GameMaster::getPlayerPos() { return world_->getStartingLoc(); }

int GameMaster::getPopulation() {
    return 7;
}

void GameMaster::setWindowSize(sf::Vector2u windowSize) { windowSize_ = sf::Vector2u{windowSize.x, windowSize.y}; }