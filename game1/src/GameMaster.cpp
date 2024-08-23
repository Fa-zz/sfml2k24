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

    // Randomly generating starting citizens (by default, 7)
    for (int i = 0; i < Data::startingPopNum; i++) {
        // int randJob = Data::getRandNum(0, Data::numJobs-1);
        int job;
        switch (i) {
            case 0:
                job = 0;
                break;
            case 1:
                job = 2;
                break;
            case 2:
                job = 2;
                break;
            case 3:
                job = 3;
                break;
            case 4:
                job = 1;
                break;
            case 5:
                job = 1;
                break;
            case 6:
                job = 1;
                break;
            default:
                job = Data::getRandNum(0, Data::numJobs-1);
                break;
        }

        int randSex = Data::getRandNum(0, 1);
        // pulling from men names if sex == 1, pulling from women names if sex == 0
        cout << "GM.cpp, randSex = " << randSex << endl;
        if (randSex == 1) { 
            int randName = Data::getRandNum(0, maleNames_.size()-1);
            people_.emplace_back(lastID_, maleNames_[randName], Data::jobs[job]);
            // personMap_[lastID_] = new Person(lastID_, maleNames_[randName], Data::jobs[job]);
        } else if (randSex == 0) {
            int randName = Data::getRandNum(0, femaleNames_.size()-1);
            people_.emplace_back(lastID_, femaleNames_[randName], Data::jobs[job]);
        } else {
            int randName = Data::getRandNum(0, femaleNames_.size()-1);
            people_.emplace_back(lastID_, femaleNames_[randName], Data::jobs[job]);
        }
        people_[lastID_].print();
        // personMap_[lastID_]->print();
        lastID_ += 1;
    }
    gui_.setPopNum(lastID_);
}

void GameMaster::genTiles(int height, int width) {
    worldTiles_.resize(height);  // Resize outer and inner vector
    for (int i = 0; i < height; ++i) {
        worldTiles_[i].resize(width, nullptr);
    }
    int tileMissionsUnd[Data::numTileMissions] = {1, 0, 0, 0};

    for (int i = 0; i < worldTiles_.size(); i++) {
        for (int j = 0; j < worldTiles_[i].size(); j++) {

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

            // every tile starts out undiscovered, with a random type and stats
            newTile->setTileType(Data::tileTypes[randNum]);
            newTile->setTileStats(getRandomStatsArray());
            newTile->setTileMissionsArr(tileMissionsUnd);
            // setting start location
            if (i == worldTiles_.size()/2 && j == worldTiles_[i].size()/2) {
                startingLoc_.x = j;
                startingLoc_.y = i;
                newTile->setTileStatus(Data::reclaimedTile);
            } else {
                newTile->setTileStatus(Data::undiscoveredTile);
            }

            worldTiles_[i][j] = newTile;

            // cout << "Tile type: " << newTile->getTileType() << endl;
            // cout << "Tile stats: " << newTile->getTileStats()[0] << " " << newTile->getTileStats()[1] << " " << newTile->getTileStats()[2] << endl;
            // cout << " " << endl;
        }
    }
    // Set the tiles immediately around starting tile to wild, and record each tiles' coord
    worldTiles_[startingLoc_.y][startingLoc_.x-1]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y, startingLoc_.x - 1));
    worldTiles_[startingLoc_.y-1][startingLoc_.x-1]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y - 1, startingLoc_.x - 1));
    worldTiles_[startingLoc_.y-1][startingLoc_.x]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y - 1, startingLoc_.x));
    worldTiles_[startingLoc_.y-1][startingLoc_.x+1]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y - 1, startingLoc_.x + 1));
    worldTiles_[startingLoc_.y][startingLoc_.x+1]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y, startingLoc_.x + 1));
    worldTiles_[startingLoc_.y+1][startingLoc_.x+1]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y + 1, startingLoc_.x + 1));
    worldTiles_[startingLoc_.y+1][startingLoc_.x]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y + 1, startingLoc_.x));
    worldTiles_[startingLoc_.y+1][startingLoc_.x-1]->setTileStatus(Data::wildTile);
    wildTilesCoords.push_back(make_pair(startingLoc_.y + 1, startingLoc_.x - 1));

    // For every widl tile, we update its missions 
    for (int i = 0 ; i < wildTilesCoords.size(); i++) {
        updateTileMissions(wildTilesCoords[i].first, wildTilesCoords[i].second);
    }
    // int arr1[4] = {0,1,1,1};
    // int arr2[4] = {0,1,1,0};
    // for (int i = 0; i < wildTilesCoords.size(); i++) {
    //     if (worldTiles_[wildTilesCoords[i].first][wildTilesCoords[i].second]->getTileStats()[1] == 0) {
    //         worldTiles_[wildTilesCoords[i].first][wildTilesCoords[i].second]->setTileMissions(arr1);
    //     } else {
    //         worldTiles_[wildTilesCoords[i].first][wildTilesCoords[i].second]->setTileMissions(arr2);
    //     }

    // }
}

void GameMaster::mapMode(int mapMode) {
    switch(mapMode) {
        case 0: // Default
            break;
        case 1: // Food map mode
            for (int i = 0; i < wildTilesCoords.size(); i++) {
                worldTiles_[wildTilesCoords[i].first][wildTilesCoords[i].second]->setTileStatStateColor(0);
            }
            break;
        case 2: // Zombies map mode
            for (int i = 0; i < wildTilesCoords.size(); i++) {
                worldTiles_[wildTilesCoords[i].first][wildTilesCoords[i].second]->setTileStatStateColor(1);
            }
            break;
        case 3: // Survivors map mode
            for (int i = 0; i < wildTilesCoords.size(); i++) {
                worldTiles_[wildTilesCoords[i].first][wildTilesCoords[i].second]->setTileStatStateColor(2);
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
    for (int i = 0; i < worldTiles_.size(); i++) {
        for (int j = 0; j < worldTiles_[i].size(); j++) {
            delete worldTiles_[i][j];
        }
    }
    // for (auto& pair : personMap_) {
    //     delete pair.second;
    // }
    // personMap_.clear();
}

Terrain& GameMaster::getGroundTileAtPos(int y, int x) {
    return *worldTiles_[y][x];
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

void GameMaster::addInfobox(float mouseX, float mouseY, string status, bool create) {
    // Add an intro infobox and pass in the starting tile type, then create it
    if (status == Data::intro) {
        if (gmcontext_->stateMachine_->IsEmpty()) {
            gmcontext_->stateMachine_->Add(std::make_unique<Infobox>(charSize_, font_, windowSize_.x, windowSize_.y, status), false);
            gmcontext_->stateMachine_->ProcessStateChange();
            passTileType( getGroundTileAtPos(startingLoc_.y, startingLoc_.x).getTileType() );
            // gui_.addIntroInfobox( getGroundTileAtPos(startingLoc_.y, startingLoc_.x).getTileType() );
        }
    // If creating an Infobox of a wild, active, reclaimed, or undiscovered tile
    } else if ( status == Data::wildTile || status == Data::reclaimedTile || status == Data::undiscoveredTile ) {
        currX_ = mouseX;
        currY_ = mouseY;
        gmcontext_->stateMachine_->Add(std::make_unique<Infobox>(
            charSize_, font_, windowSize_.x, windowSize_.y,
            getGroundTileAtPos(currY_, currX_).getTileStatus(),
            getGroundTileAtPos(currY_, currX_).getTileType(),
            getGroundTileAtPos(currY_, currX_).getTileStats(), 
            getGroundTileAtPos(currY_, currX_).getTileMissions()));
        gmcontext_->stateMachine_->ProcessStateChange();

    // If creating an Infobox for selecting a mission at a tile
    } else if (status == Data::missionChoice) {
        gmcontext_->stateMachine_->Add(std::make_unique<Infobox>(
            charSize_, font_, windowSize_.x, windowSize_.y,
            status,
            getGroundTileAtPos(currY_, currX_).getTileType(),
            getGroundTileAtPos(currY_, currX_).getTileStats(), 
            getGroundTileAtPos(currY_, currX_).getTileMissions()));
        gmcontext_->stateMachine_->ProcessStateChange();

    // If creating an Infobox for selecting a people to undertake a mission
    } else if (status == Data::personChoice || status == Data::activeTile) {
        gmcontext_->stateMachine_->Add(std::make_unique<Infobox>(
            charSize_, font_, windowSize_.x, windowSize_.y,
            status));
        gmcontext_->stateMachine_->ProcessStateChange();
        if (status == Data::personChoice) {
            passMissionInfo(); // passing mission name, danger, and days to take
            passPeopleString(); // pass the list of people sorted by the mission type
        } 
        // else if (status == Data::activeTile) {
            
        //     for (int i = 0; i < activeMissions_.size(); i++) {
        //         if (activeMissions_[i].missionY == currY_ && activeMissions_[i].missionX == currX_) {
        //             passMissionInfoDirect(
        //                 activeMissions_[i].missionObjective,
        //                 activeMissions_[i].danger,
        //                 activeMissions_[i].daysToTake
        //             );
        //         }
        //         break;
        //     }
        // }
    }
    createInfobox();
}

void GameMaster::updateInfobox(float mouseX, float mouseY, vector<string> linkData, bool clicked, bool scrollDown, bool scrollUp) {
    if (gmcontext_->stateMachine_->IsEmpty())   // if there's nothing in the stateMan, return
        return;

    // if linkData_ is == placeholder from the GameScreen, we'll check the infobox and use that linkData
    if (linkData[0] == "placeholder")
        linkData_ = gmcontext_->stateMachine_->GetCurrent()->getData();
    else
        linkData_ = linkData;

    if (linkData_.size() > 0) {
        if (linkData_[0] != "placeholder") {
            cout << "linkData_: " << linkData_[0];
            cout << linkData_[1] << endl;
        }
    }
    if (!(linkData_.empty())) {
        // User closes the current open infobox
        if (linkData_[0] == Data::onClickClose) {
            // Handling case where we are on choosing people screen, if we close that infobox we want to clear local data and signify that we are no longer on that screen
            if (choosingPeople_) {
                if (currSelected_.size() > 0)
                    currSelected_.clear();
                choosingPeople_ = false;
                currMission_ = "";
            }
            popCurrentInfobox();
            return;
        // User clicks on a link to see mission choices for a tile
        } else if (linkData_[0] == Data::onClickCreateMissionChoice) {
            addInfobox(currX_, currY_, Data::missionChoice, true);
        // User clicks on a link to select people for a selected mission.
        } else if (linkData_[0] == Data::onClickCreatePersonChoice) {
            currMission_ = linkData_[1];
            choosingPeople_ = true;
            addInfobox(currX_, currY_, Data::personChoice, true);
        // User selects/deselects people for a selected mission
        } else if (linkData_[0] == Data::onClickSelect && choosingPeople_ == true) {
            selectedIndex_ = stoi(linkData_[1]); // This is the index of the selected person in people_. (Indexes can change depending on how the vector is sorted given different missions)
            selectedID_ = people_[selectedIndex_].getID(); // This is the ID of the selected person (Unique for each person object)
            // cout << " User has chosen person at index " << personIndex << " corresponding to ";
            // people_[personIndex].print();

            // Finds the occurrence of of the ID appearing in currSelected_. If it's there the person must be erased from currSelected_. Else, add them to currSelected_
            vector<int>::iterator position = find(currSelected_.begin(), currSelected_.end(), selectedID_);
            if (position != currSelected_.end()) {  // element was found
                currSelected_.erase(position);
            } else if (position == currSelected_.end()) { // == myVector.end() means the element was not found
                currSelected_.push_back(selectedID_);
            }
            // Re calculate danger and days to take
            passMissionInfo();
        // User accepts mission, after choosing people. Mission is created, tile becomes an active tile, and stack is cleared.
        } else if (linkData_[0] == Data::onClickAccept && choosingPeople_ == true && currSelected_.size() > 0) {
            // Mission *newMission = new Mission(currMission_, currSelected_, currY_, currX_);
            activeMissions_.emplace_back(currMission_, currSelected_, currY_, currX_, strDanger_, strDays_);
            for (int i = 0; i < currSelected_.size(); i++) {
                IDtoPerson(currSelected_[i])->setBusy(true);
            }
            currMission_ = "";
            currSelected_.clear();
            choosingPeople_ = false;
            worldTiles_[currY_][currX_]->setTileStatus(Data::activeTile);
            popAllInfoboxes();
        }
        linkData_.clear();
    }
    passInput(mouseX, mouseY, clicked, scrollDown, scrollUp);
}

bool GameMaster::getInfoboxStackEmpty() { return gmcontext_->stateMachine_->IsEmpty(); }

void GameMaster::popCurrentInfobox() {
    gui_.popInfobox(); // delete reference in gui
    gmcontext_->stateMachine_->PopCurrent(); // tell stateman to pop current
    gmcontext_->stateMachine_->ProcessStateChange(); // process the state change
}

void GameMaster::popAllInfoboxes() {
    gui_.popAllInfobox(); // del all references in gui
    gmcontext_->stateMachine_->PopAll(); // tell stateman to pop all
    gmcontext_->stateMachine_->ProcessStateChange(); // process state change
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

// Takes a wildtileCoord index as argument. Certain missions are only available if there is data at the 
// Cannot scout area (Data::tileMissionsText[0]) if tile is wildTile or reclaimedTile
// Cannot scavenge for food (Data::tileMissionsText[1]) if getTileStats()[0] == 0
// Cannot kill zombies (Data::tileMissionsText[2]) if getTileStats()[1] == 0
// Cannot recruit survivors (Data::tileMissionsText[3]) if getTileStats()[2] == 0
// Cannot reclaim (Data::tileMissionsText[4]) if getTileStats()[1] > 0 AND if tile is undiscoveredTile
void GameMaster::updateTileMissions(int y, int x) {
    auto tile = worldTiles_[y][x];
    auto tileStatus = tile->getTileStatus();

    if (tileStatus == Data::reclaimedTile) {
        for (int i = 0; i < Data::numTileMissions; i++) {
            tile->setTileMissionsInt(i, false);
        }
        return;
    }

    if (tileStatus == Data::wildTile) {
        tile->setTileMissionsInt(0, false);

        // List of mission conditions based on tile stats
        std::vector<std::pair<int, bool>> missionConditions = {
            {1, tile->getTileStats()[0] != 0},  // Food present for scavenge mission
            {2, tile->getTileStats()[1] != 0},  // Zombies present for kill mission
            {3, tile->getTileStats()[2] != 0},  // Survivors present for recruit mission
            {4, tile->getTileStats()[1] == 0}   // No zombies for reclaim mission
        };

        // Apply the conditions
        for (const auto& [missionIndex, condition] : missionConditions) {
            tile->setTileMissionsInt(missionIndex, condition);
        }
    }
}

void GameMaster::passTileType(string type) {
    Infobox* currInfobox = getCurrentInfobox();
    currInfobox->setLoc(type);
}

int GameMaster::calcDanger() {
    if (getGroundTileAtPos(currY_, currX_).getTileStats()[1] != 0) {
        return 100;
    } else {
        return 0;
    }
}

int GameMaster::calcDangerDecRate() {
    int zombieStat = getGroundTileAtPos(currY_, currX_).getTileStats()[1];
    int end = Data::numTileStatStates;
    if (zombieStat == 0) {
        return 100;
    } else if (zombieStat == 1) {
        return 100;
    } else if (zombieStat == 2) {
        return 50;
    } else if (zombieStat == 3) {
        return 25;
    }
}

void GameMaster::passMissionInfo() {
    Infobox* currInfobox = getCurrentInfobox();
    string mission = currMission_;
    string strDanger_ = to_string( calcDanger() ); 
    string strDays_ = to_string( DAYS_TO_TAKE_ );

    // If people are selected, we need to iterate over the selected and using their job calculate the new danger and days to take.
    if (currSelected_.size() > 0) {
        int calcdDays = DAYS_TO_TAKE_;
        int subtractDay = 0;
        int calcdDanger = stoi(strDanger_);
        int factor = calcDangerDecRate();
        for (int i = 0; i < currSelected_.size(); i++) {
            std::__1::__wrap_iter<Person *> person = IDtoPerson(currSelected_[i]);
            // Calculate the decrease in danger. Soldiers decrease danger by complete factor, non soldiers decrease danger by 1/2 factor
            if (person->getJob() == Data::jobSoldier) {
                calcdDanger -= factor;
            } else {
                calcdDanger -= (factor/2);
            }

            // In the same loop we calculate factor of decreasing days. Person with priorJob will decrease day by 1. It takes 2 persons without to decrease day by 1.
            if (person->getJob() == priorityJob_) {
                calcdDays -= 1;
            } else {
                if (subtractDay == 1) {
                    calcdDays -= 1;
                    subtractDay = 0;
                } else {
                    subtractDay += 1;
                }
            }
        }
        if (calcdDanger < 0)
            calcdDanger = 0;
        if (calcdDays < 1)
            calcdDays = 1;
        strDanger_ = to_string( calcdDanger );
        strDays_ = to_string ( calcdDays );
    }

    currInfobox->setMissionInfo(mission, strDanger_, strDays_);
}

void GameMaster::passMissionInfoDirect(string mission, string danger, string days) {
    Infobox* currInfobox = getCurrentInfobox();
    currInfobox->setMissionInfo(mission, danger, days);
}

// void GameMaster::passMission(string mission) {
//     Infobox* currInfobox = getCurrentInfobox();
//     currInfobox->setMission(mission);
// }

// Custom comparator for sorting by specific job priority
bool GameMaster::customJobComparator(Person& p1, Person& p2, std::string& priorityJob) {
    if (p1.getJob() == priorityJob && p2.getJob() != priorityJob) {
        return true;
    }
    if (p2.getJob() == priorityJob && p1.getJob() != priorityJob) {
        return false;
    }
    return p1.getName() < p2.getName();  // Alphabetical sort if jobs are the same or neither is the priority job
}

void GameMaster::passPeopleString() {
    string peopleString;
    // // Depending on the mission, people needs to be sorted 
    // If scout mission, prior job is survivor
    if (currMission_ == Data::tileMissionsText[0]) {
        priorityJob_ = Data::jobSurvivor;
    // If scavenge mission, prior job is scavenger
    } else if (currMission_ == Data::tileMissionsText[1]) {
        priorityJob_ = Data::jobScavenger;
    // If kill zombies mission, prior job is soldier
    } else if (currMission_ == Data::tileMissionsText[2]) {
        priorityJob_ = Data::jobSoldier;
    // If recruit survivors mission, prior job is leader
    } else if (currMission_ == Data::tileMissionsText[3]) {
        priorityJob_ = Data::jobLeader;
    // If rebuild mission, prior job is builder
    } else if (currMission_ == Data::tileMissionsText[4]) {
        priorityJob_ = Data::jobBuilder;
    }
    // cout << "Priority job is : " << priorityJob_ << " for curr mission: " << currMission_ << endl;

    sort(people_.begin(), people_.end(), 
              [this](Person& p1, Person& p2) {
                  return customJobComparator(p1, p2, priorityJob_);
              });
    // sort(people_.begin(), people_.end(), priorityJob);

    // Display sorted people
    // cout << "Displaying sorted people" << endl;
    // for (const auto& person : people_) {
    //     person.print();
    // }

    for (int i = 0; i < people_.size(); i++) {
        // 20. Muhammad, Soldier
        peopleString += to_string(i+1) + ". " + people_[i].getName() + ", " + people_[i].getJob();
        if (people_[i].getBusy() == true) {
            peopleString += "!";
        }
        peopleString +=  + "\n";
    }
    Infobox* currInfobox = getCurrentInfobox();
    currInfobox->setPopulation(peopleString);
}

void GameMaster::passInput(float x, float y, bool clicked, bool scrollDown, bool scrollUp) {
    if (!(gmcontext_->stateMachine_->IsEmpty()))
        gmcontext_->stateMachine_->GetCurrent()->setInput(x, y, clicked, scrollDown, scrollUp);
}

// sf::Vector2u GameMaster::getPlayerPos() { return world_->getStartingLoc(); }

int GameMaster::getPopulationNum() {
    return 7;
}

std::__1::__wrap_iter<Person *> GameMaster::IDtoPerson(int targetID) {
    auto it = std::find_if(people_.begin(), people_.end(), 
                           [targetID](Person& person) { return person.getID() == targetID; });

    if (it != people_.end()) {
        return it;
    }
}

void GameMaster::setWindowSize(sf::Vector2u windowSize) { windowSize_ = sf::Vector2u{windowSize.x, windowSize.y}; }