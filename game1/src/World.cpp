// #include "World.hpp"
// #include "Terrain.hpp"
// #include <iostream>
// #include <fstream>
// #include <string>
// #include <sstream>
// using namespace std;

// // CONSTRUCTOR AND DESTRUCTOR 
// World::World() {
//     if (loadTerrainTextures() != 0)
//         cerr << "Failed to load terrain textures" << endl;
// }

// World::~World() {
//     for (int i = 0; i < groundTiles_.size(); i++) {
//         for (int j = 0; j < groundTiles_[i].size(); j++) {
//             delete groundTiles_[i][j];
//         }
//     }
// }

// int World::genTiles(int height, int width) {
//     worldHeight_=height;
//     worldWidth_=width;
//     groundTiles_.resize(height);  // Resize outer vector to the desired height
//     for (int i = 0; i < height; ++i) {
//         groundTiles_[i].resize(width, nullptr);
//     }
//     int tileMissionsFull[Data::numTileMissions] = {1, 1, 1, 1};

//     for (int i = 0; i < groundTiles_.size(); i++) {
//         for (int j = 0; j < groundTiles_[i].size(); j++) {

//             int lb = 0, ub = Data::numTileType-1;
//             int randNum = rand() % (ub - lb + 1) + lb;

//             // Create a new Terrain object for each tile
//             Terrain* newTile = nullptr;
//             switch (randNum) {
//                 case 0: // apartment
//                     newTile = new Terrain(64, 0, 16, 16, j, i, groundTexture_);
//                     break;
//                 case 1: // church
//                     newTile = new Terrain(64, 48, 16, 16, j, i, groundTexture_);
//                     break;
//                 case 2: // park
//                     newTile = new Terrain(64, 96, 16, 16, j, i, groundTexture_);
//                     break;
//                 case 3: // school
//                     newTile = new Terrain(160, 0, 16, 16, j, i, groundTexture_);
//                     break;
//                 case 4: // restaurant
//                     newTile = new Terrain(64, 192, 16, 16, j, i, groundTexture_);
//                     break;
//                 case 5: // gas station
//                     newTile = new Terrain(48, 288, 16, 16, j, i, groundTexture_);
//                     break;
//                 case 6: // office
//                     newTile = new Terrain(64, 144, 16, 16, j, i, groundTexture_);
//                     break;
//                 case 7: // police HQ
//                     newTile = new Terrain(48, 336, 16, 16, j, i, groundTexture_);
//                     break;
//                 default:
//                     newTile = new Terrain(64, 0, 16, 16, j, i, groundTexture_);
//                     break;
//             }

//             newTile->setTileType(Data::tileTypes[randNum]);
//             newTile->setTileStats(getRandomStatsArray());
//             newTile->setTileMissions(tileMissionsFull);
//             if (i == groundTiles_.size()/2 && j == groundTiles_[i].size()/2) {
//                 startingLoc_.x = j;
//                 startingLoc_.y = i;
//                 newTile->setTileStatus(Data::reclaimedTile);
//             } else {
//                 newTile->setTileStatus(Data::undiscoveredTile);
//             }

//             groundTiles_[i][j] = newTile;

//             // cout << "Tile type: " << newTile->getTileType() << endl;
//             // cout << "Tile stats: " << newTile->getTileStats()[0] << " " << newTile->getTileStats()[1] << " " << newTile->getTileStats()[2] << endl;
//             // cout << " " << endl;
//         }
//     }
//     // Set the tiles immediately around starting tile to wild
//     groundTiles_[startingLoc_.y][startingLoc_.x-1]->setTileStatus(Data::wildTile);
//     wildTilesCoords.push_back(pair<startingLoc_.y, startingLoc_.x-1>);
//     groundTiles_[startingLoc_.y-1][startingLoc_.x-1]->setTileStatus(Data::wildTile);
//     groundTiles_[startingLoc_.y-1][startingLoc_.x]->setTileStatus(Data::wildTile);
//     groundTiles_[startingLoc_.y-1][startingLoc_.x+1]->setTileStatus(Data::wildTile);
//     groundTiles_[startingLoc_.y][startingLoc_.x+1]->setTileStatus(Data::wildTile);
//     groundTiles_[startingLoc_.y+1][startingLoc_.x+1]->setTileStatus(Data::wildTile);
//     groundTiles_[startingLoc_.y+1][startingLoc_.x]->setTileStatus(Data::wildTile);
//     groundTiles_[startingLoc_.y+1][startingLoc_.x-1]->setTileStatus(Data::wildTile);

//     return 0;
// }

// Terrain* World::getGroundTileAtPos(int y, int x) {
//     if (groundTiles_[y][x] == nullptr) {
//         return nullptr;
//     }
//     return groundTiles_[y][x];
// }

// sf::Vector2u World::getStartingLoc() {
//     return startingLoc_;
// }

// int World::loadTerrainTextures() {
//     if (!groundTexture_.loadFromFile("assets/groundtiles.png")) {
//         return -1;
//     }
//     return 0;
// }

// int* World::getRandomStatsArray() {
//     int lb = 0, ub = Data::numTileStatStates-1;
//     static int r[Data::numTileStats] = {0, 0, 0};
//     for (int i = 0; i < Data::numTileStats; i++) {
//         int randNum = rand() % (ub - lb + 1) + lb;
//         // cout << "Random stats arr. RandNum: " << randNum << " at index i: " << i << endl;
//         // cout << "Tile stat: " << Data::tileStats[i] << "Tile stat desc: " << Data::tileStatDescs[randNum] << endl;
//         r[i] = randNum;
//     }
//     return r;
// }